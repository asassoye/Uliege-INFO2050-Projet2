cmake_minimum_required(VERSION 3.8)
project(Projet_2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Code/main.c
        Code/Maze.h
        Code/UnionFind.h)

add_executable(Projet_2 ${SOURCE_FILES})