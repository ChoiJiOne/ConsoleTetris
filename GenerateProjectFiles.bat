@echo off

echo Generate Project Files ...

if exist tetris1.0 (
	echo Remove Legacy Folder
	rmdir /s /q tetris1.0
)

mkdir tetris1.0
premake5.exe vs2019
popd tetris1.0
PAUSE