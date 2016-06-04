	CC=g++
CFLAGS= -fopenmp -O3 -Wall -std=c++11

all: distance.o color.o noise_generator.o
	$(CC) $(CFLAGS) -ltgui -lsfml-graphics -lsfml-window -lsfml-system distance.o color.o noise_generator.o main.cpp -o noiseMaker
clean:
	rm noiseMaker
	rm -rf *.o

noise_generator.o: distance.o color.o
	$(CC) $(CFLAGS) -c noise_generator.cpp

distance.o:
	$(CC) $(CFLAGS) -c distance.cpp
color.o:
	$(CC) $(CFLAGS) -c color.cpp
