#include <cstdio>
#include <cstdlib>
#include <valarray>
#include <fstream>
using namespace std;

// This is the header file of solver class
#include "solver.h"

void solve_psd(const char* matrix_file, const char* b_file, const char* x_file) {
  coo_matrix psd;
  psd.read_coo_matrix(matrix_file);
  
  valarray<double> x(psd.n);
  valarray<double> b(psd.n);

  // Read in b
  ifstream ifs_b(b_file);
  for (int i = 0; i < psd.n; ++i) {
    ifs_b >> b[i];
  }
  ifs_b.close();

  // Solve the linear system
  psd.solve(b, x);

  // Save the final solution x in a file
  ofstream ofs_x(x_file);
  for (int i = 0; i < psd.n; ++i) {
    ofs_x << x[i] << endl;
  }
  ofs_x.close();
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " matrix_file b_file x_file" << endl;
        return 1;
}

    const char* matrix_file = argv[1];
    const char* b_file = argv[2];
    const char* x_file = argv[3];

    solve_psd(matrix_file, b_file, x_file);
    return 0;
}