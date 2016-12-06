cmake_minimum_required(VERSION 3.6)
project(Projet2)

add_definitions(-std=c89 -pedantic-errors)
set_property(TARGET PROPERTY C_STANDARD 89)
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.c)
add_executable(Projet2 ${SOURCE_FILES})