#include "qp3_solver.h"

bool readInputFile(const std::string& filename, std::vector<Gate>& gates, std::vector<Pad>& pads) {
    std::ifstream inputFile(filename);
    if (!inputFile) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }

    int G, N;
    inputFile >> G >> N;

    gates.resize(G);

    for (int i = 0; i < G; ++i) {
        int gateID, M;
        inputFile >> gateID >> M;
        gates[i].gateID = gateID;
        gates[i].connectedNets.resize(M);

        for (int j = 0; j < M; ++j) {
            inputFile >> gates[i].connectedNets[j];
        }
    }

    int P;
    inputFile >> P;

    pads.resize(P);

    for (int i = 0; i < P; ++i) {
        int padID, netID;
        float x, y;
        inputFile >> padID >> netID >> x >> y;

        pads[i] = {padID, netID, x, y};
    }

    inputFile.close();
    return true;
}

void generateAdjMatrix(std::vector<Gate>& gates, int G, int N, std::vector<std::vector<int>>& C) {
    C.resize(N);
    for (auto& row : C) {
        row.assign(G, 0);
    }

    for (int i = 0; i < G; ++i) {
        for (auto j : gates[i].connectedNets) {
            if (j - 1 >= 0 && j - 1 < N) {
                C[j - 1][i] += 1;
            }
        }
    }
}

bool isSymmetricalAndDiagonalsZero(const std::vector<std::vector<int>>& matrix) {
    int n = matrix.size();
    if (n == 0 || any_of(matrix.begin(), matrix.end(), [&](const auto& row){ return row.size() != n; })) {
        return false;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (matrix[i][j] != matrix[j][i]) {
                return false;
            }
            if (i == j && matrix[i][j] != 0) {
                return false;
            }
        }
    }

    return true;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
        return 1;
    }

    std::string inputFilename = argv[1];
    std::string outputFilename = argv[2];

    std::vector<Gate> gates;
    std::vector<Pad> pads;

    if (!readInputFile(inputFilename, gates, pads)) {
        return 1;
    }

    std::ofstream outputFile(outputFilename);
    if (!outputFile) {
        std::cerr << "Error opening output file: " << outputFilename << std::endl;
        return 1;
    }

    // Example output to verify the data was read correctly
    for (const auto& pad : pads) {
        outputFile << pad.padID << " " << pad.netID << " " << pad.x << " " << pad.y << std::endl;
    }

    return 0;
}