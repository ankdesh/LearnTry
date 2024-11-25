#include <iostream>
#include <fstream>
#include <vector>
#include <string>

void readAndMergeFiles(const std::string& input1, const std::string& input2, const std::string& output) {
    // Open files for reading
    std::ifstream in1(input1);
    std::ifstream in2(input2);
    
    // Check if files are open
    if (!in1.is_open() || !in2.is_open()) {
        std::cerr << "Failed to open one or both input files." << std::endl;
        return;
    }
    
    // Open output file for writing
    std::ofstream out(output);
    
    if (!out.is_open()) {
        std::cerr << "Failed to open output file." << std::endl;
        return;
    }
    
    // Read from input files and merge data
    int row = 1;
    std::string line1, line2;
    while (std::getline(in1, line1) && std::getline(in2, line2)) {
        out << row << " " << line1 << " " << line2 << "\n";
        ++row;
    }
    
    // Close files
    in1.close();
    in2.close();
    out.close();
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file_prefix>" << std::endl;
        return 1;
    }
    
    // Input and output file names
    std::string prefix = argv[1];
    std::string input1 = prefix + ".outx";
    std::string input2 = prefix + ".outy";
    std::string output = prefix + ".mergedout";

    // Read and merge files
    readAndMergeFiles(input1, input2, output);

    std::cout << "Merged file created successfully: " << output << std::endl;

    return 0;
}