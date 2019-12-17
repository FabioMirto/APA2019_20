cmake_minimum_required(VERSION 3.15)
project(lab9_es2 C)

set(CMAKE_C_STANDARD 99)

add_executable(lab9_es2 main9_2.c inv.c inv.h pgList.h pgList.c pg.h pg.c invArray.h invArray.c
        equipArray.h equipArray.c)
