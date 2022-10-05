all: global

1:
	touch 1.out 1.fifo
	rm 1.out *fifo
	g++ chat_first_user.cpp -o ./1.out
	./1.out

2:
	# touch 2.out 1.fifo
	# rm 2.out *fifo
	g++ chat_second_user.cpp -o ./2.out
	./2.out

new:
	# touch new.out 1.fifo
	# rm new.out *fifo
	g++ new_chat.cpp -o ./new.out
	./new.out


global:
	touch 2.out 1.fifo
	rm 2.out *fifo
	g++ chat_second_user.cpp -o ./2.out
	./2.out