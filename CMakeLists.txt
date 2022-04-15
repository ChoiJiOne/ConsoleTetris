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

add_executable(
	tetris1.0 
	Source/Board.cpp
	Source/Board.h
	Source/Common.h
	Source/ConsoleUtil.cpp
	Source/ConsoleUtil.h
	Source/Game.cpp
	Source/Game.h
	Source/GameTimer.cpp
	Source/GameTimer.h
	Source/InputSystem.cpp
	Source/InputSystem.h
	Source/Main.cpp
	Source/MathUtil.cpp
	Source/MathUtil.h
	Source/StringUtil.h
	Source/Tetromino.cpp
	Source/Tetromino.h
)