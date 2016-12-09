cmake_minimum_required(VERSION 3.6)
project(ex_projet2)

add_definitions(-std=c99 -Wall -Werror -W -pedantic)
set_property(TARGET PROPERTY C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.c src/mainUnit.c src/instance.c src/instanceUnit.c src/item.c src/itemUnit.c src/parser.c src/parserUnit.c src/solutionDirect.c src/solutionIndirect.c)
add_executable(ex_projet2 ${SOURCE_FILES})
