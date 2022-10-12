all: prepare

.PHONY: prepare clean

1_shared_memory: prepare 1_shared_memory.cpp
	g++ 1_shared_memory.cpp -pthread -o ./build/1_shared_memory.out -O0
	./build/1_shared_memory.out
2_shared_memory: prepare 2_shared_memory.cpp
	g++ 2_shared_memory.cpp -pthread -o ./build/2_shared_memory.out -O0
	./build/2_shared_memory.out
rm_shm: prepare rm_shm.cpp
	g++ rm_shm.cpp -pthread -o ./build/rm_shm.out -O0
	./build/rm_shm.out

prepare:
	mkdir -p build

clean:
	rm -rf build