
#include "supConsole.hpp"


// all non super important lua function
namespace SC {
	std::ifstream::pos_type filesize(const char* filename)
	{
		std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
		return in.tellg();
	}
	namespace LU {





		static int dirExist(lua_State* Li) {
			int n = lua_gettop(Li);

			std::string np = lua_tostring(Li, 1);

			 struct stat info ;
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
				}numx++;
			}

			lua_pushstring(Li, strtoreturn.c_str());
			return 1;

		}static int fileNumber(lua_State* Li) {

			std::string np = lua_tostring(Li, 1);
			int numx = 0;
			for (const auto& entry : std::experimental::filesystem::directory_iterator(np)) {

				numx++;
			}

			lua_pushinteger(Li, numx);
			return 1;

		}static int fileSize(lua_State* Li) {

			std::string np = lua_tostring(Li, 1);
			
			lua_pushinteger(Li, SC::filesize(np.c_str()));


			return 1;

		}static int setConsoleCurPos(lua_State* Li) {

			int npx = lua_tointeger(Li, 1);
			int npy = lua_tointeger(Li, 2);
			setConsCurPos({ (float)npx,(float)npy });


			return 0;

		}
		void LoadLUCommand(lua_State* L) {
			lua_register(L, "dirExist", dirExist); //  dirExist(string arg) return : bool  | get if the directory exist or not
			lua_register(L, "dirTop", dirTop); //  dirTop(string arg) return : string  | get the top directory
			lua_register(L, "fileList", fileList); //  fileList(string path, int numberOfFile) return : string  | get the file number of a list
			lua_register(L, "fileNumber", fileNumber); //  fileNumber(string path) return : int  | get the file number
			lua_register(L, "fileSize", fileSize); //  fileSize(string path) return : int  | get the file size
			lua_register(L, "setConsoleCurPos", setConsoleCurPos); //  description to do
		};


	};



}