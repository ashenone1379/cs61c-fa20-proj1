cmake_minimum_required(VERSION 3.5)

set(CMAKE_C_STANDARD 99)

project(game_of_life)

add_executable(test-imageloader
        gameoflife.c
        imageloader.c
        imageloader.h
)