cmake_minimum_required(VERSION 3.6)
project(ex_projet2)

add_definitions(-std=c99 -Wall -Werror -W -pedantic -static -g)
set_property(TARGET PROPERTY C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/main.c
        src/mainKergosien.c src/headers/mainKergosien.h
        src/unit/mainUnit.c src/unit/headers/mainUnit.h
        src/unit/unit.c src/unit/headers/unit.h
        src/headers/utils.h

        src/instance.c src/headers/instance.h
        src/unit/instanceUnit.c src/unit/headers/instanceUnit.h

        src/item.c src/headers/item.h
        src/unit/itemUnit.c src/unit/headers/itemUnit.h

        src/parser.c src/headers/parser.h
        src/unit/parserUnit.c src/unit/headers/parserUnit.h

        src/solutionDirect.c src/headers/solutionDirect.h
        src/unit/solutionDirectUnit.c src/unit/headers/solutionDirectUnit.h

        src/bag.c src/headers/bag.h
        src/unit/bagUnit.c src/unit/headers/bagUnit.h

        src/solutionIndirect.c src/headers/solutionIndirect.h
        src/unit/solutionIndirectUnit.c src/unit/headers/solutionIndirectUnit.h

        src/solution.c src/headers/solution.h
        src/unit/solutionUnit.c src/unit/headers/solutionUnit.h

        src/heuristic.c src/headers/heuristic.h
        src/unit/heuristicUnit.c src/unit/headers/heuristicUnit.h

        src/scheduler.c src/headers/scheduler.h
        src/unit/schedulerUnit.c src/unit/headers/schedulerUnit.h

        src/metaheuristicLocal.c src/headers/metaheuristicLocal.h
        src/unit/metaheuristicLocalUnit.c src/unit/headers/metaheuristicLocalUnit.h

        src/metaheuristicTabou.c src/headers/metaheuristicTabou.h
        src/unit/metaheuristicTabouUnit.c src/unit/headers/metaheuristicTabouUnit.h
        )
add_executable(ex_projet2 ${SOURCE_FILES})
