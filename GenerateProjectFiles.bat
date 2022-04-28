@echo off

echo Generate Project Files ...

if exist ConsoleTetris (
	echo Remove Legacy Folder
	rmdir /s /q tetris1.0
)

mkdir ConsoleTetris
premake5.exe vs2019
PAUSE
