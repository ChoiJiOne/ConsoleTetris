@echo off

echo start build...
SET option=%1

if not exist ConsoleTetris (
    echo generate visual studio solution...
    Bin\\premake5.exe vs2019
)

msbuild.exe ConsoleTetris\ConsoleTetris.sln -property:Configuration=%option% -target:Rebuild