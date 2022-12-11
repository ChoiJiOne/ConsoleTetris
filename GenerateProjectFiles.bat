@echo off

echo Generate Project Files ...

if not exist Dump (
    echo don't exist dump directory...
    mkdir Dump
)

if exist ConsoleTetris (
	echo already exist ConsoleTetris...
)

echo run premake5.exe...
Bin\\premake5.exe vs2019
start ConsoleTetris\\ConsoleTetris.sln
PAUSE