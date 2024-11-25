#ifndef QP3_SOLVER_H
#define QP3_SOLVER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

/**
 * @struct Gate
 * Represents a gate in the design, containing its ID and connected net IDs.
 */
struct Gate {
    int gateID;            /**< The unique identifier of the gate. */
    std::vector<int> connectedNets;  /**< A vector of net IDs to which the gate is connected. */
};

/**
 * @struct Net
 * Represents a net in the design, containing its ID and the gates it connects.
 */
struct Net {
    int netID;            /**< The unique identifier of the net. */
    std::vector<int> connectedGates;  /**< A vector of gate IDs that are connected to this net. */
};


struct Pad {
    int padID;
    int netID;
    float x, y;
};

/**
 * Reads input from a file and populates the vectors of gates and pads.
 * @param filename The name of the input file.
 * @param gates Reference to the vector where gates will be stored.
 * @param pads Reference to the vector where pads will be stored.
 * @param N Reference to an integer that will store the number of nets.
 * @return true if the file was successfully read, false otherwise.
 */
void readInputFile(const std::string& filename, std::vector<Gate>& gates, std::vector<Pad>& pads,int& N);

/**
 * Generates a connectivity matrix based on the given gates.
 * @param gates Reference to the vector of gates.
 * @param nets Reference to the vector of nets.
 * @param G The number of gates.
 * @param N The number of nets.
 * @param C Reference to the matrix where the connectivity will be stored.
 */
void genConnMatrix(const std::vector<Gate>& gates, const std::vector<Net>& nets, int G, std::vector<std::vector<int>>& C);

/**
 * Checks if a given matrix is symmetrical and has all diagonal elements set to zero.
 * @param matrix The matrix to check.
 * @return true if the matrix is symmetrical and diagonal elements are zero, false otherwise.
 */
void checkSymmetryAndDiagonals(const std::vector<std::vector<int>>& matrix);

/**
 * Generates a vector of nets based on the given gates and the number of nets.
 * @param gates Reference to the vector of gates.
 * @param N The total number of nets in the design.
 * @param nets Reference to the vector where the nets will be stored.
 */
void genNetVector(const std::vector<Gate>& gates, const int N, std::vector<Net>& nets);

#endif // QP3_SOLVER_H
