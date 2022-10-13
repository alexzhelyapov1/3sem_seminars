all: prepare chat

.PHONY: prepare clean

chat: prepare chat.cpp
	g++ chat.cpp -pthread -o ./build/chat.out -O0
	./build/chat.out
rm_shm: prepare rm_shm.cpp
	g++ rm_shm.cpp -pthread -o ./build/rm_shm.out -O0
	./build/rm_shm.out

prepare:
	mkdir -p build

clean:
	rm -rf build