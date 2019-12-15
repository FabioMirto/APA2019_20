cmake_minimum_required(VERSION 3.15)
project(es2incompleto C)

set(CMAKE_C_STANDARD 99)

add_executable(es2incompleto main.c inv.c inv.h invArray.c invArray.h
        equipArray.h equipArray.c pg.h pg.c pgList.h pgList.c)