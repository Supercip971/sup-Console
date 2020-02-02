# CMakeList.txt : projet CMake pour supConsole, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_minimum_required (VERSION 3.8)

# Ajoutez une source à l'exécutable de ce projet.

file(GLOB lib/lua
    "*.hpp"
    "*.h"
    "*.cpp"
)

add_executable (supConsole "main.cpp" "supConsole.hpp" "ConsoleUtil.hpp" "ConsoleUtil.cpp" "ConsoleAttrib.cpp" "luaImpl.cpp" ${lib/lua})

# TODO: Ajoutez des tests et installez des cibles si nécessaire.
