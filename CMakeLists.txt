
cmake_minimum_required(VERSION 3.28)
project(bluffjack)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES "src/*.cpp")

file(GLOB_RECURSE HEADERS "src/*.h")

set(MAIN_SRC "src/main.cpp"
        src/exceptions/pot_exceptions.cpp
        src/exceptions/pot_exceptions.h
        src/exceptions/card_exceptions.cpp
        src/exceptions/card_exceptions.h
        src/exceptions/tree_exceptions.cpp
        src/exceptions/tree_exceptions.h
        src/exceptions/table_exceptions.cpp
        src/exceptions/table_exceptions.h)

list(REMOVE_ITEM SOURCES "${MAIN_SRC}")

# Add the executable
add_executable(bluffjack ${SOURCES} ${HEADERS} ${MAIN_SRC})