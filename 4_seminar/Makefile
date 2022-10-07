all: clean prepare

.PHONY: prepare clean

chat_first_user: prepare chat_first_user.cpp
	g++ chat_first_user.cpp -pthread -o ./build/chat_first_user.out
	./build/chat_first_user.out

chat_second_user: prepare chat_second_user.cpp
	g++ chat_second_user.cpp -pthread -o ./build/chat_second_user.out
	./build/chat_second_user.out
	
fork_fifo: prepare fork_fifo.cpp
	g++ fork_fifo.cpp -pthread -o ./build/fork_fifo.out
	./build/fork_fifo.out
create_fifo: prepare create_fifo.cpp
	g++ create_fifo.cpp -pthread -o ./build/create_fifo.out
	./build/create_fifo.out

prepare:
	mkdir -p build

clean:
	rm -rf build
	touch aaa.fifo
	rm aaa.fifo