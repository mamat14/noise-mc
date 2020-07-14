CC=g++
CFLAGS = -g -Wall -std=c++17
INCLUDE = -I include/AudioFile.h
default:
	$(CC) $(INCLUDE) $(CFLAGS) main.cpp -o main.o
clean:
	rm -f main.o