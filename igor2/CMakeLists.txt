cmake_minimum_required(VERSION 3.1)

project(string)

set(PROG_SRC main.cpp CString.cpp CString0.cpp CString1.cpp Creator.cpp)
set(PROG_HDR AutoTest.h CString.h CString0.h CString1.h Creator.h)

configure_file(input.txt input.txt COPYONLY)

add_executable(${PROJECT_NAME} ${PROG_SRC} ${PROG_HDR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined -std=c++17")
