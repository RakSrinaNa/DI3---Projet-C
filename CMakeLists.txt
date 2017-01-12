cmake_minimum_required(VERSION 3.6)
project(ex_projet2)

add_definitions(-std=c99 -Wall -Werror -W -pedantic -static -g)
set_property(TARGET PROPERTY C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/main.c
        src/mainKergosien.c src/mainKergosien.h
        src/unit/mainUnit.c src/unit/mainUnit.h
        src/unit/unit.c src/unit/unit.h
        src/utils.h

        src/instance.c src/instance.h
        src/unit/instanceUnit.c src/unit/instanceUnit.h

        src/item.c src/item.h
        src/unit/itemUnit.c src/unit/itemUnit.h

        src/parser.c src/parser.h
        src/unit/parserUnit.c src/unit/parserUnit.h

        src/solutionDirect.c src/solutionDirect.h
        src/unit/solutionDirectUnit.c src/unit/solutionDirectUnit.h

        src/bag.c src/bag.h
        src/unit/bagUnit.c src/unit/bagUnit.h

        src/solutionIndirect.c src/solutionIndirect.h
        src/unit/solutionIndirectUnit.c src/unit/solutionIndirectUnit.h

        src/solution.c src/solution.h
        src/unit/solutionUnit.c src/unit/solutionUnit.h

        src/heuristic.c src/heuristic.h
        src/unit/heuristicUnit.c src/unit/heuristicUnit.h

        src/scheduler.c src/scheduler.h
        src/unit/schedulerUnit.c src/unit/schedulerUnit.h

        src/metaheuristicLocal.c src/metaheuristicLocal.h
        src/unit/metaheuristicLocalUnit.c src/unit/metaheuristicLocalUnit.h

        src/metaheuristicTabou.c src/metaheuristicTabou.h
        src/unit/metaheuristicTabouUnit.c src/unit/metaheuristicTabouUnit.h
        )
add_executable(ex_projet2 ${SOURCE_FILES})
