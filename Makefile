all:
	g++ src/main.c $(shell pkg-config sdl2 --cflags --libs --static) -static -o build/main

clean:
	rm build -rf
	mkdir build