#include <stdio.h>
#include <stdlib.h>

// Function to add two matrices
void addsubM(int n, int A[n][n], int B[n][n], int C[n][n], int s)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j] * s;
        }
    }
}

// Function to multiply two matrices using Strassen's algorithm
void mulM(int n, int A[n][n], int B[n][n], int C[n][n])
{
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int m = n / 2;

    int A11[m][m], A12[m][m], A21[m][m], A22[m][m];
    int B11[m][m], B12[m][m], B21[m][m], B22[m][m];
    int C11[m][m], C12[m][m], C21[m][m], C22[m][m];
    int P1[m][m], P2[m][m], P3[m][m], P4[m][m], P5[m][m], P6[m][m], P7[m][m];
    int tmp1[m][m], tmp2[m][m];

    // Dividing matrices A and B into submatrices
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + m];
            A21[i][j] = A[i + m][j];
            A22[i][j] = A[i + m][j + m];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + m];
            B21[i][j] = B[i + m][j];
            B22[i][j] = B[i + m][j + m];
        }
    }

    // Calculating P1 to P7
    addsubM(m, A11, A22, tmp1, 1);
    addsubM(m, B11, B22, tmp2, 1);
    mulM(m, tmp1, tmp2, P1);

    addsubM(m, A21, A22, tmp1, 1);
    mulM(m, tmp1, B11, P2);

    addsubM(m, B12, B22, tmp1, -1);
    mulM(m, A11, tmp1, P3);

    addsubM(m, B21, B11, tmp1, -1);
    mulM(m, A22, tmp1, P4);

    addsubM(m, A11, A12, tmp1, 1);
    mulM(m, tmp1, B22, P5);

    addsubM(m, A21, A11, tmp1, -1);
    addsubM(m, B11, B12, tmp2, 1);
    mulM(m, tmp1, tmp2, P6);

    addsubM(m, A12, A22, tmp1, -1);
    addsubM(m, B21, B22, tmp2, 1);
    mulM(m, tmp1, tmp2, P7);

    // Calculating submatrices C11, C12, C21, C22
    addsubM(m, P3, P5, tmp1, 1);
    addsubM(m, tmp1, P2, tmp2, -1);
    addsubM(m, tmp2, P4, C11, 1);

    addsubM(m, P1, P2, C12, 1);

    addsubM(m, P3, P4, C21, 1);

    addsubM(m, P1, P5, tmp1, 1);
    addsubM(m, tmp1, P3, tmp2, -1);
    addsubM(m, tmp2, P7, C22, -1);

    // Combining submatrices to form matrix C
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            C[i][j] = C11[i][j];
            C[i][j + m] = C12[i][j];
            C[i + m][j] = C21[i][j];
            C[i + m][j + m] = C22[i][j];
        }
    }
}

int main()
{
    return 0;
}
