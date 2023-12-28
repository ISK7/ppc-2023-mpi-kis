//#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include <mpi.h>
#include "mul_tape_matrix.h"

/*TEST(MulMatrix_test, test_3x3_of_1) {
    int rankProc = 0;
    int sizeProc = 0;
    int n = 3;

    MPI_Comm_rank(MPI_COMM_WORLD, &rankProc);
    MPI_Comm_size(MPI_COMM_WORLD, &sizeProc);

    std::vector<int> vecA{1, 1, 1, 1, 1, 1, 1, 1, 1};
    std::vector<int> vecB{1, 1, 1, 1, 1, 1, 1, 1, 1};

    std::vector<int> resSeq = SeqMulMatrix(A, B, n, n);

    if (rankProc == 0) {
        std::vector<int> resPar = ParMulMatrix(&A, &B, n, n);
        ASSERT_EQ(resPar, resSeq);
    }
}

TEST(MulMatrix_test, test_3x3_of_progression) {
    int rankProc = 0;
    int sizeProc = 0;
    int n = 3;

    MPI_Comm_rank(MPI_COMM_WORLD, &rankProc);
    MPI_Comm_size(MPI_COMM_WORLD, &sizeProc);
    std::vector<int> vecA(n * n);
    std::vector<int> vecB(n * n);
    for (int i = 0; i < n * n; i++) {
        vecA[i] = i;
        vecB[i] = i;
    }

    std::vector<int> resSeq = SeqMulMatrix(A, B, n, n);

    if (rankProc == 0) {
        std::vector<int> resPar = ParMulMatrix(&A, &B, n, n);
        ASSERT_EQ(resPar, resSeq);
    }
}

TEST(MulMatrix_test, test_3x4_and_4x3_of_1) {
    int rankProc = 0;
    int sizeProc = 0;
    int n = 3;
    int m = 4;

    MPI_Comm_rank(MPI_COMM_WORLD, &rankProc);
    MPI_Comm_size(MPI_COMM_WORLD, &sizeProc);

    std::vector<int> vecA{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    std::vector<int> vecB{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

    std::vector<int> resSeq = SeqMulMatrix(A, B, n, m);

    if (rankProc == 0) {
        std::vector<int> resPar = ParMulMatrix(&A, &B, n, m);
        ASSERT_EQ(resPar, resSeq);
    }
}

TEST(MulMatrix_test, test_3x4_and_4x3_of_progression) {
    int rankProc = 0;
    int sizeProc = 0;
    int n = 3;
    int m = 4;

    MPI_Comm_rank(MPI_COMM_WORLD, &rankProc);
    MPI_Comm_size(MPI_COMM_WORLD, &sizeProc);
    std::vector<int> vecA(n * m);
    std::vector<int> vecB(n * m);
    for (int i = 0; i < n * m; i++) {
        vecA[i] = i;
        vecB[i] = i;
    }

    std::vector<int> resSeq = SeqMulMatrix(A, B, n, m);

    if (rankProc == 0) {
        std::vector<int> resPar = ParMulMatrix(&A, &B, n, m);
        ASSERT_EQ(resPar, resSeq);
    }
}

TEST(MulMatrix_test, test_4x8_and_8x4_of_random) {
    int rankProc = 0;
    int sizeProc = 0;
    int n = 4;
    int m = 8;

    MPI_Comm_rank(MPI_COMM_WORLD, &rankProc);
    MPI_Comm_size(MPI_COMM_WORLD, &sizeProc);
    std::vector<int> vecA(n * m);
    std::vector<int> vecB(n * m);
    for (int i = 0; i < n * m; i++) {
        vecA[i] = std::rand() % 10;
        vecB[i] = std::rand() % 10;
    }

    std::vector<int> resSeq = SeqMulMatrix(A, B, n, m);

    if (rankProc == 0) {
        std::vector<int> resPar = ParMulMatrix(&A, &B, n, m);
        ASSERT_EQ(resPar, resSeq);
    }
}

TEST(MulMatrix_test, test_10x10_of_random) {
    int rankProc = 0;
    int sizeProc = 0;
    int n = 10;

    MPI_Comm_rank(MPI_COMM_WORLD, &rankProc);
    MPI_Comm_size(MPI_COMM_WORLD, &sizeProc);
    std::vector<int> vecA(n * n);
    std::vector<int> vecB(n * n);
    for (int i = 0; i < n * n; i++) {
        vecA[i] = std::rand() % 10;
        vecB[i] = std::rand() % 10;
    }

    std::vector<int> resSeq = SeqMulMatrix(A, B, n, n);

    if (rankProc == 0) {
        std::vector<int> resPar = ParMulMatrix(&A, &B, n, n);
        ASSERT_EQ(resPar, resSeq);
    }
}*/

int main(int argc, char** argv) {
    int result = 0;

    //::testing::InitGoogleTest(&argc, argv);
    //::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners();

    if (MPI_Init(&argc, &argv) != MPI_SUCCESS)
        MPI_Abort(MPI_COMM_WORLD, -1);

    std::cout << "\n";
    int n = 3, m = 3;
    std::vector<int> A(n * m), B(n * m);

    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            A[i * m + j] = i;
        }
    }
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            B[i * n + j] = i;
        }
    }

    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            std::cout << A[i * m + j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            std::cout << B[i * n + j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";

    //std::vector<int> tstA{};
    //std::vector<int> tstB{};
    std::vector<int> resSeq = SeqMulMatrix(A, B, n, m);
    std::vector<int> resPar = ParMulMatrix(&A, &B, n, m);

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            std::cout << resSeq[i * n + j] << " ";
        }
        std::cout << "| ";
        for (int j = 0; j < n; j++){
            std::cout << resPar[i * n + j] << " ";
        }
        std::cout << "\n";
    }

    //result = RUN_ALL_TESTS();
    MPI_Finalize();

    return result;
}
