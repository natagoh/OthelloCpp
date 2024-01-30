include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_executable(othello_board_test OthelloBoardTest.cpp)
target_link_libraries(
  othello_board_test
  PRIVATE
  GTest::GTest
  othello_lib
)

add_executable(othello_get_actions_test OthelloGetActionsTest.cpp)
target_link_libraries(
  othello_get_actions_test
  PRIVATE
  GTest::GTest
  othello_lib
)


# gtest_discover_tests(othello_board_test)
add_test(othello_board_gtest othello_board_test)
add_test(othello_get_actions_gtest othello_get_actions_test)

