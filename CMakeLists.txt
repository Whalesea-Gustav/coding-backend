cmake_minimum_required(VERSION 3.22)
project(codeforce)

set(CMAKE_CXX_STANDARD 17)

set(MY_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(MY_INPUT_DIR "${MY_DIR}/input/")

include_directories(dependency/include)

add_subdirectory(dependency/fmt EXCLUDE_FROM_ALL)

add_subdirectory(leetcode)

add_subdirectory(nowcoder)

add_subdirectory(dependency/leetcode-debug)