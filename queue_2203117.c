/*This program implements a queue Data Type, where the maximum number of elements in the queue is 7. The elements are represented by an array of integers, and we use a structure q to define the queue. We give the user choices between enqueueing, dequeueing, peeking at the head of the queue and exiting the program, by appropriately taking care of the conditions when the queue is full.
Coded by: MAANAS B.
Roll no. 2203117*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAXSIZE 7

struct queue {
    int arr[MAXSIZE];
    int head;
    int tail;
};

struct queue q;

void enqueue(int elem) {
    if((q.tail + 1) % MAXSIZE == q.head) {
        printf("Queue is full\n");
        return;
    }
    q.arr[q.tail] = elem;
    q.tail = (q.tail + 1) % MAXSIZE;
}

int dequeue() {
    if(q.head == q.tail) {
        printf("Queue is empty\n");
        return -1;
    }
    int elem = q.arr[q.head];
    q.head = (q.head + 1) % MAXSIZE;
    return elem;
}

int peek() {
    if(q.head == q.tail) {
        printf("Queue is empty\n");
        return -1;
    }
    return q.arr[q.head];
}

bool isFull() {
    return (q.tail + 1) % MAXSIZE == q.head;
}

bool isEmpty() {
    return q.head == q.tail;
}

int main() {
    q.head = 0;
    q.tail = 0;
    while(1) {
        printf("====================\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Peek\n");
        printf("4. Exit\n");
        printf("Please enter your choice: ");
        int choice;
        scanf("%d", &choice);
        switch(choice) {
            case 1: {
                int elem;
                printf("Enter the element to be enqueued: ");
                scanf("%d", &elem);
                enqueue(elem);
                break;
            }
            case 2: {
                int elem = dequeue();
                if(elem != -1)
                    printf("The element dequeued is %d\n", elem);
                break;
            }
            case 3: {
                int elem = peek();
                if(elem != -1)
                    printf("The element at the head of the queue is %d\n", elem);
                break;
            }
            case 4: {
                exit(0);
            }
            default: {
                printf("Invalid choice\n");
            }
        }
    }
    return 0;
}

