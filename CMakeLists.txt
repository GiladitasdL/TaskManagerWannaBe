cmake_minimum_required(VERSION 3.30.3)

set(CMAKE_TOOLCHAIN_FILE "C:/tools/vcpkg/scripts/buildsystems/vcpkg.cmake")

#set(CMAKE_PREFIX_PATH "C:/tools/vcpkg/installed/x64-windows")

# include_directories("${CMAKE_PREFIX_PATH}/include")

project(TaskManagerWannaBe)
include(CTest)
enable_testing()

find_package(glad CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(gl3w CONFIG REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE glad::glad imgui::imgui glfw unofficial::gl3w::gl3w)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

#name.h .code
#para name.cpp #include "name.h"
#add_library(oneName name.cpp)