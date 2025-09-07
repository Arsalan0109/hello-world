Implement a Linked List Representation of a sparse matrix

Example foe Sparse matrix
0 0 5  
1 2 8  
2 1 6

#include <iostream>
using namespace std;

struct Node {
    int row, col, value;
    Node* next;
    
    Node(int r, int c, int val) : row(r), col(c), value(val), next(nullptr) {}
};

class SparseMatrix {
private:
    Node* head;
    int rows, cols;

public:
    SparseMatrix(int r, int c) {
        rows = r;
        cols = c;
        head = nullptr;
    }

    ~SparseMatrix() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    void insert(int r, int c, int val) {
        if (val == 0) return; // Skip zero entries

        Node* newNode = new Node(r, c, val);
        if (!head || (r < head->row) || (r == head->row && c < head->col)) {
            newNode->next = head;
            head = newNode;
        } else {
            Node* current = head;
            while (current->next &&
                   (current->next->row < r || 
                   (current->next->row == r && current->next->col < c))) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }

    void displayFullMatrix() {
        Node* current = head;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (current && current->row == i && current->col == j) {
                    cout << current->value << " ";
                    current = current->next;
                } else {
                    cout << "0 ";
                }
            }
            cout << endl;
        }
    }

    SparseMatrix transpose() {
        SparseMatrix transposed(cols, rows);
        Node* current = head;
        while (current) {
            transposed.insert(current->col, current->row, current->value);
            current = current->next;
        }
        return transposed;
    }
};

// ---------- MAIN FUNCTION FOR DEMO ----------

int main() {
    SparseMatrix sm(3, 3);

    sm.insert(0, 0, 5);
    sm.insert(1, 2, 8);
    sm.insert(2, 1, 6);

    cout << "Original Matrix:\n";
    sm.displayFullMatrix();

    SparseMatrix transposed = sm.transpose();
    cout << "\nTransposed Matrix:\n";
    transposed.displayFullMatrix();

    return 0;
}

OUTPUT:-
Original Matrix:
5 0 0
0 0 8
0 6 0

Transposed Matrix:
5 0 0
0 0 6
0 8 0


