# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required(VERSION 3.16)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(graphics "main.cpp" "GameManager.cpp" "GameManager.h" "GameView.cpp" "GameView.h")
target_link_libraries(
    graphics 
        PRIVATE sfml-graphics
        PUBLIC othello_lib
        PUBLIC players_lib
)

if(WIN32)
    add_custom_command(
        TARGET graphics
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:graphics>
        VERBATIM)
endif()


#target_include_directories(graphics PRIVATE shaders)
#install(DIRECTORY shaders DESTINATION .)

add_custom_command(
         TARGET graphics PRE_BUILD
         COMMAND ${CMAKE_COMMAND} -E copy_directory              
             ${CMAKE_SOURCE_DIR}/graphics/shaders $<TARGET_FILE_DIR:graphics>/shaders
         COMMENT "Copying shaders to \/bin" VERBATIM
 )

# ADD_DEPENDENCIES ( graphics copy_shader_files )

install(TARGETS graphics)
