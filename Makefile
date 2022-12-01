CC=g++
STD=-std=c++17
LIB=-lncursesw

build:
	$(CC) $(STD) Source/*.cpp -o ConsoleTetris.out $(LIB)

clean:
	rm -f ConsoleTetris.out
