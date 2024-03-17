#include <iostream>
using namespace std;


int maximum(int a, int b) {
    if (a>=b) return a;
    return b;
}


void subseqsum(int *a, int len, int *s) {
    
    if(len == 1) {
        s[0] = a[0];
        return;
    }
    
    subseqsum (a, len - 1, s);
    if (len == 2) {
        s[1] = maximum(a[0], a[1]);
        return;
    }
    s[len - 1]= maximum(s[len - 3] + a[len - 1], s[len - 2]);
    return;
}

int main() { 
    int n;
    cout<<"Enter the length of the array: "<<endl;
    cin>>n;
    int *arr = (int*)malloc(n * sizeof(int));
    cout<<"Enter the elements of the array: "<<endl;
    for(int i = 0; i < n; i++) {
        cin>>arr[i];
    }
    int *sumarr = (int*)malloc(n * sizeof(int));
    subseqsum(arr, n, sumarr);
    cout<<"The maximum subsequence sum in the array is: "<<sumarr[n - 1];
}
