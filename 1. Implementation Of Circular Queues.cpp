/*
 * Program: Circular Queue implementation in C++
 *
 * My approach:
 *   - A normal (linear) queue wastes space: after some dequeues the front
 *     moves forward and the empty slots at the start can never be used again.
 *   - A circular queue fixes this by treating the array as a circle. When
 *     front or rear reaches the end of the array, it wraps around to index 0.
 *     I do this using the modulus operator:  next = (current + 1) % SIZE
 *   - I keep a variable "count" for the number of elements. This makes it
 *     easy to tell the difference between a full queue and an empty queue
 *     (without it, front == rear could mean either one).
 *
 * Operations: enqueue, dequeue, peek, isEmpty, isFull, display
 * Time complexity: every operation is O(1).
 */

#include <iostream>
using namespace std;

class CircularQueue {
private:
    int *arr;       // array that stores the elements
    int capacity;   // maximum number of elements the queue can hold
    int front;      // index of the first element (the one to be removed)
    int rear;       // index of the last element (the one added most recently)
    int count;      // how many elements are currently in the queue

public:
    // Constructor: create an empty queue of the given size
    CircularQueue(int size) {
        capacity = size;
        arr = new int[capacity];
        front = 0;
        rear = -1;      // -1 because nothing has been added yet
        count = 0;
    }

    // Destructor: free the memory I allocated with new
    ~CircularQueue() {
        delete[] arr;
    }

    // Returns true if there are no elements
    bool isEmpty() const {
        return count == 0;
    }

    // Returns true if the queue has reached its capacity
    bool isFull() const {
        return count == capacity;
    }

    // Add an element at the rear
    void enqueue(int value) {
        if (isFull()) {
            cout << "Queue is full (overflow). Cannot add " << value << endl;
            return;
        }
        rear = (rear + 1) % capacity;   // move rear forward, wrap if at end
        arr[rear] = value;
        count++;
        cout << "Enqueued " << value << "  (front=" << front
             << ", rear=" << rear << ")" << endl;
    }

    // Remove and return the element at the front
    int dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty (underflow). Nothing to remove." << endl;
            return -1;
        }
        int value = arr[front];
        front = (front + 1) % capacity; // move front forward, wrap if at end
        count--;
        cout << "Dequeued " << value << "  (front=" << front
             << ", rear=" << rear << ")" << endl;
        return value;
    }

    // Look at the front element without removing it
    int peek() const {
        if (isEmpty()) {
            cout << "Queue is empty." << endl;
            return -1;
        }
        return arr[front];
    }

    // Show the elements from front to rear, and the raw array layout
    void display() const {
        if (isEmpty()) {
            cout << "Queue: [empty]" << endl;
            return;
        }
        cout << "Queue (front -> rear): ";
        for (int i = 0; i < count; i++) {
            cout << arr[(front + i) % capacity] << " ";
        }
        cout << endl;

        // Raw array so the wrap-around can be seen ("_" = unused slot)
        cout << "Array slots          : ";
        for (int i = 0; i < capacity; i++) {
            // a slot is in use if it lies between front and rear (circularly)
            bool used = false;
            for (int j = 0; j < count; j++) {
                if ((front + j) % capacity == i) used = true;
            }
            if (used) cout << arr[i] << " ";
            else      cout << "_ ";
        }
        cout << endl;
    }
};

int main() {
    CircularQueue q(5);   // queue that can hold 5 elements

    cout << "=== Step 1: fill the queue ===" << endl;
    for (int i = 10; i <= 50; i += 10) {
        q.enqueue(i);
    }
    q.display();

    cout << "\n=== Step 2: try to add to a full queue ===" << endl;
    q.enqueue(60);

    cout << "\n=== Step 3: remove two elements (frees slots at the start) ===" << endl;
    q.dequeue();
    q.dequeue();
    q.display();

    cout << "\n=== Step 4: add two more - rear wraps around to index 0 ===" << endl;
    q.enqueue(60);
    q.enqueue(70);
    q.display();
    cout << "A normal linear queue could NOT have reused those first two slots." << endl;

    cout << "\n=== Step 5: peek and empty the queue ===" << endl;
    cout << "Front element is " << q.peek() << endl;
    while (!q.isEmpty()) {
        q.dequeue();
    }
    q.display();

    cout << "\n=== Step 6: dequeue from an empty queue ===" << endl;
    q.dequeue();

    return 0;
}