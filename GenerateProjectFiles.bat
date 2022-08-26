@echo off

echo Generate Project Files ...

if exist ConsoleTetris (
	echo Remove Legacy Folder
	rmdir /s /q ConsoleTetris
)

mkdir ConsoleTetris
Bin\\premake5.exe vs2019
PAUSE
