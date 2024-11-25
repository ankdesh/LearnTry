#include "qp3_solver.h"
#include <fstream>
#include <algorithm>

void genConnMatrix(const std::vector<Gate>& gates, const std::vector<Net>& nets, int G, std::vector<std::vector<double>>& C) {
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

void checkSymmetryAndDiagonals(const std::vector<std::vector<double>>& matrix) {
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

void genMatrixA(const std::vector<std::vector<double>>& C, const std::vector<Pad>& pads, const std::vector<Net>& nets, std::vector<std::vector<double>>& A) {
    int G = C.size();
    A.resize(G, std::vector<double>(G, 0));

    // Step 1: Add all elements of the row and put the sum in diagonal element of the row
    for (int i = 0; i < G; ++i) {
        int sum = std::accumulate(C[i].begin(), C[i].end(), 0);
        A[i][i] = sum;
    }

    // Step 2: Negate all the non-diagonal entries
    for (int i = 0; i < G; ++i) {
        for (int j = 0; j < G; ++j) {
            if (i != j) {
                A[i][j] = -C[i][j];
            }
        }
    }

    // Step 3: Go through the pads and add 1 to diagonal elements of row corresponding to the connected gates
    for (const auto& pad : pads) {
        int netID = pad.netID;
        if (netID >= 1) { // Ensure netID is within the valid range
            const auto& net = nets[netID - 1];
            for (int gateID : net.connectedGates) {
                if (gateID >= 1 && gateID <= G) { // Ensure gateID is within the valid range
                    A[gateID - 1][gateID - 1] += 1;
                }
            }
        }
    }
}

void genVectorB(const std::vector<Pad>& pads, const std::vector<Net>& nets, int G, std::vector<double>& vectorBx, std::vector<double>& vectorBy) {
    // Resize vectors to match the number of gates
    vectorBx.resize(G, 0.0);
    vectorBy.resize(G, 0.0);

    // Iterate through each pad and update the vectors
    for (const auto& pad : pads) {
        int netID = pad.netID;
        if (netID >= 1 && netID <= nets.size()) { // Ensure netID is within the valid range
            const auto& net = nets[netID - 1];
            for (int gateID : net.connectedGates) {
                if (gateID >= 1 && gateID <= G) { // Ensure gateID is within the valid range
                    vectorBx[gateID - 1] += pad.x;
                    vectorBy[gateID - 1] += pad.y;
                }
            }
        }
    }
}

void writeMatrixACOO(const std::string& filename, const std::vector<std::vector<double>>& A) {
    int G = A.size();
    if (G == 0 || any_of(A.begin(), A.end(), [&](const auto& row){ return row.size() != G; })) {
        throw std::runtime_error("Matrix is not square");
    }

    // Count the number of non-zero elements
    int nnz = 0;
    for (int i = 0; i < G; ++i) {
        for (int j = 0; j < G; ++j) {
            if (A[i][j] != 0) {
                ++nnz;
            }
        }
    }

    // Open the output file
    std::ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        throw std::runtime_error("Failed to open file for writing");
    }

    // Write the header (n nnz)
    outputFile << G << " " << nnz << "\n";

    // Write the non-zero elements in COO format
    for (int i = 0; i < G; ++i) {
        for (int j = 0; j < G; ++j) {
            if (A[i][j] != 0) {
                outputFile << i << " " << j << " " << A[i][j] << "\n";
            }
        }
    }

    // Close the output file
    outputFile.close();
}