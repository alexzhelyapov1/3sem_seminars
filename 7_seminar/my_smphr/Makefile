all: prepare

.PHONY: prepare clean

smphr: prepare smphr.cpp
	g++ smphr.cpp -pthread -o ./build/smphr.out
	./build/smphr.out

prepare:
	mkdir -p build

clean:
	rm -rf build