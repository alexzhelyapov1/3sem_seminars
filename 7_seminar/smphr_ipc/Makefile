all: prepare

.PHONY: prepare clean

rm_shm: prepare rm_shm.cpp
	g++ rm_shm.cpp smphr.cpp -o ./build/rm_shm.out
	./build/rm_shm.out

1: prepare 1.cpp
	g++ 1.cpp smphr.cpp -o ./build/1.out
	./build/1.out

2: prepare 2.cpp
	g++ 2.cpp smphr.cpp -o ./build/2.out
	./build/2.out

prepare:
	mkdir -p build

clean:
	rm -rf build