all: bellmanford_driver floydwarshall_driver

bellmanford_driver: driver/bellmanford_driver.cpp src/bellmanford.cpp ../individual_csr/individual_csr.cpp
	g++ -O3 -I ../individual_csr driver/bellmanford_driver.cpp src/bellmanford.cpp ../individual_csr/individual_csr.cpp -o driver/bellmanford_driver.exe

floydwarshall_driver: driver/floydwarshall_driver.cpp src/floydwarshall.cpp
	g++ -O3 driver/floydwarshall_driver.cpp src/floydwarshall.cpp -o driver/floydwarshall_driver.exe

run: all
	cd driver && ./bellmanford_driver.exe ../tests/bf_sample_input.txt > ../outputs/bf_sample_output.txt
	cd driver && ./floydwarshall_driver.exe ../tests/fw_sample_input.txt > ../outputs/fw_sample_output.txt

show:
	cat outputs/bf_sample_output.txt
	cat outputs/fw_sample_output.txt

clean:
	rm -f driver/bellmanford_driver.exe driver/floydwarshall_driver.exe
	rm -f driver/*_sample_output.txt

.PHONY: run clean show all