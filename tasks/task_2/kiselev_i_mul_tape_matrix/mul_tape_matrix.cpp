// Copyright 2023 Kiselev Igor
#include "task_2/kiselev_i_mul_tape_matrix/mul_tape_matrix.h"

std::vector<int> SeqMulMatrix(const std::vector<int> &a, const std::vector<int> &b, int n, int m) {
    std::vector<int> resMatrix(n * n);

    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < m; k++) {
                resMatrix[j * n + i] += a[j * m + k] * b[k * n + i];
            }
        }
    }
    return resMatrix;
}
std::vector<int> ParMulMatrix(std::vector<int> *SMM, std::vector<int> *PMM, int n, int m) {
    std::vector<int> &a = *SMM;
    std::vector<int> &b = *PMM;

    int sizeProc = 0;
    int rankProc = 0;
    MPI_Comm_size(MPI_COMM_WORLD, &sizeProc);
    MPI_Comm_rank(MPI_COMM_WORLD, &rankProc);

    int chain_s = n / sizeProc;
    int reminder = n % sizeProc;

    if (rankProc == 0) {
        for (int proc = 1; proc < sizeProc; proc++) {
            int chain_vecA = proc * chain_s * m;
            int chain_vecB = proc * chain_s;

            if (reminder != 0) {
                chain_vecA += reminder * m;
                chain_vecB += reminder;
            }

            std::vector<int> sendB(chain_s * m, 0);
            for (int i = 0; i < sendB.size(); i++) {
                int row = i % chain_s;
                int col = (i / chain_s) * n;

                sendB[i] =
                    b[chain_vecB + row + col];
            }

            MPI_Send(a.data() + chain_vecA,
                chain_s * m,
                MPI_INT, proc, 1, MPI_COMM_WORLD);
            MPI_Send(sendB.data(), sendB.size(),
                MPI_INT, proc, 2, MPI_COMM_WORLD);
        }
    }
    int locSize = (chain_s + reminder) * m;

    std::vector<int> locVecA(locSize, 0);
    std::vector<int> locVecB(locSize + 1, 0);

    if (rankProc == 0) {
        for (int i = 0; i < locSize; i++) {
            int row = i % (chain_s + reminder);
            int col = (i / (chain_s + reminder)) * n;
            locVecB[i] = b[row + col];
            locVecA[i] = a[i];
        }
    } else {
        MPI_Status status;
        MPI_Recv(locVecA.data(), static_cast<int>(
            locSize - reminder * m),
            MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
        MPI_Recv(locVecB.data(), static_cast<int>(
            locSize - reminder * m),
            MPI_INT, 0, 2, MPI_COMM_WORLD, &status);
    }
    locVecB[locSize] = rankProc == 0 ? 0 : rankProc * chain_s + reminder;

    std::vector<int> locRes(n * n, 0);

    int snd = (rankProc + 1) % sizeProc;
    int recv = (rankProc - 1) < 0 ? sizeProc - 1 : rankProc - 1;

    for (int i = 0; i < sizeProc; i++) {
        int locRow =
            rankProc == 0 ? chain_s + reminder : chain_s;
        int locCol =
            (rankProc + i) % sizeProc == 0 ? chain_s + reminder : chain_s;

        std::vector<int> tmpRes =
            SeqMulMatrix(locVecA, locVecB,
            locRow, locCol);

        int chainA = rankProc == 0 ? 0 :
            (rankProc * chain_s + reminder) * n;
        for (int j = 0; j < tmpRes.size(); j++) {
            int row =
                locVecB[locSize] + j % locRow;
            int col =
                (j / locRow) * n;

            locRes[chainA + row + col] += tmpRes[j];
        }

        MPI_Send(locVecB.data(), static_cast<int>(locVecB.size()),
            MPI_INT, recv, i, MPI_COMM_WORLD);

        MPI_Status status;
        MPI_Recv(locVecB.data(), static_cast<int>(locVecB.size()),
            MPI_INT, snd, i, MPI_COMM_WORLD, &status);
    }

    std::vector<int> resMatrix(n * n, 0);
    MPI_Reduce(locRes.data(), resMatrix.data(), static_cast<int>(locRes.size()),
        MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    return resMatrix;
}
// kiselev_i
