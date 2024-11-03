#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Matrix {
private:
    vector<vector<int>> data;
    int size;

public:
    // Constructor to initialize the matrix size
    Matrix(int n) : size(n) {
        data.resize(size, vector<int>(size, 0));
    }

    // Function to load matrix data from a file
    bool loadMatrixFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error opening file: " << filename << endl;
            return false;
        }
        
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                file >> data[i][j];
            }
        }
        file.close();
        return true;
    }

    // Function to display the matrix
    void displayMatrix() const {
        for (const auto& row : data) {
            for (int value : row) {
                cout << value << " ";
            }
            cout << endl;
        }
    }

    // Operator overloading for matrix addition
    Matrix operator+(const Matrix& other) const {
        Matrix result(size);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                result.data[i][j] = this->data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    // Operator overloading for matrix multiplication
    Matrix operator*(const Matrix& other) const {
        Matrix result(size);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                result.data[i][j] = 0;
                for (int k = 0; k < size; k++) {
                    result.data[i][j] += this->data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    // Function to calculate the sum of the main and secondary diagonals
    int sumDiagonals() const {
        int mainDiagonalSum = 0;
        int secondaryDiagonalSum = 0;
        for (int i = 0; i < size; i++) {
            mainDiagonalSum += data[i][i];
            secondaryDiagonalSum += data[i][size - i - 1];
        }
        return mainDiagonalSum + secondaryDiagonalSum;
    }

    // Function to swap two rows in the matrix
    void swapRows(int row1, int row2) {
        if (row1 >= 0 && row1 < size && row2 >= 0 && row2 < size) {
            swap(data[row1], data[row2]);
        } else {
            cout << "Invalid row indices." << endl;
        }
    }
};

int main() {
    int matrixSize = 4;  // Assuming a 4x4 matrix as per the sample input
    Matrix matrixA(matrixSize);
    Matrix matrixB(matrixSize);

    // Get file names from user input
    string filenameA, filenameB;
    cout << "Enter the filename for Matrix A: ";
    cin >> filenameA;
    cout << "Enter the filename for Matrix B: ";
    cin >> filenameB;

    // Load matrices from user-specified files
    if (!matrixA.loadMatrixFromFile(filenameA) || !matrixB.loadMatrixFromFile(filenameB)) {
        return 1;
    }

    // Display loaded matrices
    cout << "\nMatrix A:" << endl;
    matrixA.displayMatrix();

    cout << "\nMatrix B:" << endl;
    matrixB.displayMatrix();

    // Add two matrices
    Matrix matrixSum = matrixA + matrixB;
    cout << "\nSum of Matrix A and B:" << endl;
    matrixSum.displayMatrix();

    // Multiply two matrices
    Matrix matrixProduct = matrixA * matrixB;
    cout << "\nProduct of Matrix A and B:" << endl;
    matrixProduct.displayMatrix();

    // Sum of diagonal elements
    int diagonalSum = matrixA.sumDiagonals();
    cout << "\nSum of diagonals of Matrix A: " << diagonalSum << endl;

    // Swap rows
    cout << "\nMatrix A after swapping row 1 and row 3:" << endl;
    matrixA.swapRows(0, 2);  // Swap row 1 and row 3 (0-indexed)
    matrixA.displayMatrix();

    return 0;
}
