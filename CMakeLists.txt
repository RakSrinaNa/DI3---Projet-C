cmake_minimum_required(VERSION 3.6)
project(ex_projet2)

add_definitions(-std=c99 -Wall -Werror -W -pedantic)
set_property(TARGET PROPERTY C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/main.c src/mainUnit.c

        src/instance.c src/instance.h
        src/instanceUnit.c src/instanceUnit.h

        src/item.c src/item.h
        src/itemUnit.c src/itemUnit.h

        src/parser.c src/parser.h
        src/parserUnit.c  src/parserUnit.h

        src/solutionDirect.c src/solutionDirect.h
        src/solutionDirectUnit.c src/solutionDirectUnit.h

        src/bag.c src/bag.h

        src/solutionIndirect.c src/solutionIndirect.h
        src/solutionIndirectUnit.c src/solutionIndirectUnit.h
        )
add_executable(ex_projet2 ${SOURCE_FILES})
