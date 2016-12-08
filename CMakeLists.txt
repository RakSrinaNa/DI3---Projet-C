cmake_minimum_required(VERSION 3.6)
project(ex_projet2)

add_definitions(-std=c99 -Wall -Werror -W -pedantic)
set_property(TARGET PROPERTY C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.c instance.c object.c parser.c stringUtils.c)
add_executable(ex_projet2 ${SOURCE_FILES})
