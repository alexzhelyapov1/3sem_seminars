all: prepare

.PHONY: prepare clean

out_thread_to_console: prepare out_thread_to_console.cpp
	g++ out_thread_to_console.cpp -pthread -o ./build/out_thread_to_console.out
	./build/out_thread_to_console.out

new_thread: prepare new_thread.cpp
	g++ new_thread.cpp -pthread -o ./build/new_thread.out
	./build/new_thread.out
	
five_threads: prepare five_threads.cpp
	g++ five_threads.cpp -pthread -o ./build/five_threads.out
	./build/five_threads.out

prepare:
	mkdir -p build

clean:
	rm -rf build