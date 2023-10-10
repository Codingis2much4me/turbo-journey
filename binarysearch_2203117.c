/*Write a recursive function binarysearch() that takes an integer array arr and an integer x as input and outputs the 
index of x in arr if it exists and -1 otherwise. 
In the main function take an integer k from the user and for every i belonging to {1, 2, 3, ..., k} take a random* positive integer array of 
size n = 2^i and sort it using quicksort. 
Output the time T(n) (in terms of number of operations) taken by binarysearch to search for x = -1 in the sorted array.
Calculate the ratio ci = T(n)/logn and print the tuple (i, 2^i, T(2^i), i*2^i, ci) for each i on a new row.
Find the expected value and variance of ci and print it.*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

int *count_the_operations;

void swap(int *a, int *b) {
    *count_the_operations += 1; // swap operation
    int temp = *a;
    *a = *b;
    *b = temp; 
}

void quicksort(int *a, int startindex, int n) {
    if(n <= 1)
    *count_the_operations += 1; 
        return;
    int pivot = a[startindex];
    int i = startindex, j = startindex + n - 1;
    while (i <= j) {
        *count_the_operations += 1; // while loop
        while(a[i] < pivot) {
            i++;
            *count_the_operations += 1;
        }
        while(a[j] > pivot) {
            j--;
            *count_the_operations += 1;
        }
        if(i <= j) {
            swap(&a[i], &a[j]);
            i++;
            j--;
        }
    }
    quicksort(a, startindex, j - startindex + 1);
    quicksort(a, i, startindex + n - i);
    
}

int binarysearch(int *arr, int x, int startindex, int endindex) {
    if(startindex > endindex) {
        *count_the_operations += 1;
        return -1;
    }
    *count_the_operations += 1;
    int mid = (startindex + endindex) / 2;
    if(arr[mid] == x)
        return mid;
    else if(arr[mid] > x)
        return binarysearch(arr, x, startindex, mid - 1);
    else
        return binarysearch(arr, x, mid + 1, endindex);
}

int main() {
    srand(time(0));
    double expected_ci = 0, ci_square = 0, expected_ci_square = 0, variance = 0;
    printf("Enter the value of k: ");
    int k;
    scanf("%d", &k);
    for(int i = 1; i <= k; i++) {
        int n = pow(2, i);
        int a[n];
        for(int j = 0; j < n; j++)
            a[j] = rand() % 100;
        count_the_operations = (int *)malloc(sizeof(int));
        *count_the_operations = 0;
        quicksort(a, 0, n);
        int index = binarysearch(a, -1, 0, n - 1);
        double ci = (double)(*count_the_operations) / log2(n);
        printf("(i, 2^i, T(2^i), i*2^i, ci) = (%d, %d, %d, %d, %lf)\n", i, n, *count_the_operations, i * n, ci);
        free(count_the_operations);
        if(i > 5) {
        expected_ci += ci;
        ci_square = ci * ci;
        expected_ci_square += ci_square;
        }
    }
    expected_ci /= (k - 5);
    expected_ci_square /= (k - 5);
    variance = expected_ci_square - expected_ci * expected_ci;
    printf("Expected value of ci = %lf\n", expected_ci);
    printf("Variance of ci = %lf\n", variance);
    return 0;
}