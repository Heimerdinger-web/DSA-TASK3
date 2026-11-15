/*
 * Program: Double Ended Queue (Deque) operations in C
 *   (a) Front insertion
 *   (b) Rear insertion
 *   (c) Front deletion
 *   (d) Rear deletion
 *
 * What I understand about a deque:
 *   A double ended queue (deque) is a queue in which insertion AND deletion
 *   can both be done at either end (the front or the rear). In a normal
 *   queue, I can only add at the rear and remove from the front.
 *
 * How I implemented it:
 *   I used a CIRCULAR array. This is because inserting at the front means
 *   moving "front" backwards, and when front is at index 0 it must wrap
 *   round to the last index of the array.
 *       moving forward  : index = (index + 1) % SIZE
 *       moving backward : index = (index - 1 + SIZE) % SIZE
 *   I use a "count" variable to know how many elements are stored, which
 *   makes it easy to check if the deque is empty or full.
 *
 *   front -> index of the first element
 *   rear  -> index of the last element
 */

#include <stdio.h>

#define SIZE 5              /* maximum number of elements in the deque */

int deque[SIZE];            /* array that stores the elements */
int front = 0;              /* index of the first element */
int rear = -1;              /* index of the last element */
int count = 0;              /* number of elements currently stored */

/* Returns 1 if the deque has no elements, otherwise 0 */
int isEmpty(void) {
    return count == 0;
}

/* Returns 1 if the deque is full, otherwise 0 */
int isFull(void) {
    return count == SIZE;
}

/* (a) FRONT INSERTION
 * Steps:
 *   1. If the deque is full, show overflow and stop.
 *   2. If the deque is empty, the new element becomes both front and rear.
 *   3. Otherwise, move front one step BACKWARD (wrapping round if needed).
 *   4. Store the value at deque[front] and increase count.
 */
void insertFront(int value) {
    if (isFull()) {
        printf("Overflow! Deque is full. Cannot insert %d at the front.\n", value);
        return;
    }
    if (isEmpty()) {
        front = 0;
        rear = 0;
    } else {
        front = (front - 1 + SIZE) % SIZE;   /* move backward, wrap if at 0 */
    }
    deque[front] = value;
    count++;
    printf("%d inserted at the front.\n", value);
}

/* (b) REAR INSERTION
 * Steps:
 *   1. If the deque is full, show overflow and stop.
 *   2. If the deque is empty, the new element becomes both front and rear.
 *   3. Otherwise, move rear one step FORWARD (wrapping round if needed).
 *   4. Store the value at deque[rear] and increase count.
 */
void insertRear(int value) {
    if (isFull()) {
        printf("Overflow! Deque is full. Cannot insert %d at the rear.\n", value);
        return;
    }
    if (isEmpty()) {
        front = 0;
        rear = 0;
    } else {
        rear = (rear + 1) % SIZE;            /* move forward, wrap if at end */
    }
    deque[rear] = value;
    count++;
    printf("%d inserted at the rear.\n", value);
}

/* (c) FRONT DELETION
 * Steps:
 *   1. If the deque is empty, show underflow and stop.
 *   2. Take the value at deque[front].
 *   3. Move front one step FORWARD (wrapping round if needed).
 *   4. Decrease count.
 */
void deleteFront(void) {
    if (isEmpty()) {
        printf("Underflow! Deque is empty. Nothing to delete from the front.\n");
        return;
    }
    int removed = deque[front];
    front = (front + 1) % SIZE;
    count--;
    printf("%d deleted from the front.\n", removed);
}

/* (d) REAR DELETION
 * Steps:
 *   1. If the deque is empty, show underflow and stop.
 *   2. Take the value at deque[rear].
 *   3. Move rear one step BACKWARD (wrapping round if needed).
 *   4. Decrease count.
 */
void deleteRear(void) {
    if (isEmpty()) {
        printf("Underflow! Deque is empty. Nothing to delete from the rear.\n");
        return;
    }
    int removed = deque[rear];
    rear = (rear - 1 + SIZE) % SIZE;
    count--;
    printf("%d deleted from the rear.\n", removed);
}

/* Show the elements from front to rear */
void display(void) {
    int i;
    if (isEmpty()) {
        printf("Deque is empty.\n");
        return;
    }
    printf("Deque (front -> rear): ");
    for (i = 0; i < count; i++) {
        printf("%d ", deque[(front + i) % SIZE]);
    }
    printf("\n");
}

int main(void) {
    int choice, value;

    do {
        printf("\n===== DEQUE MENU =====\n");
        printf("1. Insert at front\n");
        printf("2. Insert at rear\n");
        printf("3. Delete from front\n");
        printf("4. Delete from rear\n");
        printf("5. Display\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            break;                           /* stop if input is not a number */
        }

        switch (choice) {
        case 1:
            printf("Enter the value: ");
            scanf("%d", &value);
            insertFront(value);
            break;
        case 2:
            printf("Enter the value: ");
            scanf("%d", &value);
            insertRear(value);
            break;
        case 3:
            deleteFront();
            break;
        case 4:
            deleteRear();
            break;
        case 5:
            display();
            break;
        case 6:
            printf("Goodbye!\n");
            break;
        default:
            printf("Invalid choice, try again.\n");
        }
    } while (choice != 6);

    return 0;
}