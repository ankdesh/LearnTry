#include <vector>
#include <algorithm>
#include <iostream>

// Define a structure to hold gate information
struct Gate {
    int x;
    int y;
};

// Function to sort gates based on X coordinate, then Y coordinate if X coordinates are equal
bool compareGates(const Gate& a, const Gate& b) {
    if (a.x == b.x) return a.y < b.y;
    return a.x < b.x;
}

// Function to assign gates to left and right partitions
void assignGatesToPartitions(std::vector<Gate>& gates, std::vector<int>& leftPartition, std::vector<int>& rightPartition) {
    int n = gates.size();
    if (n % 2 == 0) {
        leftPartition.assign(gates.begin(), gates.begin() + n / 2);
        rightPartition.assign(gates.begin() + n / 2, gates.end());
    } else {
        leftPartition.assign(gates.begin(), gates.begin() + n / 2 + 1);
        rightPartition.assign(gates.begin() + n / 2 + 1, gates.end());
    }
}

// Example usage
int main() {
    std::vector<Gate> gates = {{3, 5}, {1, 2}, {3, 4}, {2, 3}, {1, 1}};
    
    // Sort the gates
    std::sort(gates.begin(), gates.end(), compareGates);
    
    // Assign gates to left and right partitions
    std::vector<int> leftPartition;
    std::vector<int> rightPartition;
    assignGatesToPartitions(gates, leftPartition, rightPartition);
    
    // Output the results
    for (int gate : leftPartition) {
        std::cout << "Left: " << gate << std::endl;
    }
    for (int gate : rightPartition) {
        std::cout << "Right: " << gate << std::endl;
    }
    
    return 0;
}
