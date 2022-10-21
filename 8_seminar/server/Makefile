
all: prepare

.PHONY: prepare clean

server: prepare server.cpp
	g++ server.cpp -pthread -o ./build/server.out
	./build/server.out

client: prepare client.cpp
	g++ client.cpp -pthread -o ./build/client.out
	./build/client.out

prepare:
	mkdir -p build

clean:
	rm -rf build