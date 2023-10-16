/*Implement a circular linked list with the following functions
void createList(struct node** head_ptr): Creates a circular linked list with the length and
elements taken from the user.
void Print(struct node* head): Prints the elements of the circular linked list.*/

#include<stdio.h>
#include<stdlib.h>

struct node {
    int elem;
    struct node *next;
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
        if(*head_ptr == NULL) {
            *head_ptr = new_node;
            new_node->next = *head_ptr;
            continue;
        }
        struct node *temp = *head_ptr;
        while(temp->next != *head_ptr)
            temp = temp->next;
        temp->next = new_node;
        new_node->next = *head_ptr;
    }
}

void Print(struct node* head) {
    if(head == NULL)
        return;
    struct node *temp = head;
    do {
        printf("%d ", temp->elem);
        temp = temp->next;
    } while(temp != head);
}

int main() {
    struct node *head = NULL;
    createList(&head);
    Print(head);
    return 0;
}

// Path: circularLinkedList_2203117.c


