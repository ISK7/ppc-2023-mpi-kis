#ifndef MUL_TAPE_MATRIX
#define MUL_TAPE_MATRIX
#include <vector>
#include <string>
#include <mpi.h>


std::vector<int> SeqMulMatrix(const std::vector<int> &a, const std::vector<int> &b, int n, int m);
std::vector<int> ParMulMatrix(std::vector<int> *a, std::vector<int> *b, int an, int am);
#endif  // MUL_TAPE_MATRIX
