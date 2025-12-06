#include <iostream>
using namespace std;

#define MAX 5   // Maximum size of queue

class Queue {
private:
    int arr[MAX];
    int front, rear;

public:
    Queue() {
        front = -1;
        rear = -1;
    }

    // Check if queue is full
    bool isFull() {
        return (rear == MAX - 1);
    }

    // Check if queue is empty
    bool isEmpty() {
        return (front == -1 || front > rear);
    }

    // Insert element
    void enqueue(int value) {
        if (isFull()) {
            cout << "Queue Overflow! Cannot insert " << value << endl;
            return;
        }
        if (front == -1) front = 0;
        arr[++rear] = value;
        cout << value << " inserted into the queue." << endl;
    }

    // Delete element
    void dequeue() {
        if (isEmpty()) {
            cout << "Queue Underflow! Nothing to delete." << endl;
            return;
        }
        cout << arr[front] << " deleted from the queue." << endl;
        front++;

        if (front > rear) { // Reset queue if empty
            front = rear = -1;
        }
    }

    // Display queue
    void display() {
        if (isEmpty()) {
            cout << "Queue is empty." << endl;
            return;
        }
        cout << "Queue elements: ";
        for (int i = front; i <= rear; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    Queue q;
    int choice, value;

    cout << "---- SIMPLE QUEUE USING ARRAY ----" << endl;

    while (true) {
        cout << "\n1. Enqueue\n2. Dequeue\n3. Display\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter value to insert: ";
            cin >> value;
            q.enqueue(value);
            break;

        case 2:
            q.dequeue();
            break;

        case 3:
            q.display();
            break;

        case 4:
            cout << "Exiting..." << endl;
            return 0;

        default:
            cout << "Invalid choice! Try again." << endl;
        }
    }
}








