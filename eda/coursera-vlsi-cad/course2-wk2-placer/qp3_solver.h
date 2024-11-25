#ifndef QP3_SOLVER_H
#define QP3_SOLVER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <numeric>

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

/**
 * @struct Pad
 * Represents a pad in the design, containing its ID, connected net ID, and position.
 */
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
 */
void readInputFile(const std::string& filename, std::vector<Gate>& gates, std::vector<Pad>& pads, int& N);

/**
 * Generates a connectivity matrix based on the given gates.
 * @param gates Reference to the vector of gates.
 * @param nets Reference to the vector of nets.
 * @param G The number of gates.
 * @param C Reference to the matrix where the connectivity will be stored.
 */
void genConnMatrix(const std::vector<Gate>& gates, const std::vector<Net>& nets, int G, std::vector<std::vector<double>>& C);

/**
 * Checks if a given matrix is symmetrical and has all diagonal elements set to zero.
 * @param matrix The matrix to check.
 * @return true if the matrix is symmetrical and diagonal elements are zero, false otherwise.
 */
void checkSymmetryAndDiagonals(const std::vector<std::vector<double>>& matrix);

/**
 * Generates a vector of nets based on the given gates and the number of nets.
 * @param gates Reference to the vector of gates.
 * @param N The total number of nets in the design.
 * @param nets Reference to the vector where the nets will be stored.
 */
void genNetVector(const std::vector<Gate>& gates, const int N, std::vector<Net>& nets);

/**
 * Generates matrix A from the given connectivity matrix and stores it in the output parameter.
 * @param C Reference to the input connectivity matrix.
 * @param pads Reference to the vector of pads.
 * @param A Reference to the matrix where the result will be stored.
 */
void genMatrixA(const std::vector<std::vector<double>>& C, const std::vector<Pad>& pads, const std::vector<Net>& nets, std::vector<std::vector<double>>& A);

/**
 * Generates vectors vectorB, vectorBx, and vectorBy based on the provided pads.
 * @param pads Reference to the vector of pads.
 * @param nets Reference to the vector of nets.
 * @param G The number of gates.
 * @param vectorBx Reference to the vector that will store the x-coordinate contributions from pads.
 * @param vectorBy Reference to the vector that will store the y-coordinate contributions from pads.
 */
void genVectorB(const std::vector<Pad>& pads, const std::vector<Net>& nets, int G, std::vector<double>& vectorBx, std::vector<double>& vectorBy);

/**
 * Writes matrix A to a file in COO format.
 * @param filename The name of the output file.
 * @param A Reference to the matrix A.
 */
void writeMatrixACOO(const std::string& filename, const std::vector<std::vector<double>>& A);

#endif // QP3_SOLVER_H
