CC=g++
STD=-std=c++17
LIB=-lncursesw
SOURCE=Source/*.cpp
OUTPUT=ConsoleTetris.out
DEBUG=-g
WARN=-Wall
OPTIMIZE=-O2
VIEW=-v

debug:
	$(CC) $(STD) $(DEBUG) $(WARN) $(VIEW) $(SOURCE) -o $(OUTPUT) $(LIB)

release:
	$(CC) $(STD) $(OPTIMIZE) $(SOURCE) -o $(OUTPUT) $(LIB)

clean:
	rm -f ConsoleTetris.out
