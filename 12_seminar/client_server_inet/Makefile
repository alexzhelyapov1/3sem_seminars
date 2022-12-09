all: prepare

.PHONY: prepare clean

mmap: prepare mmap.cpp
	g++ mmap.cpp -o ./build/mmap.out
	./build/mmap.out

server: prepare server.cpp
	g++ server.cpp -o ./build/server.out
	./build/server.out

client: prepare client.cpp
	g++ client.cpp -o ./build/client.out
	./build/client.out

prepare:
	mkdir -p build

clean:
	rm -rf build