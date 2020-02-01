# CMakeList.txt : projet CMake pour supConsole, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_minimum_required (VERSION 3.8)

# Ajoutez une source à l'exécutable de ce projet.
add_executable (supConsole "supConsole.cpp" "supConsole.hpp" "ConsoleUtil.hpp" "ConsoleUtil.cpp" "ConsoleAttrib.cpp")

# TODO: Ajoutez des tests et installez des cibles si nécessaire.
