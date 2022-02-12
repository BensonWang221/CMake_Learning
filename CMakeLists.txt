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
    # 关于list, 看https://www.jianshu.com/p/89fb01752d6f
    list(APPEND EXTRA_LIBS MathFunctions)
    # !!注意这里没有EXTRA_INCLUDE了,相比于step3来说, 因为下级指定了库的include_directories并用了INTERFACE
endif()

add_executable(Tutorial tutorial.cxx)

# PUBLIC/PRIVATE/INTERFACE的区别
# PUBLIC: 如果目标的头文件包含了依赖的头文件(源文件简介包含), 那么就是PUBLIC
# PRIVATE: 如果目标仅仅是源文件中包含了依赖的头文件, 那么就是PRIVATE
# INTERFACE: 目标的头文件包含依赖, 但源文件未包含, 那么就是INTERFACE, consumers require but the producer doesn't
target_link_libraries(Tutorial PUBLIC ${EXTRA_LIBS})

#为指定项目添加include路径
target_include_directories(Tutorial PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          )

# install命令看https://blog.csdn.net/rangfei/article/details/109304175
install(TARGETS Tutorial DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h"
    DESTINATION include 
    )

# 开启项目的测试功能 make test执行
enable_testing()

# add_test(NAME <name> [CONFIGURATIONS [DEBUG|RELEASE|...]]
#          [WORKING_DIRECTORY dir]
#          COMMAND <command> [arg1 [arg2 ...]])
# 通过NAME关键值指定本测试的名称
# DEBUG/RELEASE选项可以控制在不同编译版本下是否进行测试
# WORKING_DIRECTORY可以设置工作路径
# command表示测试需要运行的命令

# does the application run
add_test(NAME Runs COMMAND Tutorial 25)

# does the usage message work
add_test(NAME Usage COMMAND Tutorial)
set_tests_properties(Usage PROPERTIES
    PASS_REGULAR_EXPRESSION "Usage:.*number"
    )

# define a function to simplify adding tests
function(do_test target arg result)
    add_test(NAME Comp${arg} COMMAND ${target} ${arg})
    set_tests_properties(Comp${arg}
        PROPERTIES PASS_REGULAR_EXPRESSION ${result}
    )
endfunction()

# do a bunch of result based tests
do_test(Tutorial 4 "4 is 2")
do_test(Tutorial 9 "9 is 3")
do_test(Tutorial 5 "5 is 2.236")
do_test(Tutorial 7 "7 is 2.645")
do_test(Tutorial 25 "25 is 5")
do_test(Tutorial -25 "-25 is (-nan|nan|0)")
do_test(Tutorial 0.0001 "0.0001 is 0.01")