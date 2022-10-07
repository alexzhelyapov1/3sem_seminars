all: prepare

.PHONY: prepare clean

out_thread_to_console: prepare out_thread_to_console.cpp
	g++ out_thread_to_console.cpp -pthread -o ./build/out_thread_to_console.out
	./build/out_thread_to_console.out

new_thread: prepare new_thread.cpp
	g++ new_thread.cpp -pthread -o ./build/new_thread.out
	./build/new_thread.out
	
five_threads: prepare five_threads.cpp
	g++ five_threads.cpp -pthread -o ./build/five_threads.out -O0
	./build/five_threads.out

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