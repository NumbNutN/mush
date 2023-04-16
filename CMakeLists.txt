cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(CMAKE_C_COMPILER "/usr/bin/gcc")

project(mush)



set(CMAKE_C_STANDARD 99)


include_directories(.)

include_directories(${CMAKE_SOURCE_DIR})

file(GLOB_RECURSE DIR_SRC "src/*.c")
#包含的头文件目录

find_package(BISON)
BISON_TARGET(MyParser sh.y ${CMAKE_SOURCE_DIR}/sh.tab.c)

find_package(FLEX)
FLEX_TARGET(MyScanner sh.l ${CMAKE_SOURCE_DIR}/lex.yy.c)

#设置可执行文件的输出目录
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

#添加编译选项
add_compile_options(-g)

#生成可执行文件
add_executable(${PROJECT_NAME} ${DIR_SRC} ${BISON_MyParser_OUTPUTS} ${FLEX_MyScanner_OUTPUTS})
