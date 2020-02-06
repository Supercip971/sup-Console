# CMakeList.txt : projet CMake pour supConsole, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_minimum_required (VERSION 3.8)

# Ajoutez une source à l'exécutable de ce projet.

file(GLOB ldd
    "lib/lua/*.hpp"
    "lib/lua/*.h"
    "lib/lua/*.cpp"
    "lib/lua/*.c"
)
file(GLOB luad
    "app/*.lua"
)

add_executable (supConsole "main.cpp" "supConsole.hpp" "ConsoleUtil.hpp" "ConsoleUtil.cpp" "ConsoleAttrib.cpp" "luaSC.cpp" "luaUtil.cpp" "luaUtil.hpp" ${ldd} project.rc)

# TODO: Ajoutez des tests et installez des cibles si nécessaire.
