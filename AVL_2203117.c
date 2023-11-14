/*This program Implements an AVL tree with nodes of the type struct avlnode. Also implements proper functions associated with the AVL tree such as checking for height balance, insertion, deletion, etc.
Created by: MAANAS B.
Created on : 07/01/2023*/

#include<stdio.h>
#include<stdlib.h>

struct avlnode
{
    int data;
    int height;
    struct avlnode *left;
    struct avlnode *right;
};

int max(int a, int b)
{
    if(a>b) return a;
	 else return b;
}

int height(struct avlnode *root)
{
    if(root==NULL)
    {
        return 0;
    }
    return root->height;
}

struct avlnode* newNode(int item)
{
    struct avlnode *temp = (struct avlnode*)malloc(sizeof(struct avlnode));
    temp->data = item;
    temp->height = 1;
    temp->left = NULL;
    temp->right=NULL;
    return temp;
}

struct avlnode* rightRotate(struct avlnode *y)
{
    struct avlnode *x = y->left;
    struct avlnode *T2 = x->right;
    
    x->right = y;
    y->left = T2;
    
    y->height = max(height(y->left),height(y->right))+1;
    x->height = max(height(x->left),height(x->right))+1;
    
    return x;
}

struct avlnode* leftRotate(struct avlnode *x)
{
    struct avlnode *y = x->right;
    struct avlnode *T2 = y->left;
    
    y->left = x;
    x->right = T2;
    
    x->height = max(height(x->left),height(x->right))+1;
    y->height = max(height(y->left),height(y->right))+1;
    
    return y;
}

int getBalance(struct avlnode *root)
{
    if(root == NULL)
    {
        return 0;
    }
    return height(root->left)-height(root->right);
}

struct avlnode* add(int item, struct avlnode *root)
{
    if(root == NULL)
    {
        return newNode(item);
    }
    else if(item < root->data)
    {
        root->left= add(item,root->left);
    }
    else if(item > root->data)
    {
        root->right = add(item,root->right);
    }
    else
    {
        return root;
    }
    
    root->height= 1+max(height(root->left),height(root->right));
    
    int balance = getBalance(root);
    
    if(balance > 1 && item < root->left->data)
    {
        return rightRotate(root);
    }
    if(balance < -1 && item > root->right->data)
    {
        return leftRotate(root);
    }
    if(balance > 1 && item > root->left->data)
    {
        root->left=leftRotate(root->left);
        return rightRotate(root);
    }
    if(balance < -1 && item < root->right->data)
    {
        root->right=rightRotate(root->right);
        return leftRotate(root);
    }
    
    return root;
}

struct avlnode* minValueNode(struct avlnode *root)
{
    struct avlnode *current=root;
    while(current->left!=NULL)
    {
        current =current->left;
    }
    return current;
}

struct avlnode* delete(int key, struct avlnode *root)
{
    if(root==NULL)
    {
        return root;
    }
    else if(key<root->data)
    {
        root->left=delete(key,root->left);
    }
    else if(key>root->data)
    {
        root->right=delete(key,root->right);
    }
    else
    {
        if(root->left==NULL || root->right==NULL)
        {
            struct avlnode *temp=root->left?root->left:root->right;
            
            if(temp==NULL)
            {
                temp=root;
                root=NULL;
            }
            else
            {
                *root=*temp;
            }
            free(temp);
        }
        else
        {
            struct avlnode *temp=minValueNode(root->right);
            
            root->data=temp->data;
            
            root->right=delete(temp->data,root->right);
        }
    }
    
    if(root==NULL)
    {
        return root;
    }
    
    root->height=1+max(height(root->left),height(root->right));
    
    int balance=getBalance(root);
    
    if(balance>1 && getBalance(root->left)>=0)
    {
        return rightRotate(root);
    }
    if(balance>1 && getBalance(root->left)<0)
    {
        root->left=leftRotate(root->left);
        return rightRotate(root);
    }
    if(balance<-1 && getBalance(root->right)<=0)
    {
        return leftRotate(root);
    }
    if(balance<-1 && getBalance(root->right)>0)
    {
        root->right=rightRotate(root->right);
        return leftRotate(root);
    }
    
    return root;
}

struct avlnode* search(int key, struct avlnode *root)
{
    if(root==NULL)
    {
        return NULL;
    }
    else if(key==root->data)
    {
        return root;
    }
    else if(key<root->data)
    {
        return search(key,root->left);
    }
    else if(key>root->data)
    {
        return search(key,root->right);
    }
}

void printPreorder(struct avlnode *root)
{
    if(root!=NULL)
    {
        printf("%d ",root->data);
        printPreorder(root->left);
        printPreorder(root->right);
    }
}

void printInorder(struct avlnode *root)
{
    if(root!=NULL)
    {
        printInorder(root->left);
        printf("%d ",root->data);
        printInorder(root->right);
    }
}

void printPostorder(struct avlnode *root)
{
    if(root!=NULL)
    {
        printPostorder(root->left);
        printPostorder(root->right);
        printf("%d ",root->data);
    }
}

int main()
{
    struct avlnode *root=NULL;
    int choice,item;
    while(1)
    {
        printf("\n====================\n1. Add\n2. Search\n3. Delete\n4. Print\n5. Exit\n====================\nPlease enter your choice: ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                printf("Enter the item to be added: ");
                scanf("%d",&item);
                root=add(item,root);
                break;
            case 2:
                printf("Enter the item to be searched: ");
                scanf("%d",&item);
                if(search(item,root)==NULL)
                {
                    printf("Item not found\n");
                }
                else
                {
                    printf("Item found\n");
                }
                break;
            case 3:
                printf("Enter the item to be deleted: ");
                scanf("%d",&item);
                root=delete(item,root);
                break;
            case 4:
                printf("Preorder: ");
                printPreorder(root);
                printf("\nInorder: ");
                printInorder(root);
                printf("\nPostorder: ");
                printPostorder(root);
                printf("\n");
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}

