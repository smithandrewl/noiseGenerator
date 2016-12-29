	CC=g++
CFLAGS= -fopenmp -O3 -Wall -std=c++11

all: distance.o color.o noise_generator.o
	$(CC) $(CFLAGS) main.cpp -ltgui -lsfml-window -lsfml-graphics -lsfml-system distance.o color.o noise_generator.o  -o noiseMaker
clean:
	rm noiseMaker
	rm -rf *.o

noise_generator.o: distance.o color.o
	$(CC) $(CFLAGS) -c noise_generator.cpp

distance.o:
	$(CC) $(CFLAGS) -c distance.cpp
color.o:
	$(CC) $(CFLAGS) -c color.cpp
