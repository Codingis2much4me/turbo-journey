#include <iostream>
#include <climits>
using namespace std;

struct subarray {
    int startindex;
    int endindex;
    int sum;
};

int max(int a, int b, int c) {
    if (a >= b && a >= c) return a;
    else if(a <= b && b >= c) return b;
    else return c;
}

struct subarray maxCrossingSubarray(int *arr, int low, int mid, int high) {
    struct subarray var;
    int leftsum = INT_MIN, sum = 0, leftindex;
    int rightsum = INT_MIN, rightindex;
    for(int i = mid; i >= low; i--) {
        sum += arr[i];
        if (sum > leftsum) {
            leftsum = sum;
            leftindex = i;
        }
    }
    sum = 0;
    for(int j = mid+1; j <= high; j++) {
        sum += arr[j];
        if(sum > rightsum) {
            rightsum = sum;
            rightindex = j;
        }
    }
    var.startindex = leftindex;
    var.endindex = rightindex;
    var.sum = leftsum + rightsum;
    return var;
}

struct subarray maxsubarray(int *arr, int low, int high) {
    if (low == high) {
        struct subarray result;
        result.startindex = low;
        result.endindex = high;
        result.sum = arr[low];
        return result;
    }
    
    int mid = (low + high) / 2;
    struct subarray array1 = maxsubarray(arr, 0, mid);
    struct subarray array2 = maxsubarray(arr, mid + 1, high);
    struct subarray array3 = maxCrossingSubarray(arr, low, mid, high);
    if (array1.sum >= array2.sum && array1.sum >= array3.sum) return array1;
    else if(array2.sum >= array1.sum && array2.sum >= array3.sum) return array2;
    else return array3;
}

int main() {
    int len;
    cout<<"Length: "<<endl;
    cin>>len;
    cout<<"Enter elements: "<<endl;
    int *arr = (int*)malloc(len*sizeof(int));
    for(int i = 0; i < len; i++) {
        cin>>arr[i];
    }
    struct subarray final = maxsubarray(arr, 0, len);
    cout<<"leftindex: "<<final.startindex<<endl;
    cout<<"rightindex: "<<final.endindex<<endl;
    cout<<"max sum: "<<final.sum<<endl;
}
