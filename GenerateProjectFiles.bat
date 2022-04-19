@echo off

echo Generate Project Files...

if exist tetris1.0 (
	echo remove legacy folder
	rmdir /s /q tetris1.0
)

mkdir tetris1.0
pushd tetris1.0
cmake ..
popd tetris1.0
PAUSE