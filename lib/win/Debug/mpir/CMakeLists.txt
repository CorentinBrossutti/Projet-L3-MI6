# CMakeList.txt : projet CMake pour MPIR, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_minimum_required (VERSION 3.8)

# Ajoutez une source à l'exécutable de ce projet.
add_library(MPIR_DEBUG SHARED "mpir.lib")
set_target_properties(MPIR_DEBUG PROPERTIES LINKER_LANGUAGE CXX)
