cmake_minimum_required(VERSION 3.21)
project(MetroMondego C)

set(CMAKE_C_STANDARD 11)

add_executable(MetroMondego
        Main.c
        Paragens.c
        Linhas.c
        data.c
        )
