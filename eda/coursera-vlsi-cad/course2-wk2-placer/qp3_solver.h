#ifndef QP3_SOLVER_H
#define QP3_SOLVER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

struct Gate {
    int gateID;
    std::vector<int> connectedNets;
};

struct Pad {
    int padID;
    int netID;
    float x, y;
};

bool readInputFile(const std::string& filename, std::vector<Gate>& gates, std::vector<Pad>& pads);
void generateAdjMatrix(std::vector<Gate>& gates, int G, int N, std::vector<std::vector<int>>& C);
bool isSymmetricalAndDiagonalsZero(const std::vector<std::vector<int>>& matrix);

#endif // QP3_SOLVER_H