all: prepare

.PHONY: prepare clean

ls: prepare ls.cpp
	g++ ls.cpp -o ./build/ls.out
	./build/ls.out

ls_attributes: prepare ls_attributes.cpp
	g++ ls_attributes.cpp -o ./build/ls_attributes.out
	./build/ls_attributes.out

ls_recursive: prepare ls_recursive.cpp
	g++ ls_recursive.cpp -o ./build/ls_recursive.out
	./build/ls_recursive.out .

prepare:
	mkdir -p build

clean:
	rm -rf build