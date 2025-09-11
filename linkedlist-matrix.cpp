#include <iostream>
using namespace std;

// Node representing a non-zero matrix element
struct Node {
    int row;
    int col;
    int value;
    Node* next;
};

// SparseMatrix class using sorted linked list 
class SparseMatrix {
    int rows, cols;
    Node* head;

public:
    SparseMatrix(int r, int c) : rows(r), cols(c), head(nullptr) {}

    ~SparseMatrix() {
        while (head != nullptr) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
    }

    // Insert maintaining sorted order by (row, col)
    void insert(int r, int c, int val) {
        if (val == 0) return; // skip zero values

        Node* newNode = new Node{r, c, val, nullptr};

        // Insert at head if needed
        if (!head || (r < head->row) || (r == head->row && c < head->col)) {
            newNode->next = head;
            head = newNode;
            return;
        }

        // Find correct position
        Node* current = head;
        while (current->next != nullptr && 
               (current->next->row < r || 
               (current->next->row == r && current->next->col < c))) {
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;
    }

    // Display full matrix including zeros
    void display() const {
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
            cout << "\n";
        }
    }
};

int main() {
    int rows, cols, nonZeroCount;
    cout << "Enter matrix dimensions (rows cols): ";
    cin >> rows >> cols;
    cout << "Enter number of non-zero elements: ";
    cin >> nonZeroCount;

    SparseMatrix sm(rows, cols);

    cout << "Enter row, column, and value of non-zero elements:\n";
    for (int i = 0; i < nonZeroCount; i++) {
        int r, c, val;
        cin >> r >> c >> val;
        sm.insert(r, c, val);
    }

    cout << "\nSparse Matrix representation:\n";
    sm.display();

    return 0;
}
