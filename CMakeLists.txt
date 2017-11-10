cmake_minimum_required(VERSION 3.8)
project(Projet_2)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES
        Code/main.c
        Code/Maze.h
        Code/UnionFind.h Code/UnionFindList.c Code/UnionFindTree.c Code/Maze.c)

add_executable(Projet_2 ${SOURCE_FILES})