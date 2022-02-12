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

# option (<variable> "<help_text>" [value]) 选项
# variable: 选项名; help_text: 描述/备注; value: 选项初始化值(除ON以外全为OFF)
option(USE_MYMATH "Use tutorial provided math implementation" ON)

configure_file(TutorialConfig.h.in TutorialConfig.h)

if(USE_MYMATH)
    # add_subdirectory (source_dir [binary_dir] [EXCLUDE_FROM_ALL]): 添加一个子目录并构建该子目录
    # source_dir: 指定一个子目录, 子目录应该包含CMakeLists.txt文件和代码文件
    # binary_dir: 用于存放子目录构建输出文件存放路径
    # EXCLUDE_FROM_ALL: 若
    # 加了add_subdirectory后就不用在target_include_directories了
    add_subdirectory(MathFunctions)
    list(APPEND EXTRA_LIBS MathFunctions)
    list(APPEND EXTRA_INCLUDED "${PROJECT_SOURCE_DIR}/MathFunctions")
endif()

add_executable(Tutorial tutorial.cxx)

# PUBLIC/PRIVATE/INTERFACE的区别
# PUBLIC: 如果目标的头文件包含了依赖的头文件(源文件简介包含), 那么就是PUBLIC
# PRIVATE: 如果目标仅仅是源文件中包含了依赖的头文件, 那么就是PRIVATE
# INTERFACE: 目标的头文件包含依赖, 但源文件未包含, 那么就是INTERFACE
target_link_libraries(Tutorial PUBLIC ${EXTRA_LIBS})

#为指定项目添加include路径
target_include_directories(Tutorial PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          ${EXTRA_INCLUDED}
                          )