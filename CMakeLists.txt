cmake_minimum_required(VERSION 3.22)
project(coding-backend)

set(CMAKE_CXX_STANDARD 20)

set(MY_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(MY_INPUT_DIR "${MY_DIR}/input/")

include_directories(dependency/include)

add_subdirectory(dependency/fmt EXCLUDE_FROM_ALL)

add_subdirectory(leetcode)

add_subdirectory(nowcoder)

add_subdirectory(dependency/leetcode-debug)

add_subdirectory(test)

add_subdirectory(utility)

add_subdirectory(STL1W)

add_subdirectory(Batch)