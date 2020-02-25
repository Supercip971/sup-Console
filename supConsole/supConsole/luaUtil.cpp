#include "supConsole.hpp"

// all non super important lua function
namespace SC {
	std::ifstream::pos_type filesize(const char* filename)
	{
		std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
		return in.tellg();
	}
	namespace LU {
		std::vector<std::string>* logsInfo;
		static int dirExist(lua_State* Li) {
			int n = lua_gettop(Li);

			std::string np = lua_tostring(Li, 1);

			logsInfo->push_back(" get if file exist : " + np);
			struct stat info;
			bool direxist = false;

			if (stat(np.c_str(), &info) != 0)
				direxist = false;
			else if (info.st_mode & 0x4000) // 0x4000 because visual studio didn't detect the enum >:(
				direxist = true;
			else
				direxist = false;

			lua_pushboolean(Li, direxist);

			return 1;
		}

		static int dirTop(lua_State* Li) {
			int n = lua_gettop(Li);
			std::string np = lua_tostring(Li, 1);
			logsInfo->push_back(" get file top : " + np);
			np = np.substr(0, np.find_last_of("/"));
			lua_pushstring(Li, np.c_str());
			return 1;
		}

		static int fileList(lua_State* Li) {
			std::string np = lua_tostring(Li, 1);
			std::string strtoreturn = "an error has occur";
			int num = lua_tointeger(Li, 2);
			int numx = 0;
			for (const auto& entry : std::experimental::filesystem::directory_iterator(np)) {
				entry.path();
				if (num == numx)
				{
					strtoreturn = entry.path().filename().u8string();
				}
				++numx;
			}

			logsInfo->push_back(" get file list : " + np);
			lua_pushstring(Li, strtoreturn.c_str());
			return 1;
		}

		static int fileNumber(lua_State* Li) {
			std::string np = lua_tostring(Li, 1);
			int numx = 0;
			for (const auto& entry : std::experimental::filesystem::directory_iterator(np)) {
				++numx;
			}

			logsInfo->push_back(" get file number : " + numx);
			lua_pushinteger(Li, numx);
			return 1;
		}

		static int fileSize(lua_State* Li) {
			std::string np = lua_tostring(Li, 1);

			logsInfo->push_back(" get file size : " + np);
			lua_pushinteger(Li, SC::filesize(np.c_str()));
			return 1;
		}

		static int setConsoleCurPos(lua_State* Li) {
			int npx = lua_tointeger(Li, 1);
			int npy = lua_tointeger(Li, 2);
			setConsCurPos({ (float)npx,(float)npy });

			logsInfo->push_back(" set console cursot pos : " + std::to_string(npx) + " " + std::to_string(npy));
			return 0;
		}

		static int getOS(lua_State* Li) {
			int n = lua_gettop(Li);
			std::string OS = "windows";
#ifdef SYS_LINUX
			OS = "linux";
#endif // SYS_WINDOWS
			lua_pushstring(Li, OS.c_str());
			logsInfo->push_back(" get OS");
			return 1;
		}

		static int getConsoleSize(lua_State* Li) {
			int npx = lua_tointeger(Li, 1);
			int npy = lua_tointeger(Li, 2);
			setConsCurPos({ (float)npx,(float)npy });

			return 2;
		} // doing

		static int pathAbsolute(lua_State* Li) {
			int n = lua_gettop(Li);
			std::string fp = lua_tostring(Li, 1);
			logsInfo->push_back(" get path Absolute" + fp);
			fp = std::filesystem::absolute(fp).string();

			lua_pushstring(Li, fp.c_str());
			return 1;
		}
		void LoadLUCommand(lua_State* L) {
			logsInfo = SC::gettingSysInfo();
			clog("loading lua function : dirExist", LOG_NORMAL);
			lua_register(L, "dirExist", dirExist); //  dirExist(string arg) return : bool  | get if the directory exist or not

			clog("loading lua function : dirTop", LOG_NORMAL);
			lua_register(L, "dirTop", dirTop); //  dirTop(string arg) return : string  | get the top directory

			clog("loading lua function : fileList", LOG_NORMAL);
			lua_register(L, "fileList", fileList); //  fileList(string path, int numberOfFile) return : string  | get the file number of a list

			clog("loading lua function : fileNumber", LOG_NORMAL);
			lua_register(L, "fileNumber", fileNumber); //  fileNumber(string path) return : int  | get the file number

			clog("loading lua function : fileSize", LOG_NORMAL);
			lua_register(L, "fileSize", fileSize); //  fileSize(string path) return : int  | get the file size

			clog("loading lua function : setConsoleCurPos", LOG_NORMAL);
			lua_register(L, "setConsoleCurPos", setConsoleCurPos); //  setConsoleCurPos(int x, int y) return : nothing | set console cursor pos (-1 for y = don't change y value)

			clog("loading lua function : getConsoleSize", LOG_NORMAL);
			lua_register(L, "getConsoleSize", getConsoleSize); //  to do

			clog("loading lua function : getOs", LOG_NORMAL);
			lua_register(L, "getOs", getOS); //  getOs () return : string | get the os [linux / windows]

			clog("loading lua function : pathAbsolute", LOG_NORMAL);
			lua_register(L, "pathAbsolute", pathAbsolute); //  pathAbsolute(string path) return : path absolute | for ../ replacing and other thing
		};
	};
}