// supConsole.h : fichier Include pour les fichiers Include système standard,
// ou les fichiers Include spécifiques aux projets.

 // -- OPTION 

  // system support
 //#define SYS_LINUX 
#define SYS_WINDOWS
#ifdef SYS_LINUX
#include <sys/ioctl.h> // use for get width and get height
#endif // SYS_LINUX

#ifdef SYS_WINDOWS
#include <windows.h>
#endif // SYS_WINDOWS
#include <algorithm>

#include <sstream>
#include "ConsoleUtil.hpp"
#include "lib/lua/lua.hpp"
#include <iostream>
#include <iomanip>
// TODO: Référencez ici les en-têtes supplémentaires nécessaires à votre programme.
