#include <iostream>
#include <cmath>
#include <fstream>


int** createMatrix(int n, int m) {
    int** matrix = new int* [n];
    for (int i = 0; i < n; i++)
        matrix[i] = new int[m];
    return matrix;
}


void deleteMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++)
        delete[] matrix[i];
    delete[] matrix;
}


void fillMatrix(int** matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("matrix[%d, %d] = ", i, j);
            std::cin >> matrix[i][j];
        }
    }
}


bool isSymmetric(int** matrix, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (matrix[i][j] != matrix[j][i])
                return false;
    return true;
}


int** createTransposedMatrix(int** sourceMatrix, int n, int m) {
    int** targetMatrix = createMatrix(m, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            targetMatrix[j][i] = sourceMatrix[i][j];
    return targetMatrix;
}


int** multiply(int** leftMatrix, int** rightMatrix, int n, int p, int m) {
    int** result = createMatrix(n, m);
    for (int i = 0; i < n; i)
        for (int j = 0; j < m; j++) {
            result[i][j] = 0;
            for (int k = 0; k < p; k++) {
                result[i][j] += leftMatrix[i][k] * rightMatrix[k][j];
            }
        }
    return result;
}


double calculateLength(int** g, int** x, int n) {
    int** x_g = multiply(x, g, 1, n, n); // [1][n]
    int** xt = createTransposedMatrix(x, 1, n); // [n][1]
    int** x_g_xt = multiply(x_g, xt, 1, n, 1); // [1][1]

    double length = std::sqrt(x_g_xt[0][0]);

    deleteMatrix(x_g, 1);
    deleteMatrix(xt, n);
    deleteMatrix(x_g_xt, 1);

    return length;
}


void readInputFile(const char* filePath, int& n, int**& g, int**& x) {
    // TODO: enter n, g and x
    g = createMatrix(n, n);
    x = createMatrix(1, n);
}


int main(int argc, char* argv[])
{
    puts("Enter the path to the file: ");
    char* filePath;
    std::cin >> filePath;

    int n;
    int** g;
    int** x;
    readInputFile(filePath, n, g, x);

    if (!isSymmetric(g, n)) {
        puts("Error: matrix G is not symmetric.");
        exit(-1);
    }

    int length = calculateLength(g, x, n);
    printf("Vector X length: %d", length);

    deleteMatrix(g, n);
    deleteMatrix(x, 1);
}