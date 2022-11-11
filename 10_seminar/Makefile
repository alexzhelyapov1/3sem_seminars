all: prepare

.PHONY: prepare clean

file_attributes: prepare file_attributes.cpp
	g++ file_attributes.cpp -o ./build/file_attributes.out
	./build/file_attributes.out file_attributes.cpp

extend_file: prepare extend_file.cpp
	g++ extend_file.cpp -o ./build/extend_file.out
	./build/extend_file.out ./test_file.txt

links: prepare links.cpp
	g++ links.cpp -o ./build/links.out
	./build/links.out test_file.txt


prepare:
	mkdir -p build

clean:
	rm -rf build