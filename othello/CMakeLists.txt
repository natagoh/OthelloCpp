﻿# CMakeList.txt : CMake project for OthelloCpp, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (othello "OthelloCpp.cpp" "OthelloCpp.h" "OthelloBoard.cpp" "OthelloBoard.h")

add_library (othello_lib "OthelloBoard.cpp" "OthelloBoard.h")

# TODO: Add tests and install targets if needed.
