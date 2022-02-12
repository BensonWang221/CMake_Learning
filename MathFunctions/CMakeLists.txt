#add_library(<name> [STATIC|SHARED|MODULE] [EXCLUDE_FROM_ALL]
#            source1 [source2 ...])
# <name>: 库的名字, 直接写名字不用加lib
# [SHARED]: 动态库; [STATIC]: 静态库; [MODULE]: 在使用dyld系统有效,非dyld则同SHARED
# EXCLUDE_FROM_ALL: 这个库不会被默认构建,除非有其它组件依赖或手动构建
add_library(MathFunctions EXCLUDE_FROM_ALL mysqrt.cxx)

# !!这里表示外部链接到此库的话就不用再include_directories添加本库的include路径了
target_include_directories(MathFunctions INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# 以下是示例
# SET(LIBHELLO_SRC hello.c)
# ADD_LIBRARY(hello SHARED ${LIBHELLO_SRC})
# ADD_LIBRARY(hello_static STATIC ${LIBHELLO_SRC})
# 一般我们使用的静态库/动态库只是后缀名不同而已，上面构建的libhello.so与libhello_static.a，
# 显然名字不同哦。这时你会有一个想法，那我把hello_static改成hello，结果是不可行的，静态库无法构建。
# 重名会忽略第二条指令。
# 解决办法:
# SET_TARGET_PROPERTIES(hello_static PROPERTIES OUTPUT_NAME "hello")