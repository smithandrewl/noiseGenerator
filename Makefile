CC=clang++
CFLAGS=-ltgui -lsfml-graphics -lsfml-window -lsfml-system
all:
	$(CC) -Wall -std=c++11 $(CFLAGS) main.cpp -o noiseMaker
clean:
	rm -rf noiseMaker

