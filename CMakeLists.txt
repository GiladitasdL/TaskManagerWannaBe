
cmake_minimum_required(VERSION 3.13.4)

project(TaskManagerWannaBe) 

set(CMAKE_CXX_STANDARD 11)
set(DCMAKE_TOOLCHAIN_FILE "D:/storage/pcsource/myrepositories/projects/programing/libraries/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

add_executable(${PROJECT_NAME} src/main.cpp)

#name.h .code
#para name.cpp #include "name.h"
#add_library(oneName name.cpp)