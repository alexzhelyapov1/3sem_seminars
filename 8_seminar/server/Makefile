
all: prepare

.PHONY: prepare clean

1_empty_msgs: prepare 1_empty_msgs.cpp
	g++ 1_empty_msgs.cpp -pthread -o ./build/1_empty_msgs.out
	./build/1_empty_msgs.out

2_empty_msgs: prepare 2_empty_msgs.cpp
	g++ 2_empty_msgs.cpp -pthread -o ./build/2_empty_msgs.out
	./build/2_empty_msgs.out

1hello: prepare 1hello.cpp
	g++ 1hello.cpp -pthread -o ./build/1hello.out
	./build/1hello.out

2hello: prepare 2hello.cpp
	g++ 2hello.cpp -pthread -o ./build/2hello.out
	./build/2hello.out

1sync: prepare 1sync.cpp
	g++ 1sync.cpp -pthread -o ./build/1sync.out
	./build/1sync.out

2sync: prepare 2sync.cpp
	g++ 2sync.cpp -pthread -o ./build/2sync.out
	./build/2sync.out

prepare:
	mkdir -p build

clean:
	rm -rf build