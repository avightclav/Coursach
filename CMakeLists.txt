cmake_minimum_required(VERSION 3.9)
project(Coursach)

set(CMAKE_CXX_STANDARD 11)

add_executable(Coursach main.cpp Calc/headers/rkf45.h Calc/headers/fmin.h)