# CMakeList.txt : CMake project for OthelloCpp, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_library (players_lib "PlayerInterface.h" "RandomPlayer.h" "RandomPlayer.cpp")
# add_executable (players "PlayerInterface.h" "RandomPlayer.h" "RandomPlayer.cpp")

target_link_libraries(players_lib PUBLIC othello_lib)

# TODO: Add tests and install targets if needed.
