/*This program writes a function quicksort that sorts a given array of integers using the quicksort algorithm. In the main function,
 we Take an integer k from the user and for every i belonging to {1, 2, 3, ..., k} take a random integer array of size n = 2^i and output
the time T(n) (in terms of number of operations) taken by quicksort to sort the array. For each i, calculate the ratio ci = T(n)/nlogn
and print the tuple (i, 2^i, T(2^i), i*2^i, ci) for each i on a new row. We find the expected value and variance of ci and print it.*/
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
    {
    *count_the_operations += 1; //Returning if base case;
        return;
    }
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
    quicksort(a, startindex, j - startindex + 1); //recursive call on both partitions
    quicksort(a, i, startindex + n - i);
    
}

int main() {
    srand(time(0));
    double expected_ci = 0, ci_square = 0, expected_ci_square = 0, variance = 0; //Initializing variables to store E[X], Var[x}]
    printf("Enter the value of k: ");
    int k;
    scanf("%d", &k);
    for(int i = 1; i <= k; i++) {
        int n = pow(2, i);
        int a[n];
        for(int j = 0; j < n; j++)
            a[j] = rand() % 100; //Taking random integers less than 100
        count_the_operations = (int *)malloc(sizeof(int));
        *count_the_operations = 0;  //Initalizing counter to zero.
        quicksort(a, 0, n);
        double ci = (double)(*count_the_operations) / (n * log2(n));
        
        printf("(i, 2^i, T(2^i), i*2^i, ci) = (%d, %d, %d, %d, %lf)\n", i, n, *count_the_operations, i * n, ci);
        free(count_the_operations);
        
        if(i > 5) {  //Taking values > 5
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
}

