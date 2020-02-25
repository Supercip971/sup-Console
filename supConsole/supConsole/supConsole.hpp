
 // -- OPTION 

  // system support
 //#define SYS_LINUX 
    // When you build on windows you define SYS_WINDOWS and if you build for linux you define SYS_LINUX (only ubuntu is supported)
#define SYS_WINDOWS
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#ifdef SYS_LINUX


#include <sys/ioctl.h> // use for get width and get height
#include <cstring>
#include <unistd.h>
#include <cstdio>

#endif // SYS_LINUX

#ifdef SYS_WINDOWS

#include <windows.h>

#endif // SYS_WINDOWS
#include <filesystem>
namespace fs = std::filesystem;



#include <limits.h>
#include <stdlib.h>
#include <memory>
#include <stdexcept>
#include <array>
#include <stdlib.h>
#include <sys/stat.h>
#include <algorithm>
#include "luaUtil.hpp"
#include <stdio.h>
#include <sstream>

#include <iomanip>
#include <iostream>
#include <experimental/filesystem>
#include <fstream>

extern "C" {
#include "lib/lua/lua.h"
#include "lib/lua/lauxlib.h"
#include "lib/lua/lualib.h"
}

#include "ConsoleUtil.hpp"
