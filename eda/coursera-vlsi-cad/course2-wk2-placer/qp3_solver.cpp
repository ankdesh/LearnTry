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

void genConnMatrix(const std::vector<Gate>& gates, const std::vector<Net>& nets, int G, std::vector<std::vector<int>>& C) {
    // Resize the matrix to be G x G
    C.resize(G);
    for (auto& row : C) {
        row.assign(G, 0);
    }

    // Iterate through each net and mark connections between gates
    for (const auto& net : nets) {
        if (net.connectedGates.size() < 2) continue; // A net must connect at least two gates

        for (size_t i = 0; i < net.connectedGates.size(); ++i) {
            for (size_t j = i + 1; j < net.connectedGates.size(); ++j) {
                int gateID1 = net.connectedGates[i];
                int gateID2 = net.connectedGates[j];

                if (gateID1 >= 1 && gateID1 <= G && gateID2 >= 1 && gateID2 <= G) { // Ensure IDs are within valid range
                    C[gateID1 - 1][gateID2 - 1] = 1;
                    C[gateID2 - 1][gateID1 - 1] = 1; // Since the matrix is symmetrical
                }
            }
        }
    }
}

/**
 * Checks if a given matrix is symmetrical and has all diagonal elements set to zero.
 * @param matrix The matrix to check.
 * @throw std::runtime_error if the matrix is not symmetrical or diagonal elements are not zero.
 */
void checkSymmetryAndDiagonals(const std::vector<std::vector<int>>& matrix) {
    int n = matrix.size();
    if (n == 0 || any_of(matrix.begin(), matrix.end(), [&](const auto& row){ return row.size() != n; })) {
        throw std::runtime_error("Matrix is not square");
    }

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (matrix[i][j] != matrix[j][i]) {
                throw std::runtime_error("Matrix is not symmetrical");
            }
            if (i == j && matrix[i][j] != 0) {
                throw std::runtime_error("Diagonal elements are not zero");
            }
        }
    }
}

/**
 * Generates a vector of nets based on the given gates and the number of nets.
 * @param gates Reference to the vector of gates.
 * @param N The total number of nets in the design.
 * @param nets Reference to the vector where the nets will be stored.
 */
void genNetVector(const std::vector<Gate>& gates, const int N, std::vector<Net>& nets) {
    nets.resize(N);

    for (int i = 0; i < N; ++i) {
        nets[i].netID = i + 1; // Adjusting index to be 1-based
        nets[i].connectedGates.clear();
    }

    for (const auto& gate : gates) {
        for (int netID : gate.connectedNets) {
            if (netID >= 1 && netID <= N) { // Ensure netID is within the valid range
                nets[netID - 1].connectedGates.push_back(gate.gateID);
            }
        }
    }
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

    // Declare vectors to store gates and pads
    std::vector<Gate> gates;
    std::vector<Pad> pads;

    // Variable to store the number of nets
    int N;

    // Read input data from the specified file
    readInputFile(inputFilename, gates, pads, N) ;

    // Print the read values in a readable format on the screen
    std::cout << "Number of Gates (G): " << gates.size() << std::endl;
    for (const auto& gate : gates) {
        std::cout << "Gate ID: " << gate.gateID << ", Connected Nets: ";
        for (int netID : gate.connectedNets) {
            std::cout << netID << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Number of Pads (P): " << pads.size() << std::endl;
    for (const auto& pad : pads) {
        std::cout << "Pad ID: " << pad.padID << ", Net ID: " << pad.netID
                  << ", Position: (" << pad.x << ", " << pad.y << ")" << std::endl;
    }

    std::cout << "Number of Nets (N): " << N << std::endl;

    // Declare a vector to store nets
    std::vector<Net> nets;

    // Generate the net vector based on the gates and number of nets
    genNetVector(gates, N, nets);

    // Open the output file for writing
    std::ofstream outputFile(outputFilename);
    if (!outputFile) {
        std::cerr << "Error opening output file: " << outputFilename << std::endl;
        return 1; // Return error if output file cannot be opened
    }

    // Example output to verify the data was read and processed correctly
    for (const auto& net : nets) {
        outputFile << net.netID << " ";
        for (int gateID : net.connectedGates) {
            outputFile << gateID << " ";
        }
        outputFile << std::endl;
    }
}

