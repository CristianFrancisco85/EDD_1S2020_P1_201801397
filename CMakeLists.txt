cmake_minimum_required(VERSION 3.15)
project(Practica1EDD)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-lncurses")

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

include_directories(include)
file(GLOB SOURCES "*.c")

add_executable(Practica1EDD main.cpp Nodo.h DoubleLinkedList.h Stack.h Word.h Change.h Archive.h DoubleLinkedCircularList.h)
target_link_libraries(Practica1EDD ${CURSES_LIBRARIES})