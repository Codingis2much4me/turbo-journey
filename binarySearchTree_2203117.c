#include <stdio.h>
#include <stdlib.h>

struct tnode {
    int data;
    struct tnode* left;
    struct tnode* right;
};

struct tnode* add(int item, struct tnode* root) {
    
    if(root == NULL) {
        struct tnode* temp = (struct tnode*)malloc(sizeof(struct tnode));
        temp->data = item;
        temp->left = NULL;
        temp->right = NULL;
        return temp;
    }
    else if(item < root->data) {
        root->left = add(item, root->left);
    }
    else if(item > root->data) {
        root->right = add(item, root->right);
    }
    return root;
}

struct tnode* search(int key, struct tnode* root) {
    if(root == NULL) return NULL;
    else if(key == root->data)
        return root;
    else if(key < root->data) 
        return search(key, root->left);
    else if(key > root->data) 
        return search(key, root->right);
}

struct tnode* delete(int key, struct tnode* root) {
    if(root == NULL) return NULL;
    else if (key < root->data)
        root->left = delete(key, root->left);
    else if(key > root->data)
        root->right = delete(key, root->right);
    else {
        if(root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }
        else if (root->left == NULL) {
            struct tnode* temp = root->left;
            free(root);
            return temp;
        }
        else if(root->right == NULL) {
            struct tnode* temp = root->right;
            free(root);
            return temp;
        }
        else {
            struct tnode* temp = root->right;
            while(temp->left != NULL) {
                temp = temp->left;
            }
            root->data = temp->data;
            root->right = delete(temp->data, root->right);
        }
    }
    return root;
}

void preorder(struct tnode* root) {
    if(root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}
 
void inorder(struct tnode* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void postorder(struct tnode* root) {
    if(root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

void print(struct tnode* root) {
    printf("Preorder: ");
    preorder(root);
    printf("\nPostorder: ");
    postorder(root);
    printf("\nInorder: ");
    inorder(root);
    printf("\n");
}

int main() {
    struct tnode* root = NULL;
    int choice, item, key;
    while(1) {
        printf("1.Add\n2.Search\n3.Delete\n4.Print\n5.Exit\n");
        scanf("%d", &choice);
        if(choice == 1) {
            printf("Enter the item to be added: ");
            scanf("%d", &item);
            root = add(item, root);
        }
        else if(choice == 2) {
            printf("Enter the key to be searched: ");
            scanf("%d", &key);
            if(search(key, root) == NULL) 
                printf("Key not found!\n");
            else printf("Key found!\n");
        }
        else if (choice == 3) {
            printf("Enter the key to be deleted: ");
            scanf("%d", &key);
            root = delete(key, root);
        }
        else if (choice == 4) {
            print(root);
        }
        else if (choice == 5) exit(0);
        else { 
            printf("Invalid choice\n");
        }
    }
}