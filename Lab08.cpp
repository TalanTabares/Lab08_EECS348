/*
Author: Talan Tabares
Subject: Lab08
Date: 4-2-2025
Description: C++ program that takes an inputted test file and does various operations to manipulate the matrices.
Inputs:
 - Test file (User specified name)

Outputs:
 - Matrix[i][j]
 - result
 - sum

 Sources:
- mathisfun
Used to make sure I know how to do matrix operations

- W3Schools
Used for help on efficient techniques to implement matrices in C++
*/

#include <iostream> // Library for Input and Output
#include <fstream>  // Library for file input and output
#include <vector>   // Library used to create vectors
#include <iomanip>  // Library to help with vector formatting

using namespace std; // Standard namespace for common functions

void loadMatrixFromFile(const string& filename, vector<vector<int>>& matrix1, vector<vector<int>>& matrix2, int& N) { // Function that opens the test file
    ifstream file(filename); // Open the file 
    if (!file) { // Check if the file could not open
        cerr << "Error opening file" << endl; // Output an error message if failure
        exit(1); // Exit the program 
    }

    file >> N; // Read the matrix size from the file and store in variable N
    matrix1.resize(N, vector<int>(N)); // Turn matrix 1 into an N X N matrix
    matrix2.resize(N, vector<int>(N)); // Turn matrix 2 into an N X N matrix

    for (int i = 0; i < N; ++i) { // Loop through each row of the first matrix
        for (int j = 0; j < N; ++j) { // Loop through each column of the first matrix
            file >> matrix1[i][j]; // Read element of matrix1
        }
    }

    for (int i = 0; i < N; ++i) { // Loop through each row of the second matrix
        for (int j = 0; j < N; ++j) { // Loop through each column of the second matrix
            file >> matrix2[i][j]; // Read element of matrix2
        }
    }

    file.close(); // Close the file once all information is read
}


void displayMatrix(const vector<vector<int>>& matrix, int N) { // Displays matrix to terminal
    for (int i = 0; i < N; ++i) { // Loop through each row of the matrix
        for (int j = 0; j < N; ++j) { // Loop through each column of the matrix
            cout << setw(4) << matrix[i][j]; // Display each element with a 4 space formatting
        }
        cout << endl; // Prints a newline after each row
    }
}

vector<vector<int>> addMatrices(const vector<vector<int>>& matrix1, const vector<vector<int>>& matrix2, int N) { // Adds two matrices
    vector<vector<int>> result(N, vector<int>(N)); // Create a new matrix to store the result of the computations
    for (int i = 0; i < N; ++i) { // Loop through each row
        for (int j = 0; j < N; ++j) { // Loop through each column
            result[i][j] = matrix1[i][j] + matrix2[i][j]; // Add elements of matrix1 and matrix2
        }
    }
    return result; // Return the result
}


vector<vector<int>> multiplyMatrices(const vector<vector<int>>& matrix1, const vector<vector<int>>& matrix2, int N) { // Multiplies two matrices
    vector<vector<int>> result(N, vector<int>(N, 0)); // Initialize a new matrix to store the results
    for (int i = 0; i < N; ++i) { // Loop through each row of matrix1
        for (int j = 0; j < N; ++j) { // Loop through each column of matrix2
            for (int k = 0; k < N; ++k) { // Dot product computation
                result[i][j] += matrix1[i][k] * matrix2[k][j]; // Multiply 
            }
        }
    }
    return result; // Return the result
}


int sumDiagonal(const vector<vector<int>>& matrix, int N) { // Calculates diagonal sums
    int sum = 0; // Initialize sum to 0
    for (int i = 0; i < N; ++i) { // Loop through each row
        sum += matrix[i][i]; // Add main diagonal element
        sum += matrix[i][N - i - 1]; // Add second diagonal element
    }

    if (N % 2 != 0) { // If the matrix size is odd, then get rid of the element that was added twice during the computation
        sum -= matrix[N / 2][N / 2]; // Subtract the center element for odd matrix
    }
    return sum; // Return the sum 
}


void swapRows(vector<vector<int>>& matrix, int row1, int row2, int N) { // Swaps two rows in a matrix
    if (row1 >= 0 && row1 < N && row2 >= 0 && row2 < N) { // Check if row indices are valid
        swap(matrix[row1], matrix[row2]); // Swap the rows
    }
}


void swapColumns(vector<vector<int>>& matrix, int col1, int col2, int N) { // Swaps two columns in a matrix
    if (col1 >= 0 && col1 < N && col2 >= 0 && col2 < N) { // Check if column indices are valid
        for (int i = 0; i < N; ++i) { // Loop through all rows
            swap(matrix[i][col1], matrix[i][col2]); // Swap the elements in the column
        }
    }
}


void updateElement(vector<vector<int>>& matrix, int row, int col, int newValue, int N) { // Replaces value of an element at a specified point
    if (row >= 0 && row < N && col >= 0 && col < N) { // Check if indices are valid
        matrix[row][col] = newValue; // Update the element at the specified position
    }
}

int main() { // Main function that calls other functions
    string filename; // Initialize filename to store the input file name
    cout << "Enter the test file: "; // Get user input for file name
    cin >> filename; // Read the filename 

    int N; // Initialize a variable to hold the matrix size
    vector<vector<int>> matrix1, matrix2; // Initialize two matrices to store the data

    
    loadMatrixFromFile(filename, matrix1, matrix2, N); // Get matrix information from input file

  
    cout << "Matrix 1:" << endl; // Text before displaying matrix 1
    displayMatrix(matrix1, N); // Display matrix 1
    cout << "Matrix 2:" << endl; // Text before displating matrix 2
    displayMatrix(matrix2, N); // Display matrix 2

    
    vector<vector<int>> addedMatrix = addMatrices(matrix1, matrix2, N); // Add two matrices
    cout << "Sum of matrices:" << endl; // Text to terminal
    displayMatrix(addedMatrix, N); // Display the result of the addition

    
    vector<vector<int>> multipliedMatrix = multiplyMatrices(matrix1, matrix2, N); // Multiply two matrices
    cout << "Product of matrices:" << endl; // Text to terminal
    displayMatrix(multipliedMatrix, N); // Display the result of the multiplication

    
    int diagonalSum = sumDiagonal(matrix1, N); // Calculate the sum of diagonal elements in a matrix
    cout << "Sum of diagonal elements of Matrix 1: " << diagonalSum << endl; // Display the result of the computation

    
    int row1, row2; // Creates variables to get ready for swapping rows
    cout << "Enter two row indices to swap: "; // Ask users for row indices
    cin >> row1 >> row2; // Read the row indices
    swapRows(matrix1, row1, row2, N); // Swap the rows in matrix 1
    cout << "Matrix 1 after row swap:" << endl;
    displayMatrix(matrix1, N); // Display matrix 1 after the row swap

    
    int col1, col2; // Creates variables to get ready for swapping columns
    cout << "Enter two column indices to swap: "; // Ask the user for column indices
    cin >> col1 >> col2; // Read the column indices
    swapColumns(matrix1, col1, col2, N); // Swap the columns in matrix 1
    cout << "Matrix 1 after column swap:" << endl;
    displayMatrix(matrix1, N); // Display matrix 2 after the column swap

    
    int row, col, newValue; // Create variables to hold the row, column, and new value in prepearation for replacing a value
    cout << "Enter the row and column indices and the new value to update: "; // Ask the user for row, column, and value
    cin >> row >> col >> newValue; // Read the row, column, and new value
    updateElement(matrix1, row, col, newValue, N); // Update the element in matrix 1
    cout << "Matrix 1 after update:" << endl;
    displayMatrix(matrix1, N); // Display matrix 1 after the update

    return 0; // Return 0 once program has ran 
}
