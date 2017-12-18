all: adzip

adzip: main.o
	g++ main.o -o adzip

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm -f *.o adzip
