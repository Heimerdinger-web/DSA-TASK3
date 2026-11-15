/*
 * Program: Enqueue and Dequeue operations on a Queue (C++)
 *
 * What I understand about a queue:
 *   A queue is a linear data structure that follows the FIFO rule
 *   (First In, First Out). The element that enters first is the first one
 *   to leave, like people lining up at a bank.
 *     - Elements are ADDED at the REAR   (enqueue)
 *     - Elements are REMOVED from the FRONT (dequeue)
 *
 * How I implemented it:
 *   I used an array with two index variables:
 *     front -> index of the first element (next one to be removed)
 *     rear  -> index of the last element  (most recently added)
 *   Both start at -1, which means the queue is empty.
 *
 * Limitation: this is a simple (linear) queue. After elements are dequeued,
 * the slots at the start of the array are not reused. A circular queue
 * solves this problem.
 */

#include <iostream>
using namespace std;

#define SIZE 5          // maximum number of elements the queue can hold

int queueArr[SIZE];     // array that stores the queue elements
int front = -1;         // -1 means the queue is empty
int rear  = -1;

// Returns true if there are no elements in the queue
bool isEmpty() {
    return front == -1 || front > rear;
}

// Returns true if rear has reached the last position of the array
bool isFull() {
    return rear == SIZE - 1;
}

/* ENQUEUE: add an element at the rear
 * Steps:
 *   1. If the queue is full, show overflow and stop.
 *   2. If the queue is empty, set front to 0 (first insertion).
 *   3. Move rear forward by 1.
 *   4. Store the value at queueArr[rear].
 */
void enqueue(int value) {
    if (isFull()) {
        cout << "Queue Overflow! Cannot add " << value << endl;
        return;
    }
    if (front == -1) {      // first element being added
        front = 0;
    }
    rear++;
    queueArr[rear] = value;
    cout << value << " has been added to the queue." << endl;
}

/* DEQUEUE: remove an element from the front
 * Steps:
 *   1. If the queue is empty, show underflow and stop.
 *   2. Take the value at queueArr[front].
 *   3. Move front forward by 1.
 *   4. If the queue is now empty, reset front and rear to -1.
 */
void dequeue() {
    if (isEmpty()) {
        cout << "Queue Underflow! The queue is empty." << endl;
        return;
    }
    int removed = queueArr[front];
    front++;
    cout << removed << " has been removed from the queue." << endl;

    if (front > rear) {     // the last element was removed
        front = -1;
        rear = -1;
    }
}

// Show the elements from front to rear
void display() {
    if (isEmpty()) {
        cout << "Queue is empty." << endl;
        return;
    }
    cout << "Queue (front -> rear): ";
    for (int i = front; i <= rear; i++) {
        cout << queueArr[i] << " ";
    }
    cout << endl;
}

int main() {
    int choice, value;

    do {
        cout << "\n===== QUEUE MENU =====" << endl;
        cout << "1. Enqueue (add an element)" << endl;
        cout << "2. Dequeue (remove an element)" << endl;
        cout << "3. Display queue" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        if (!(cin >> choice)) break;      // stop if input is not a number

        switch (choice) {
        case 1:
            cout << "Enter the value to add: ";
            cin >> value;
            enqueue(value);
            break;
        case 2:
            dequeue();
            break;
        case 3:
            display();
            break;
        case 4:
            cout << "Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice, try again." << endl;
        }
    } while (choice != 4);

    return 0;
}