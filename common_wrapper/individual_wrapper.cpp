#include <iostream>
#include <cstdlib>
#include <string>

// Helper to execute system commands
void run_cmd(const char* cmd) {
    std::cout << "[INDIVIDUAL WRAPPER] Executing: " << cmd << std::endl;
    int ret = std::system(cmd);
    if (ret != 0) {
        std::cerr << "[WRAPPER ERROR] Command failed with code " << ret << std::endl;
    }
}

void run_assignment_1() {
    std::string size;
    std::cout << "\nEnter graph/matrix size for Assignment 1 (e.g., 10, 100, 500, 1000): ";
    std::cin >> size;

    std::cout << "\n=== RUNNING ASSIGNMENT 1 FOR SIZE " << size << " ===" << std::endl;

    // Compile the Individual CSR Driver
    std::cout << "\n[1/3] Compiling csr_test_driver..." << std::endl;
    #ifdef _WIN32
        run_cmd("g++ -O3 -I ..\\Assignment_01\\src ..\\Assignment_01\\driver\\csr_test_driver.cpp ..\\Assignment_01\\src\\csr_graph.cpp -o ..\\Assignment_01\\driver\\csr_test_driver.exe");
    #else
        run_cmd("g++ -O3 -I ../Assignment_01/src ../Assignment_01/driver/csr_test_driver.cpp ../Assignment_01/src/csr_graph.cpp -o ../Assignment_01/driver/csr_test_driver.exe");
    #endif

    // Execute using dynamic size input
    std::cout << "\n[2/3] Running CSR Driver for size " << size << "..." << std::endl;
    #ifdef _WIN32
        std::string cmd = "cd ..\\Assignment_01\\driver && .\\csr_test_driver.exe ..\\tests\\csr_input_" + size + ".txt > ..\\outputs\\csr_output_" + size + ".txt";
        run_cmd(cmd.c_str());
    #else
        std::string cmd = "cd ../Assignment_01/driver && ./csr_test_driver.exe ../tests/csr_input_" + size + ".txt > ../outputs/csr_output_" + size + ".txt";
        run_cmd(cmd.c_str());
    #endif

    std::cout << "  ASSIGNMENT 1 EXECUTED SUCCESSFULLY FOR SIZE " << size << "! " << std::endl;
}

void run_assignment_2() {
    std::string size;
    std::cout << "\nEnter graph size for Assignment 2 (e.g., 10, 100, 10000): ";
    std::cin >> size;

    std::cout << "\n=== RUNNING ASSIGNMENT 2 FOR SIZE " << size << " ===" << std::endl;

    // 1. Bellman-Ford Compilation and Execution
    std::cout << "\n[1/2] Compiling and running Bellman-Ford..." << std::endl;
    #ifdef _WIN32
        run_cmd("g++ -O3 -I ..\\individual_csr ..\\Assignment_02\\driver\\bellmanford_driver.cpp ..\\Assignment_02\\src\\bellmanford.cpp ..\\individual_csr\\individual_csr.cpp -o ..\\Assignment_02\\driver\\bellmanford_driver.exe");
        std::string bf_cmd = "cd ..\\Assignment_02\\driver && .\\bellmanford_driver.exe ..\\tests\\bf_input_" + size + ".txt > ..\\outputs\\bf_output_" + size + ".txt";
        run_cmd(bf_cmd.c_str());
    #else
        run_cmd("g++ -O3 -I ../individual_csr ../Assignment_02/driver/bellmanford_driver.cpp ../Assignment_02/src/bellmanford.cpp ../individual_csr/individual_csr.cpp -o ../Assignment_02/driver/bellmanford_driver.exe");
        std::string bf_cmd = "cd ../Assignment_02/driver && ./bellmanford_driver.exe ../tests/bf_input_" + size + ".txt > ../outputs/bf_output_" + size + ".txt";
        run_cmd(bf_cmd.c_str());
    #endif

    // 2. Floyd-Warshall Compilation and Execution
    std::cout << "\n[2/2] Compiling and running Floyd-Warshall..." << std::endl;
    #ifdef _WIN32
        run_cmd("g++ -O3 ..\\Assignment_02\\driver\\floydwarshall_driver.cpp ..\\Assignment_02\\src\\floydwarshall.cpp -o ..\\Assignment_02\\driver\\floydwarshall_driver.exe");
        std::string fw_cmd = "cd ..\\Assignment_02\\driver && .\\floydwarshall_driver.exe ..\\tests\\fw_input_" + size + ".txt > ..\\outputs\\fw_output_" + size + ".txt";
        run_cmd(fw_cmd.c_str());
    #else
        run_cmd("g++ -O3 ../Assignment_02/driver/floydwarshall_driver.cpp ../Assignment_02/src/floydwarshall.cpp -o ../Assignment_02/driver/floydwarshall_driver.exe");
        std::string fw_cmd = "cd ../Assignment_02/driver && ./floydwarshall_driver.exe ../tests/fw_input_" + size + ".txt > ../outputs/fw_output_" + size + ".txt";
        run_cmd(fw_cmd.c_str());
    #endif

    std::cout << "  ASSIGNMENT 2 EXECUTED SUCCESSFULLY FOR SIZE " << size << "! " << std::endl;
}

int main() {
    int choice = 0;
    std::cout << "========================================\n";
    std::cout << "   CS509 - INDIVIDUAL TASKS WRAPPER     \n";
    std::cout << "========================================\n";
    std::cout << "1. Run Assignment 1 (CSR Graph)\n";
    std::cout << "2. Run Assignment 2 (Bellman-Ford & Floyd-Warshall)\n";
    std::cout << "3. Run Both\n";
    std::cout << "Enter your choice (1-3): ";
    
    if (std::cin >> choice) {
        if (choice == 1) {
            run_assignment_1();
        } else if (choice == 2) {
            run_assignment_2();
        } else if (choice == 3) {
            run_assignment_1();
            run_assignment_2();
        } else {
            std::cout << "Invalid choice. Exiting." << std::endl;
        }
    }

    return 0;
}