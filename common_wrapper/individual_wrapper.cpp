#include <iostream>
#include <cstdlib>
#include <cstring>

// Helper to execute system commands
void run_cmd(const char* cmd) {
    std::cout << "[INDIVIDUAL WRAPPER] Executing: " << cmd << std::endl;
    int ret = std::system(cmd);
    if (ret != 0) {
        std::cerr << "[WRAPPER ERROR] Command failed with code " << ret << std::endl;
    }
}

int main() {
    std::cout << "  INDIVIDUAL TASK: CSR GRAPH WRAPPER    " << std::endl;

    // Compile the Individual CSR Driver
    std::cout << "\n[1/3] Compiling csr_test_driver..." << std::endl;
    #ifdef _WIN32
        run_cmd("g++ -O3 -I Assignment_01\\src Assignment_01\\driver\\csr_test_driver.cpp Assignment_01\\src\\csr_graph.cpp -o Assignment_01\\driver\\csr_test_driver.exe");
    #else
        run_cmd("g++ -O3 -I Assignment_01/src Assignment_01/driver/csr_test_driver.cpp Assignment_01/src/csr_graph.cpp -o Assignment_01/driver/csr_test_driver.exe");
    #endif

    // Execute from inside the driver directory (so relative paths like ../tests/ work smoothly)
    std::cout << "\n[2/3] Running CSR Driver..." << std::endl;
    #ifdef _WIN32
        run_cmd("cd Assignment_01\\driver && .\\csr_test_driver.exe");
    #else
        run_cmd("cd Assignment_01/driver && ./csr_test_driver.exe");
    #endif

    // Ensure output file is duplicated/renamed to outputs/csr_output.txt if needed
    std::cout << "\n[3/3] Finalizing output file..." << std::endl;
    #ifdef _WIN32
        run_cmd("if exist Assignment_01\\outputs\\input_out.txt copy /Y Assignment_01\\outputs\\input_out.txt Assignment_01\\outputs\\csr_output.txt");
    #else
        run_cmd("cp Assignment_01/outputs/input_out.txt Assignment_01/outputs/csr_output.txt 2>/dev/null || true");
    #endif

    std::cout << "  INDIVIDUAL TASK EXECUTED SUCCESSFULLY! " << std::endl;

    return 0;
}