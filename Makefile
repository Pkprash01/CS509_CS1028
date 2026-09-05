all: compile run

compile:
	g++ -O3 individual_wrapper.cpp -o individual_wrapper.exe

run: compile
	./individual_wrapper.exe

clean:
	rm -f individual_wrapper.exe
	rm -f Assignment_01/driver/*.exe
	rm -f Assignment_02/driver/*.exe
	rm -f Assignment_03/driver/*.exe
	rm -f Assignment_04/driver/*.exe

.PHONY: all compile run clean