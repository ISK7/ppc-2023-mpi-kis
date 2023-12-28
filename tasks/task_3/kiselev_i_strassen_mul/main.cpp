// Copyright 2023 Kiselev Igor
#include <gtest/gtest.h>
#include "./strassen_mul.h"

TEST(strassen_mul_test, test_2x2_of_1) {
    int rankProc = 0;
    int sizeProc = 0;
    int N = 2;

    MPI_Comm_rank(MPI_COMM_WORLD, &rankProc);
    MPI_Comm_size(MPI_COMM_WORLD, &sizeProc);

    std::vector<std::vector<double>> A = { { 1.0, 1.0 },
        { 1.0, 1.0 } };
    std::vector<std::vector<double>> B = { { 1.0, 1.0 },
        { 1.0, 1.0 } };
    std::vector<std::vector<double>> CSeq(N, std::vector<double>(N));
    CSeq = SeqMulMatrix(A, B, N);

    if (rankProc == 0) {
        std::vector<std::vector<double>> CStr(N, std::vector<double>(N));
        CStr = Strassen(A, B, N);
        ASSERT_EQ(CStr, CSeq);
    }
}

TEST(strassen_mul_test, test_4x4_of_1) {
    int rankProc = 0;
    int sizeProc = 0;
    int N = 4;

    MPI_Comm_rank(MPI_COMM_WORLD, &rankProc);
    MPI_Comm_size(MPI_COMM_WORLD, &sizeProc);

    std::vector<std::vector<double>> A = { { 1.0, 1.0, 1.0, 1.0 },
       { 1.0, 1.0, 1.0, 1.0 },
       { 1.0, 1.0, 1.0, 1.0 },
       { 1.0, 1.0, 1.0, 1.0 } };
    std::vector<std::vector<double>> B = { { 1.0, 1.0, 1.0, 1.0 },
       { 1.0, 1.0, 1.0, 1.0 },
       { 1.0, 1.0, 1.0, 1.0 },
       { 1.0, 1.0, 1.0, 1.0 } };
    std::vector<std::vector<double>> CSeq(N, std::vector<double>(N));
    CSeq = SeqMulMatrix(A, B, N);

    if (rankProc == 0) {
        std::vector<std::vector<double>> CStr(N, std::vector<double>(N));
        CStr = Strassen(A, B, N);
        ASSERT_EQ(CStr, CSeq);
    }
}

TEST(strassen_mul_test, test_4x4_of_progression) {
    int rankProc = 0;
    int sizeProc = 0;
    int N = 4;

    MPI_Comm_rank(MPI_COMM_WORLD, &rankProc);
    MPI_Comm_size(MPI_COMM_WORLD, &sizeProc);

    std::vector<std::vector<double>> A = { { 1.0, 2.0, 3.0, 4.0 },
       { 5.0, 6.0, 7.0, 8.0 },
       { 9.0, 10.0, 11.0, 12.0 },
       { 13.0, 14.0, 15.0, 16.0 } };
    std::vector<std::vector<double>> B = { { 1.0, 2.0, 3.0, 4.0 },
       { 5.0, 6.0, 7.0, 8.0 },
       { 9.0, 10.0, 11.0, 12.0 },
       { 13.0, 14.0, 15.0, 16.0 } };
    std::vector<std::vector<double>> CSeq(N, std::vector<double>(N));
    CSeq = SeqMulMatrix(A, B, N);

    if (rankProc == 0) {
        std::vector<std::vector<double>> CStr(N, std::vector<double>(N));
        CStr = Strassen(A, B, N);
        ASSERT_EQ(CStr, CSeq);
    }
}

TEST(strassen_mul_test, test_4x4_of_random) {
    int rankProc = 0;
    int sizeProc = 0;
    int N = 4;

    MPI_Comm_rank(MPI_COMM_WORLD, &rankProc);
    MPI_Comm_size(MPI_COMM_WORLD, &sizeProc);

    std::vector<std::vector<double>> A = { { 34.0, 54.0, 21.0, 44.0 },
       { 23.0, 45.0, 21.0, 8.0 },
       { 78.0, 33.0, 42.0, 45.0 },
       { 63.0, 73.0, 12.0, 40.0 } };
    std::vector<std::vector<double>> B = { { 64.0, 44.0, 31.0, 35.0 },
       { 86.0, 23.0, 54.0, 67.0 },
       { 85.0, 14.0, 23.0, 54.0 },
       { 76.0, 91.0, 19.0, 34.0 } };

    std::vector<std::vector<double>> CSeq(N, std::vector<double>(N));
    CSeq = SeqMulMatrix(A, B, N);

    if (rankProc == 0) {
        std::vector<std::vector<double>> CStr(N, std::vector<double>(N));
        CStr = Strassen(A, B, N);
        ASSERT_EQ(CStr, CSeq);
    }
}

TEST(strassen_mul_test, test_10x10_of_random) {
    int rankProc = 0;
    int sizeProc = 0;
    int N = 10;

    MPI_Comm_rank(MPI_COMM_WORLD, &rankProc);
    MPI_Comm_size(MPI_COMM_WORLD, &sizeProc);

    std::vector<std::vector<double>> A = { { 6.0, 90.0, 48.0, 21.0, 24.0, 17.0, 53.0, 39.0, 68.0, 86.0 },
        { 24.0, 51.0, 56.0, 20.0, 12.0, 50.0, 34.0, 44.0, 2.0, 54.0 },
        { 93.0, 14.0, 6.0, 22.0, 57.0, 84.0, 45.0, 60.0, 94.0, 25.0 },
        { 43.0, 41.0, 0.0, 86.0, 6.0, 70.0, 51.0, 30.0, 15.0, 58.0 },
        { 59.0, 57.0, 35.0, 49.0, 43.0, 3.0, 19.0, 94.0, 65.0, 63.0 },
        { 13.0, 62.0, 27.0, 37.0, 73.0, 14.0, 61.0, 85.0, 16.0, 59.0 },
        { 71.0, 55.0, 4.0, 66.0, 39.0, 86.0, 32.0, 10.0, 67.0, 96.0 },
        { 3.0, 45.0, 16.0, 49.0, 85.0, 60.0, 47.0, 52.0, 20.0, 57.0 },
        { 3.0, 99.0, 26.0, 68.0, 15.0, 3.0, 59.0, 90.0, 61.0, 73.0 },
        { 10.0, 91.0, 1.0, 80.0, 57.0, 71.0, 55.0, 87.0, 72.0, 63.0 } };
    std::vector<std::vector<double>> B = { { 81.0, 34.0, 14.0, 56.0, 5.0, 95.0, 30.0, 52.0, 23.0, 94.0 },
        { 89.0, 81.0, 29.0, 24.0, 21.0, 9.0, 62.0, 80.0, 80.0, 51.0 },
        { 83.0, 33.0, 85.0, 90.0, 43.0, 91.0, 76.0, 29.0, 58.0, 64.0 },
        { 4.0, 60.0, 75.0, 93.0, 26.0, 33.0, 77.0, 36.0, 81.0, 35.0 },
        { 40.0, 6.0, 40.0, 6.0, 46.0, 12.0, 72.0, 17.0, 66.0, 30.0 },
        { 64.0, 45.0, 74.0, 56.0, 56.0, 18.0, 71.0, 27.0, 10.0, 82.0 },
        { 11.0, 51.0, 15.0, 2.0, 26.0, 19.0, 50.0, 69.0, 30.0, 27.0 },
        { 52.0, 77.0, 15.0, 79.0, 89.0, 97.0, 93.0, 46.0, 74.0, 29.0 },
        { 37.0, 0.0, 3.0, 83.0, 15.0, 49.0, 16.0, 80.0, 26.0, 7.0 },
        { 45.0, 3.0, 74.0, 48.0, 87.0, 45.0, 90.0, 86.0, 5.0, 37.0 } };

    std::vector<std::vector<double>> CSeq(N, std::vector<double>(N));
    CSeq = SeqMulMatrix(A, B, N);

    if (rankProc == 0) {
        std::vector<std::vector<double>> CStr(N, std::vector<double>(N));
        CStr = Strassen(A, B, N);
        ASSERT_EQ(CStr, CSeq);
    }
}

int main(int argc, char **argv) {
    int result = 0;
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners();

    if (MPI_Init(&argc, &argv) != MPI_SUCCESS)
        MPI_Abort(MPI_COMM_WORLD, -1);

    int rankProc;
    MPI_Comm_rank(MPI_COMM_WORLD, &rankProc);

    if (rankProc != 0) {
        delete listeners.Release(listeners.default_result_printer());
    }

    result = RUN_ALL_TESTS();
    MPI_Finalize();
    return 0;
}
