all: compile run

compile:
	g++ -O3 individual_wrapper.cpp -o individual_wrapper.exe

run: compile
	./individual_wrapper.exe

clean:
	rm -f individual_wrapper.exe Assignment_01/driver/*.exe Assignment_02/driver/*.exe
	rm -f Assignment_01/outputs/*_output_*.txt Assignment_01/outputs/gemm_*_out.txt
	rm -f Assignment_02/outputs/bf_out_*.txt Assignment_02/outputs/fw_out_*.txt

.PHONY: all compile run clean