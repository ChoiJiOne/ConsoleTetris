CC=g++
STD=-std=c++17

build:
	$(CC) $(STD) Source/*.cpp -o ConsoleTetris.out

clean:
	rm -f ConsoleTetris.out
