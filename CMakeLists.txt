# CMAKELists

cmake_minimum_required (VERSION 2.8.11)
project (cairo-test)

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -I/usr/include/SDL -D_GNU_SOURCE=1 -D_REENTRANT")


add_executable (cairo-test test.cpp)

target_link_libraries (cairo-test LINK_PUBLIC SDL2 cairo)
