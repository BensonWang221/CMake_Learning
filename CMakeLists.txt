cmake_minimum_required(VERSION 3.10)

#Sets the name of the project, and stores it in the variable PROJECT_NAME. When called from the top-level CMakeLists.txt 
#also stores the project name in the variable CMAKE_PROJECT_NAME.
project(Tutorial VERSION 1.0)

#指定CMAKE编译C++版本有两种方法
#一个是在CMakeLists中set(CMAKE_CXX_STANDARD ...) 比较好的方法
#另一个是在cmake命令行时，cmake -DCMAKE_CXX_STANDARD=11
set(CMAKE_CXX_STANDARD 11)
#CMAKE_CXX_STANDARD_REQUIRED设置为True，则必须使用CMAKE_CXX_STANDARD指定的版本,
#如果CMAKE_CXX_STANDARD_REQUIRED设置为OFF则CMAKE_CXX_STANDARD指定版本的为首选版本，如果没有会使用上一版本。
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file(TutorialConfig.h.in TutorialConfig.h)

add_executable(Tutorial tutorial.cxx)

message(STATUS "binary dir ${PROJECT_BINARY_DIR}")

#为指定项目添加include路径
target_include_directories(Tutorial PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          )