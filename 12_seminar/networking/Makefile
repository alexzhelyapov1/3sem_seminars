all: prepare

.PHONY: prepare clean

mmap: prepare mmap.cpp
	g++ mmap.cpp -o ./build/mmap.out
	./build/mmap.out

prepare:
	mkdir -p build

clean:
	rm -rf build