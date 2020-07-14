CC=g++
CFLAGS = -g -Wall -std=c++17
INCLUDE = -I AudioFile.h
default:
	$(CC) $(INCLUDE) $(CFLAGS) main.cpp -o main.o
clean:
	rm -f main.o
