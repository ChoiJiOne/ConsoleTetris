cmake_minimum_required(VERSION 3.0)

project(tetris1.0)

if(NOT WIN32)
	message(FATAL_ERROR "only supports windows platform.")
endif()

if(NOT MSVC)
	message(FATAL_ERROR "only supports MSVC project currently.")
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB source
    "Source/*.h"
    "Source/*.cpp"
)

add_executable(
	tetris1.0 
	${source}
)
