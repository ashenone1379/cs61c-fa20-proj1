cmake_minimum_required(VERSION 3.5)

set(CMAKE_C_STANDARD 99)

project(game_of_life)

add_executable(imageloader
        imageloadertester.c
        imageloader.h
        imageloader.c
)

add_executable(steganography
        imageloader.c
        imageloader.h
        steganography.c
)
