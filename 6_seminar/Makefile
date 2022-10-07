all: prepare

.PHONY: prepare out_thread_to_console new_thread five_threads clean

out_thread_to_console: prepare
	g++ out_thread_to_console.cpp -pthread -o ./build/out_thread_to_console.out
	./build/out_thread_to_console.out

new_thread: prepare
	g++ new_thread.cpp -pthread -o ./build/new_thread.out
	./build/new_thread.out
	
five_threads: prepare
	g++ five_threads.cpp -pthread -o ./build/five_threads.out
	./build/five_threads.out

prepare:
	mkdir -p build

clean:
	rm -rf build