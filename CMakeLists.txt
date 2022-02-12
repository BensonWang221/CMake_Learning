cmake_minimum_required(VERSION 3.10)

#Sets the name of the project, and stores it in the variable PROJECT_NAME. When called from the top-level CMakeLists.txt 
#also stores the project name in the variable CMAKE_PROJECT_NAME.
project(Tutorial VERSION 1.0)

add_executable(Tutorial tutorial.cxx)