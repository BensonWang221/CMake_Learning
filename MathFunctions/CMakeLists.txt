# 应该先构建MakeTable
add_executable(MakeTable MakeTable.cxx)

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Table.h
    COMMAND MakeTable ${CMAKE_CURRENT_BINARY_DIR}/Table.h
    DEPENDS MakeTable
    )
#add_library(<name> [STATIC|SHARED|MODULE] [EXCLUDE_FROM_ALL]
#            source1 [source2 ...])
# <name>: 库的名字, 直接写名字不用加lib
# [SHARED]: 动态库; [STATIC]: 静态库; [MODULE]: 在使用dyld系统有效,非dyld则同SHARED
# EXCLUDE_FROM_ALL: 这个库不会被默认构建,除非有其它组件依赖或手动构建
add_library(MathFunctions
            EXCLUDE_FROM_ALL
            mysqrt.cxx
            # 这里必须要说明Table.h, 指定MathFunctions依赖Table.h
            # 这样才会让构建MathFunctions前先生成Table.h
            ${CMAKE_CURRENT_BINARY_DIR}/Table.h)

message("current binary directory: ${CMAKE_CURRENT_BINARY_DIR}")

# 以下是示例
# SET(LIBHELLO_SRC hello.c)
# ADD_LIBRARY(hello SHARED ${LIBHELLO_SRC})
# ADD_LIBRARY(hello_static STATIC ${LIBHELLO_SRC})
# 一般我们使用的静态库/动态库只是后缀名不同而已，上面构建的libhello.so与libhello_static.a，
# 显然名字不同哦。这时你会有一个想法，那我把hello_static改成hello，结果是不可行的，静态库无法构建。
# 重名会忽略第二条指令。
# 解决办法:
# SET_TARGET_PROPERTIES(hello_static PROPERTIES OUTPUT_NAME "hello")
# !!这里表示外部链接到此库的话就不用再include_directories添加本库的include路径了
target_include_directories(MathFunctions 
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
                           PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
                           )

message("Current source directory: ${CMAKE_CURRENT_SOURCE_DIR},\n
         Current binary directory: ${CMAKE_CURRENT_BINARY_DIR}")

# checksymbolexists (SYMBOL FILES VARIABLE): 查找相关文件(FILES)
# 里面是否包含相关符号(SYMBOL), 如果存在则设置VARIABLE为1
# 需要在CMakeLists中包含CheckSymbolExists --> include (CheckSymbolExists)
# If the symbol is a type, enum value, or intrinsic it will not be recognized 
# (consider using CheckTypeSize or CheckCSourceCompiles)
# If the check needs to be done in C++, consider using CheckCXXSymbolExists instead.
#include(CheckSymbolExists)
# unset(<variable> PARENT_SCOPE)
# PARENT_SCOPE: 清除时也带上PARENT_SCOPE
# 如清除缓存变量时带上CACHE unset(<variable> CACHE)
# 如清除环境变量 unset(ENV{<variable>})
#check_symbol_exists(log "math.h" HAVE_LOG)
#check_symbol_exists(exp "math.h" HAVE_EXP)
#if(NOT(HAVE_LOG AND HAVE_EXP))
#    unset(HAVE_LOG CACHE)
#    unset(HAVE_EXP CACHE)
#    # CMAKE_REQUIRED_LIBRARIES还不知道什么意思
#    set(CMAKE_REQUIRED_LIBRARIES "m")
#    check_symbol_exists(log "math.h" HAVE_LOG)
#    check_symbol_exists(exp "math.h" HAVE_EXP)
#    if(HAVE_EXP AND HAVE_LOG)
#        target_link_libraries(MathFunctions PRIVATE m)
#    endif()
#endif()

#if (HAVE_EXP AND HAVE_LOG)
#    # target_compile_definitions(<target>
#    #                            <INTERFACE|PUBLIC|PRIVATE> [items1 ...]
#    #                            <INTERFACE|PUBLIC|PRIVATE> [items2 ...])
#    # 下面这样使用的话, 就相当于在源代码中定义了这些宏
#    target_compile_definitions(MathFunctions PRIVATE "HAVE_LOG" "HAVE_EXP")
#endif()