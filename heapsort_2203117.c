/*Implements the heap data structure. Also implements the heapsort() and heapify() functions.
I have also writtn the time complexities of all the associated functions in the pdf file.
Created by: MAANAS B.
Created on 7/11/2023
*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#include<math.h>

int sift_down(int *arr, int n, int index)
{
    int l_child=2*index+1;
    int r_child=2*index+2;
    int max_index=index;
    if(l_child<n && arr[l_child]>arr[max_index])
    {
        max_index=l_child;
    }
    if(r_child<n && arr[r_child]>arr[max_index])
    {
        max_index=r_child;
    }
    if(max_index!=index)
    {
        int temp=arr[index];
        arr[index]=arr[max_index];
        arr[max_index]=temp;
        sift_down(arr, n, max_index);
    }
    return 0;
}

int sift_up(int *arr, int index)
{
    int parent=(index-1)/2;
    if(parent>=0 && arr[parent]<arr[index])
    {
        int temp=arr[parent];
        arr[parent]=arr[index];
        arr[index]=temp;
        sift_up(arr, parent);
    }
    return 0;
}

int find_parent(int index)
{
    return (index-1)/2;
}

int find_l_child(int index)
{
    return 2*index+1;
}

int find_r_child(int index)
{
    return 2*index+2;
}

bool is_valid_index(int index, int n)
{
    return (index>=0 && index<n);
}

struct heap
{
    int *arr;
    int n;
};

void heapify(int *arr, int n)
{
    for(int i=(n-2)/2;i>=0;i--)
    {
        sift_down(arr, n, i);
    }
}

int get_max(int *arr, int n)
{
    return arr[0];
}

void insert(int *arr, int *n, int item)
{
    arr[*n]=item;
    (*n)++;
    sift_up(arr, *n-1);
}

int delete_max(int *arr, int *n)
{
    int max=arr[0];
    arr[0]=arr[*n-1];
    (*n)--;
    sift_down(arr, *n, 0);
    return max;
}

void heapsort(int *arr, int n)
{
    heapify(arr, n);
    for(int i=n-1;i>=0;i--)
    {
        arr[i]=delete_max(arr, &n);
    }
}

int main()
{
    srand(time(0));
    int n=20;
    int arr[n];
    for(int i=0;i<n;i++)
    {
        arr[i]=rand()%100;
    }
    printf("Original array:\n");
    for(int i=0;i<n;i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
    heapsort(arr, n);
    printf("Sorted array:\n");
    for(int i=0;i<n;i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
    return 0;
}

// Time complexity of sift_down(): O(logn)
// Time complexity of sift_up(): O(logn)
// Time complexity of find_parent(): O(1)
// Time complexity of find_l_child(): O(1)
// Time complexity of find_r_child(): O(1)
// Time complexity of is_valid_index(): O(1)
// Time complexity of heapify(): O(nlogn)
// Time complexity of get_max(): O(1)
// Time complexity of insert(): O(logn)
// Time complexity of delete_max(): O(logn)
// Time complexity of heapsort(): O(nlogn)
