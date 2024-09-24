#include <iostream>
using namespace std;

#define SIZE 5  // Define the maximum size of the queue

class CircularQueue {
private:
    int front, rear;
    int queue[SIZE];

public:
    // Constructor to initialize the queue
    CircularQueue() {
        front = rear = -1;
    }

    // Insertion (Enqueue)
    void enqueue(int value) {
        if ((rear + 1) % SIZE == front) {
            cout << "Queue is Full. Cannot insert " << value << endl;
            return;
        }
        if (front == -1)  // If queue is initially empty
            front = 0;
        
        rear = (rear + 1) % SIZE;
        queue[rear] = value;
        cout << "Inserted " << value << " into the queue." << endl;
    }

    // Deletion (Dequeue)
    void dequeue() {
        if (front == -1) {
            cout << "Queue is Empty. Cannot dequeue." << endl;
            return;
        }
        cout << "Deleted " << queue[front] << " from the queue." << endl;
        if (front == rear) {  // If the queue has only one element left
            front = rear = -1;  // Reset queue to empty state
        } else {
            front = (front + 1) % SIZE;
        }
    }

    // Display the queue
    void display() {
        if (front == -1) {
            cout << "Queue is Empty." << endl;
            return;
        }

        cout << "Queue elements are: ";
        int i = front;
        while (true) {
            cout << queue[i] << " ";
            if (i == rear)
                break;
            i = (i + 1) % SIZE;
        }
        cout << endl;
    }
};

// Main function with switch case menu
int main() {
    CircularQueue cq;
    int choice, value;

    do {
        cout << "\nCircular Queue Operations Menu:";
        cout << "\n1. Enqueue (Insert)";
        cout << "\n2. Dequeue (Delete)";
        cout << "\n3. Display Queue";
        cout << "\n4. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                cq.enqueue(value);
                break;

            case 2:
                cq.dequeue();
                break;

            case 3:
                cq.display();
                break;

            case 4:
                cout << "Exiting..." << endl;
                break;

            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}

