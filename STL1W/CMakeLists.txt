cmake_minimum_required(VERSION 3.21)
project(nowcoder)

set(CMAKE_CXX_STANDARD 20)

# 获取cpp文件相对于当前工作路径的相对路径，即文件名
# 工作路径${CMAKE_CURRENT_SOURCE_DIR}就是CMakeList.txt所在的文件夹
file(GLOB files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
# 遍历每个文件名
foreach (file ${files})
    # 将去掉后缀的文件名存入exe变量（executable的缩写，不是代表.exe）
    string(REGEX REPLACE "(.+).cpp$" "\\1" exe ${file})
    # 分别生成add_executable(<name> <source>)命令
    set(cur_name "STL1W-${exe}")
    add_executable(${cur_name} ${file})
    #fmt support
    target_link_libraries(${cur_name} fmt-header-only)
endforeach ()
