#include <iostream>
#include <fstream>
#include "qp3_solver.h"

/**
 * Reads input from a file and populates the vectors of gates and pads.
 * @param filename The name of the input file.
 * @param gates Reference to the vector where gates will be stored.
 * @param pads Reference to the vector where pads will be stored.
 * @param N Reference to an integer that will store the number of nets.
 * @throw std::runtime_error if the file was not successfully read.
 */
void readInputFile(const std::string& filename, std::vector<Gate>& gates, std::vector<Pad>& pads, int& N) {
    std::ifstream inputFile(filename);
    if (!inputFile) {
        throw std::runtime_error("Error opening file: " + filename);
    }

    int G;
    inputFile >> G >> N;

    gates.resize(G);

    for (int i = 0; i < G; ++i) {
        int gateID, M;  // M is the number of nets connected to each gate
        inputFile >> gateID >> M;
        if (gateID <= 0 || gateID > G) {
            throw std::runtime_error("Invalid gate ID: " + std::to_string(gateID));
        }
        gates[i].gateID = gateID;
        gates[i].connectedNets.resize(M);

        for (int j = 0; j < M; ++j) {
            inputFile >> gates[i].connectedNets[j];
            if (gates[i].connectedNets[j] <= 0 || gates[i].connectedNets[j] > N) {
                throw std::runtime_error("Invalid net ID: " + std::to_string(gates[i].connectedNets[j]));
            }
        }
    }

    int P;
    inputFile >> P;

    pads.resize(P);

    for (int i = 0; i < P; ++i) {
        int padID, netID;
        float x, y;
        inputFile >> padID >> netID >> x >> y;
        if (padID <= 0 || padID > P) {
            throw std::runtime_error("Invalid pad ID: " + std::to_string(padID));
        }
        pads[i] = {padID, netID, x, y};
    }

    inputFile.close();
}

/**
 * Main function to process input and output files.
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 * @return 0 on success, non-zero on failure.
 */
int main(int argc, char* argv[]) {
    // Check if the correct number of command-line arguments are provided
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
        return 1;
    }

    // Extract input and output file names from command-line arguments
    std::string inputFilename = argv[1];
    std::string outputFilename = argv[2];
    std::string outputFilenameA = outputFilename + ".outA";
    std::string outputFilenameBx = outputFilename + ".outBx";
    std::string outputFilenameBy = outputFilename + ".outBy";

    // Declare vectors to store gates and pads
    std::vector<Gate> gates;
    std::vector<Pad> pads;

    // Variable to store the number of nets
    int N;

    // Read input data from the specified file
    readInputFile(inputFilename, gates, pads, N);

    // Declare a vector to store nets
    std::vector<Net> nets;

    // Generate the net vector based on the gates and number of nets
    genNetVector(gates, N, nets);

    // Declare a matrix to store connections between gates
    std::vector<std::vector<double>> C;

    // Generate the connection matrix
    genConnMatrix(gates, nets, gates.size(), C);

    // Check if the connection matrix is symmetrical and diagonal elements are zero
    checkSymmetryAndDiagonals(C);

    // Declare a matrix to store A
    std::vector<std::vector<double>> A;

    // Generate matrix A from the connectivity matrix
    genMatrixA(C, pads, nets, A);

    // Writes matrix A to outputfile in COO format with nnz values
    writeMatrixACOO(outputFilenameA, A);

    // Declare vectors to store Bx and By
    std::vector<double> vectorBx;
    std::vector<double> vectorBy;

    // Generate vectors Bx and By
    genVectorB(pads, nets, gates.size(), vectorBx, vectorBy);

    // Write vector Bx to output file in column format
    {
        std::ofstream outputFile(outputFilenameBx);
        if (!outputFile.is_open()) {
            throw std::runtime_error("Failed to open file for writing");
        }
        for (const auto& value : vectorBx) {
            outputFile << value << "\n";
        }
        outputFile.close();
    }

    // Write vector By to output file in column format
    {
        std::ofstream outputFile(outputFilenameBy);
        if (!outputFile.is_open()) {
            throw std::runtime_error("Failed to open file for writing");
        }
        for (const auto& value : vectorBy) {
            outputFile << value << "\n";
        }
        outputFile.close();
    }

    return 0;
}
