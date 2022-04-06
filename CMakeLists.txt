cmake_minimum_required(VERSION 3.0)

project(tetris1.0)

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