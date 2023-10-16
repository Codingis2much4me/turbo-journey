/* Implement a singly linked list with the following functions
    1. bool InsertAtPosition(struct node** head_ptr, int index, int elem) which creates a node 
    with data = elem and places this new node at the index th position in the linked list. Returns 
    True if the operation is successful (i.e. index is in the correct range) and False otherwise.
    2. int DeleteAtPosition(struct node** head_ptr, int index) which deletes the node at the index th
    position in the linked list. Returns -1 if the operation is unsuccessful (i.e. index is not in the
    correct range) otherwise returns the data (elem) of the deleted node.
    3. void createList(struct node** head_ptr) which creates a linked list whose length and elements
    are taken from the user. It should use the InsertAtPosition function to create the linked list. 
    It should also print the linked list.
    4. void Reverse(struct node** head_ptr) which reverses the linked list. Note that you don't need
    to create new nodes, just change the 'next' pointer to point to the previous node. */

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct node {
    int elem;
    struct node *next;
};

bool InsertAtPosition(struct node** head_ptr, int index, int elem) {
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->elem = elem;
    if(index == 0) {
        new_node->next = *head_ptr;
        *head_ptr = new_node;
        return true;
    }
    struct node *temp = *head_ptr;
    for(int i = 0; i < index - 1; i++) {
        if(temp == NULL)
            return false;
        temp = temp->next;
    }
    if(temp == NULL)
        return false;
    new_node->next = temp->next;
    temp->next = new_node;
    return true;
}

int DeleteAtPosition(struct node** head_ptr, int index) {
    if(index == 0) {
        struct node *temp = *head_ptr;
        *head_ptr = (*head_ptr)->next;
        int elem = temp->elem;
        free(temp);
        return elem;
    }
    struct node *temp = *head_ptr;
    for(int i = 0; i < index - 1; i++) {
        if(temp == NULL)
            return -1;
        temp = temp->next;
    }
    if(temp == NULL || temp->next == NULL)
        return -1;
    struct node *temp2 = temp->next;
    temp->next = temp2->next;
    int elem = temp2->elem;
    free(temp2);
    return elem;
}

void createList(struct node** head_ptr) {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    printf("Enter the elements: ");
    for(int i = 0; i < n; i++) {
        int elem;
        scanf("%d", &elem);
        InsertAtPosition(head_ptr, i, elem);
    }
    //Also print the linked list
    struct node *temp = *head_ptr;
    while(temp != NULL) {
        printf("%d ", temp->elem);
        temp = temp->next;
    }
    printf("\n");
}

void Reverse(struct node** head_ptr) {
    struct node *prev = NULL, *curr = *head_ptr, *next = NULL;
    while(curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next; 
    }
    *head_ptr = prev;
}
//Write an appropriate main function to test the above functions including InsertAtPosition, DeleteAtPosition, createList and Reverse.
int main() {
    struct node *head = NULL;
    createList(&head);
    Reverse(&head);
    struct node *temp = head;
    while(temp != NULL) {
        printf("%d ", temp->elem);
        temp = temp->next;
    }
    printf("\n");
    return 0;
}