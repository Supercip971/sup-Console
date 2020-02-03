
 // -- OPTION 

  // system support
 //#define SYS_LINUX 

#define SYS_WINDOWS
#ifdef SYS_LINUX
#include <sys/ioctl.h> // use for get width and get height
#include <cstring>
#include <unistd.h>
#include <cstdio>

#endif // SYS_LINUX

#ifdef SYS_WINDOWS
#include <windows.h>
#endif // SYS_WINDOWS


#include <stdlib.h>


#include <algorithm>

#include "luaUtil.hpp"
#include <stdio.h>
#include <sstream>
extern "C" {
#include "lib/lua/lua.h"
#include "lib/lua/lauxlib.h"
#include "lib/lua/lualib.h"
}

#include "ConsoleUtil.hpp"
#include <iostream>
#include <iomanip>
