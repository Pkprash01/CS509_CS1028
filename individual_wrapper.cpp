#include <iostream>
#include <cstdlib>
#include <string>

// Helper to execute system commands safely
void run_cmd(const char* cmd) {
    std::cout << "[WRAPPER] Executing: " << cmd << std::endl;
    int ret = std::system(cmd);
    if (ret != 0) {
        std::cerr << "[WRAPPER ERROR] Command failed with code " << ret << std::endl;
    }
}

void handle_assignment_1() {
    int task_choice = 0;
    std::cout << "\n--- Assignment 1 Menu ---\n";
    std::cout << "1. Run Single CSR Test File\n";
    std::cout << "2. Run Single GEMM Test File\n";
    std::cout << "3. Batch Run ALL Assignment 1 Inputs (CSR & GEMM)\n";
    std::cout << "Select task choice (1-3): ";
    std::cin >> task_choice;

    if (task_choice == 1) {
        std::string filename;
        std::cout << "Enter CSR input filename (e.g., csr_input_10.txt): ";
        std::cin >> filename;

        run_cmd("g++ -O3 -I Assignment_01/src Assignment_01/driver/csr_test_driver.cpp Assignment_01/src/csr_graph.cpp -o Assignment_01/driver/csr_test_driver.exe");
        
        std::string out_name = filename;
        if (out_name.rfind("csr_input_", 0) == 0) {
            out_name.replace(0, 10, "csr_output_");
        } else {
            out_name = "csr_output_" + out_name;
        }

        #ifdef _WIN32
            std::string cmd = "powershell -Command \"cd Assignment_01/driver; ./csr_test_driver.exe ../tests/" + filename + " ../outputs/" + out_name + "\"";
        #else
            std::string cmd = "cd Assignment_01/driver && ./csr_test_driver.exe ../tests/" + filename + " ../outputs/" + out_name;
        #endif

        run_cmd(cmd.c_str());
        std::cout << "CSR task executed successfully! Output saved to Assignment_01/outputs/" << out_name << "\n";

    } else if (task_choice == 2) {
        std::string filename;
        std::cout << "Enter GEMM input filename (e.g., gemm_10.txt): ";
        std::cin >> filename;

        run_cmd("g++ -O3 Assignment_01/driver/gemm_driver.cpp Assignment_01/src/GEMM_simple.cpp Assignment_01/src/GEMM_blocking.cpp -o Assignment_01/driver/gemm_driver.exe");

        std::string out_name = filename;
        if (out_name.rfind("gemm_", 0) == 0) {
            out_name.replace(0, 5, "gemm_");
            size_t dot_pos = out_name.find(".txt");
            if (dot_pos != std::string::npos) {
                out_name.replace(dot_pos, 4, "_out.txt");
            }
        } else {
            out_name = "gemm_output.txt";
        }

        #ifdef _WIN32
            std::string cmd = "powershell -Command \"cd Assignment_01/driver; ./gemm_driver.exe ../tests/" + filename + " > ../outputs/" + out_name + "\"";
        #else
            std::string cmd = "cd Assignment_01/driver && ./gemm_driver.exe ../tests/" + filename + " > ../outputs/" + out_name;
        #endif

        run_cmd(cmd.c_str());
        std::cout << "GEMM task executed successfully! Output saved to Assignment_01/outputs/" << out_name << "\n";

    } else if (task_choice == 3) {
        std::cout << "\n[BATCH] Compiling Assignment 1 Drivers...\n";
        run_cmd("g++ -O3 -I Assignment_01/src Assignment_01/driver/csr_test_driver.cpp Assignment_01/src/csr_graph.cpp -o Assignment_01/driver/csr_test_driver.exe");
        run_cmd("g++ -O3 Assignment_01/driver/gemm_driver.cpp Assignment_01/src/GEMM_simple.cpp Assignment_01/src/GEMM_blocking.cpp -o Assignment_01/driver/gemm_driver.exe");

        std::cout << "\n[BATCH] Running all matching CSR and GEMM test files automatically...\n";
        
        #ifdef _WIN32
            std::string batch_cmd = "powershell -Command \""
                "foreach ($file in Get-ChildItem -Path Assignment_01/tests -Filter 'csr_input_*.txt') { "
                "  $outName = $file.Name -replace 'csr_input_', 'csr_output_'; "
                "  Write-Host 'Running CSR:' $file.Name '->' $outName; "
                "  cd Assignment_01/driver; ./csr_test_driver.exe ('../tests/' + $file.Name) ('../outputs/' + $outName); cd ../..; "
                "}"
                "foreach ($file in Get-ChildItem -Path Assignment_01/tests -Filter 'gemm_*.txt') { "
                "  $outName = $file.Name.Replace('.txt', '_out.txt'); "
                "  Write-Host 'Running GEMM:' $file.Name '->' $outName; "
                "  cd Assignment_01/driver; ./gemm_driver.exe ('../tests/' + $file.Name) | Out-File ('../outputs/' + $outName); cd ../..; "
                "}"
                "\"";
        #else
            std::string batch_cmd = "cd Assignment_01/driver && "
                "for f in ../tests/csr_input_*.txt; do "
                "  base=$(basename $f); "
                "  out=$(echo $base | sed 's/csr_input_/csr_output_/'); "
                "  ./csr_test_driver.exe $f ../outputs/$out; "
                "done; "
                "for f in ../tests/gemm_*.txt; do "
                "  base=$(basename $f); "
                "  out=$(echo $base | sed 's/\\.txt/_out.txt/'); "
                "  ./gemm_driver.exe $f > ../outputs/$out; "
                "done";
        #endif

        run_cmd(batch_cmd.c_str());
        std::cout << "\n[BATCH] All Assignment 1 tasks executed successfully! Check Assignment_01/outputs/ folder.\n";

    } else {
        std::cout << "Invalid task choice for Assignment 1.\n";
    }
}

void handle_assignment_2() {
    int algo_choice = 0;
    std::cout << "\n--- Assignment 2 Menu ---\n";
    std::cout << "1. Run Single Bellman-Ford Test File\n";
    std::cout << "2. Run Single Floyd-Warshall Test File\n";
    std::cout << "3. Batch Run ALL Assignment 2 Inputs (BF & FW)\n";
    std::cout << "Select task choice (1-3): ";
    std::cin >> algo_choice;

    if (algo_choice == 1) {
        std::string filename;
        std::cout << "Enter Bellman-Ford input filename (e.g., bf_1.txt): ";
        std::cin >> filename;

        run_cmd("g++ -O3 -I individual_csr Assignment_02/driver/bellmanford_driver.cpp Assignment_02/src/bellmanford.cpp individual_csr/individual_csr.cpp -o Assignment_02/driver/bellmanford_driver.exe");
        
        std::string out_name = filename;
        if (out_name.rfind("bf_", 0) == 0) {
            out_name.replace(0, 3, "bf_out_");
        } else {
            out_name = "bf_out_" + out_name;
        }

        #ifdef _WIN32
            std::string cmd = "powershell -Command \"cd Assignment_02/driver; ./bellmanford_driver.exe ../tests/" + filename + " > ../outputs/" + out_name + "\"";
        #else
            std::string cmd = "cd Assignment_02/driver && ./bellmanford_driver.exe ../tests/" + filename + " > ../outputs/" + out_name;
        #endif

        run_cmd(cmd.c_str());
        std::cout << "Bellman-Ford executed successfully! Output saved to Assignment_02/outputs/" << out_name << "\n";

    } else if (algo_choice == 2) {
        std::string filename;
        std::cout << "Enter Floyd-Warshall input filename (e.g., fw_1.txt): ";
        std::cin >> filename;

        run_cmd("g++ -O3 Assignment_02/driver/floydwarshall_driver.cpp Assignment_02/src/floydwarshall.cpp -o Assignment_02/driver/floydwarshall_driver.exe");
        
        std::string out_name = filename;
        if (out_name.rfind("fw_", 0) == 0) {
            out_name.replace(0, 3, "fw_out_");
        } else {
            out_name = "fw_out_" + out_name;
        }

        #ifdef _WIN32
            std::string cmd = "powershell -Command \"cd Assignment_02/driver; ./floydwarshall_driver.exe ../tests/" + filename + " > ../outputs/" + out_name + "\"";
        #else
            std::string cmd = "cd Assignment_02/driver && ./floydwarshall_driver.exe ../tests/" + filename + " > ../outputs/" + out_name;
        #endif

        run_cmd(cmd.c_str());
        std::cout << "Floyd-Warshall executed successfully! Output saved to Assignment_02/outputs/" << out_name << "\n";

    } else if (algo_choice == 3) {
        std::cout << "\n[BATCH] Compiling Assignment 2 Drivers...\n";
        run_cmd("g++ -O3 -I individual_csr Assignment_02/driver/bellmanford_driver.cpp Assignment_02/src/bellmanford.cpp individual_csr/individual_csr.cpp -o Assignment_02/driver/bellmanford_driver.exe");
        run_cmd("g++ -O3 Assignment_02/driver/floydwarshall_driver.cpp Assignment_02/src/floydwarshall.cpp -o Assignment_02/driver/floydwarshall_driver.exe");

        std::cout << "\n[BATCH] Running all matching Bellman-Ford and Floyd-Warshall test files automatically...\n";
        
        #ifdef _WIN32
            std::string batch_cmd = "powershell -Command \""
                "foreach ($file in Get-ChildItem -Path Assignment_02/tests -Filter 'bf_*.txt') { "
                "  $outName = $file.Name -replace 'bf_', 'bf_out_'; "
                "  Write-Host 'Running Bellman-Ford:' $file.Name '->' $outName; "
                "  cd Assignment_02/driver; ./bellmanford_driver.exe ('../tests/' + $file.Name) | Out-File ('../outputs/' + $outName); cd ../..; "
                "}"
                "foreach ($file in Get-ChildItem -Path Assignment_02/tests -Filter 'fw_*.txt') { "
                "  $outName = $file.Name -replace 'fw_', 'fw_out_'; "
                "  Write-Host 'Running Floyd-Warshall:' $file.Name '->' $outName; "
                "  cd Assignment_02/driver; ./floydwarshall_driver.exe ('../tests/' + $file.Name) | Out-File ('../outputs/' + $outName); cd ../..; "
                "}"
                "\"";
        #else
            std::string batch_cmd = "cd Assignment_02/driver && "
                "for f in ../tests/bf_*.txt; do "
                "  base=$(basename $f); "
                "  out=$(echo $base | sed 's/bf_/bf_out_/'); "
                "  ./bellmanford_driver.exe $f > ../outputs/$out; "
                "done; "
                "for f in ../tests/fw_*.txt; do "
                "  base=$(basename $f); "
                "  out=$(echo $base | sed 's/fw_/fw_out_/'); "
                "  ./floydwarshall_driver.exe $f > ../outputs/$out; "
                "done";
        #endif

        run_cmd(batch_cmd.c_str());
        std::cout << "\n[BATCH] All Assignment 2 tasks executed successfully! Check Assignment_02/outputs/ folder.\n";

    } else {
        std::cout << "Invalid algorithm choice for Assignment 2.\n";
    }
}

int main() {
    int assignment = 0;
    std::cout << "========================================\n";
    std::cout << "      CS509 INDIVIDUAL TASKS PORTAL     \n";
    std::cout << "========================================\n";
    std::cout << "1. Assignment 1\n";
    std::cout << "2. Assignment 2\n";
    std::cout << "Select Assignment number (1-2): ";

    if (std::cin >> assignment) {
        if (assignment == 1) {
            handle_assignment_1();
        } else if (assignment == 2) {
            handle_assignment_2();
        } else {
            std::cout << "Invalid assignment selection.\n";
        }
    }
    return 0;
}