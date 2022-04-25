cmake_minimum_required(VERSION 3.21)
project(polynomial C)

set(CMAKE_C_STANDARD 11)

add_executable(polynomial main.c gc.c gc.h list.c list.h polynomial.c polynomial.h)
