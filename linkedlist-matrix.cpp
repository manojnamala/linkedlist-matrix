#include <iostream>
using namespace std;

// Node structure for linked list
struct Node {
    int row, col, value;
    Node* next;
    Node(int r, int c, int v) : row(r), col(c), value(v), next(nullptr) {}
};

class SparseMatrix {
private:
    int rows, cols;
    Node* head;

public:
    // Constructor
    SparseMatrix(int r, int c) {
        rows = r;
        cols = c;
        head = nullptr;
    }

    // Insert non-zero element into linked list
    void insert(int r, int c, int v) {
        if (v == 0) return; // Skip zero values
        Node* newNode = new Node(r, c, v);

        if (head == nullptr) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    // Display sparse matrix in triplet form
    void displayTriplet() {
        cout << "Row\tCol\tValue\n";
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->row << "\t" << temp->col << "\t" << temp->value << endl;
            temp = temp->next;
        }
    }

    // Display full matrix
    void displayFull() {
        Node* temp = head;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (temp != nullptr && temp->row == i && temp->col == j) {
                    cout << temp->value << " ";
                    temp = temp->next;
                } else {
                    cout << "0 ";
                }
            }
            cout << endl;
        }
    }
};

int main() {
    int rows, cols, numNonZero;
    cout << "Enter number of rows, cols, and non-zero elements: ";
    cin >> rows >> cols >> numNonZero;

    SparseMatrix sm(rows, cols);

    cout << "Enter row, column, and value for " << numNonZero << " non-zero elements:\n";
    for (int i = 0; i < numNonZero; i++) {
        int r, c, v;
        cin >> r >> c >> v;
        sm.insert(r, c, v);
    }

    cout << "\nSparse Matrix (Triplet Form):\n";
    sm.displayTriplet();

    cout << "\nFull Matrix Representation:\n";
    sm.displayFull();

    return 0;
}
