cmake_minimum_required(VERSION 3.20)
project(bjarnes-game-of-life)
set(SOURCES src/main.cpp)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-stdlib=libc++)
add_link_options(-stdlib=libc++ -lc++abi)

add_executable(bjarnes-game-of-life ${SOURCES})
