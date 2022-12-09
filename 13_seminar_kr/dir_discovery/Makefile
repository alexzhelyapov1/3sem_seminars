all: prepare dir_discovery

.PHONY: prepare clean

dir_discovery: prepare dir_discovery.cpp
	g++ dir_discovery.cpp -o ./build/dir_discovery.out
	./build/dir_discovery.out

client: prepare client.cpp
	g++ client.cpp -o ./build/client.out
	./build/client.out

server: prepare server.cpp
	g++ server.cpp -o ./build/server.out
	./build/server.out

prepare:
	mkdir -p build

clean:
	rm -rf build