


#include "supConsole.hpp"



namespace SC {


    void print_errorLUA(lua_State* state) {
        // The error message is on top of the stack.
        // Fetch it, print it and then pop it off the stack.
        const char* message = lua_tostring(state, -1);

        SC::clog(message, SC::LOG_LUA_ERROR);
        lua_pop(state, 1);
    }

    void executeLUA(std::string data)
    {
        lua_State* state = luaL_newstate();

        // Make standard libraries available in the Lua object
        luaL_openlibs(state);

        int result;

        // Load the program; this supports both source code and bytecode files.
        result = luaL_loadstring(state, data.c_str());

        if (result != LUA_OK) {
            print_errorLUA(state);
            return;
        }

        // Finally,e execute the program by calling into it.
        // Change the arguments if you're not running vanilla Lua code.

        result = lua_pcall(state, 0, LUA_MULTRET, 0);

        if (result != LUA_OK) {
            print_errorLUA(state);
            return;
        }
    }
	void luaInterp(std::string cmd) {
		
        executeLUA(cmd);
	} // interpret lua







}