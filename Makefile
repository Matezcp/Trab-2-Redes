all:
	mkdir -p bin
	g++ src/physical.cpp src/link.cpp src/application.cpp src/main.cpp -o bin/trab
run:
	./bin/trab
