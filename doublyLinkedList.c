/* Implement a doubly linked list with the following functions:
void createList(struct node** head_ptr) Creates a doubly linked list with the length and elements
taken from the user. Also print the linked list.
void InsertionSort(struct node** head_ptr) Implement insertion sort on the doubly linked list so 
that the elements are in ascending order.*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct node {
    int elem;
    struct node *next;
    struct node *prev;
};

void createList(struct node** head_ptr) {
    int n;
    printf("Enter the length of the linked list: ");
    scanf("%d", &n);
    printf("Enter the elements of the linked list: ");
    for(int i = 0; i < n; i++) {
        int elem;
        scanf("%d", &elem);
        struct node *new_node = (struct node *)malloc(sizeof(struct node));
        new_node->elem = elem;
        new_node->next = NULL;
        new_node->prev = NULL;
        if(*head_ptr == NULL) {
            *head_ptr = new_node;
            continue;
        }
        struct node *temp = *head_ptr;
        while(temp->next != NULL)
            temp = temp->next;
        temp->next = new_node;
        new_node->prev = temp;
    }
}

void InsertionSort(struct node** head_ptr) {
    if(*head_ptr == NULL || (*head_ptr)->next == NULL)
        return;
    struct node *temp = (*head_ptr)->next;
    while(temp != NULL) {
        struct node *temp2 = temp;
        while(temp2->prev != NULL && temp2->elem < temp2->prev->elem) {
            int elem = temp2->elem;
            temp2->elem = temp2->prev->elem;
            temp2->prev->elem = elem;
            temp2 = temp2->prev;
        }
        temp = temp->next;
    }
}

void printList(struct node** head_ptr) {
    struct node *temp = *head_ptr;
    while(temp != NULL) {
        printf("%d ", temp->elem);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    struct node *head = NULL;
    createList(&head);
    printf("The linked list is: ");
    printList(&head);
    InsertionSort(&head);
    printf("The sorted linked list is: ");
    printList(&head);
    return 0;
}