all: prepare

.PHONY: prepare clean

1: prepare 1.cpp
	g++ 1.cpp -pthread -o ./build/1.out
	./build/1.out

2: prepare 2.cpp
	g++ 2.cpp -pthread -o ./build/2.out
	./build/2.out

3.1: prepare 3.1.cpp
	g++ 3.1.cpp -pthread -o ./build/3.1.out
	./build/3.1.out

3.2: prepare 3.2.cpp
	g++ 3.2.cpp -pthread -o ./build/3.2.out
	./build/3.2.out


prepare:
	mkdir -p build

clean:
	rm -rf build
	touch env.txt
	rm -f env.txt