
Implement an Array Implementation for Sparse Matrices

Example for Sparse Matrices
0 0 5  
1 2 8  
2 1 6
C++ Code:
#include <iostream>
using namespace std;

// Structure to represent a non-zero element
struct Element {
    int row;
    int col;
    int value;
};

// Sparse Matrix Class using array implementation
class SparseMatrix {
private:
    int rows;
    int cols;
    int numNonZero;
    Element elements[100]; // Array to store non-zero elements

public:
    SparseMatrix(int r, int c, int n) {
        rows = r;
        cols = c;
        numNonZero = n;
    }

    void readElements() {
        cout << "Enter " << numNonZero << " non-zero elements (row col value):" << endl;
        for (int i = 0; i < numNonZero; i++) {
            cin >> elements[i].row >> elements[i].col >> elements[i].value;
        }
    }
    void displayFullMatrix() {
        int k = 0;
        cout << "\nThe full matrix is:\n";
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (k < numNonZero && elements[k].row == i && elements[k].col == j) {
                    cout << elements[k].value << " ";
                    k++;
                } else {
                    cout << "0 ";
                }
            }
            cout << endl;
        }
    }
};

int main() {
    // Fixed size based on the sample input you gave
    int rows = 3;
    int cols = 3;
    int nonZeroElements = 3;

    SparseMatrix sm(rows, cols, nonZeroElements);

    // Example input: 0 0 5 | 1 2 8 | 2 1 6
    sm.readElements();      // Reads the non-zero elements
    sm.displayFullMatrix(); // Displays full matrix with zeros

    return 0;
}




INPUT:-
0 0 5
1 2 8
2 1 6
OUTPUT:-
5 0 0
0 0 8
0 6 0
