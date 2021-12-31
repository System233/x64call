cmake_minimum_required(VERSION 3.21)
project(x64call)
enable_language(ASM_NASM)


add_library(x64call 
        include/x64call.h
        include/x64call
        src/x64call.nasm
)
target_include_directories(x64call PUBLIC include)


add_subdirectory(examples)