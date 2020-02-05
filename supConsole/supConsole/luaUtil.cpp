
#include "supConsole.hpp"


// all non super important lua function
namespace SC {

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


		void LoadLUCommand(lua_State* L) {
			lua_register(L, "dirExist", dirExist); //  dirExist(string arg) return : bool  | get if the directory exist or not
			lua_register(L, "dirTop", dirTop); //  dirTop(string arg) return : string  | get the top directory
		};


	};



}