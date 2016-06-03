CC=g++
CFLAGS= -fopenmp -O3 -ltgui -lsfml-graphics -lsfml-window -lsfml-system
all: distance.o color.o noise_generator.o
	$(CC) -Wall -std=c++11 $(CFLAGS) distance.o color.o noise_generator.o main.cpp -o noiseMaker
clean:
	rm noiseMaker
	rm -rf *.o

noise_generator.o: distance.o color.o
	$(CC) -fopenmp -Ofast -Wall -std=c++11 -c noise_generator.cpp

distance.o:
	$(CC) -fopenmp -Ofast -Wall -std=c++11 -c distance.cpp
color.o:
	$(CC) -fopenmp -Ofast -Wall -std=c++11 -c color.cpp
