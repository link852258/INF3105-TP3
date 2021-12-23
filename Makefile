OPTIONS = -O2 -Wall -Wextra -std=c++11    # pour optimiser

all: tp3

tp3: tp3.o
	g++ ${OPTIONS} -o tp3 tp3.o

tp3.o: tp3.cpp
	g++ ${OPTIONS} -c tp3.cpp


