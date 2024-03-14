#include <iostream>
using namespace std;

struct subarray {
    int sum;
    int leftindex;
    int rightindex;
};

int maximum(int a, int b) {
    if(a >=b) return a;
    else return b;
}

void lineartime(int *a, int length, struct subarray* s) {
    
    if(length == 1) {
        s[0].sum = a[0];
        s[0].leftindex = 0;
        s[0].rightindex = 0;
        return;
    }
    lineartime(a, length - 1, s);
    int val = a[length-1];
    s[length - 1].sum = maximum(val, s[length - 2].sum + val);
    if (s[length - 1].sum == val) {
        s[length - 1].leftindex = length - 1;
        s[length - 1].rightindex = length - 1;
    }
    else if (s[length - 1].sum == val + s[length - 2].sum) {
        s[length - 1].leftindex = s[length - 2].leftindex;
        s[length - 1].rightindex = length - 1;
    }
    return;
}
    // for(int i = 1; i < length; i++) {
    //     int val = a[i];
    //     if(val >= maxsum + val) {
    //         result[i].leftindex = i;
    //         result[i].rightindex = i;
    //         result[i].sum = val;
    //         maxsum = val;
    //     }
    //     else {
    //         result[i].leftindex = result[i-1].leftindex;
    //         result[i].rightindex = i;
    //         result[i].sum = maxsum + val;;
    //         maxsum = maxsum + val;
    //     }
    // }
    // return result;

int main() {
    int len;
    cout<<"Length: "<<endl;
    cin>>len;
    cout<<"Elements: "<<endl;
    int *arr = (int*)malloc(len*sizeof(int));
    struct subarray* final = (struct subarray*)malloc(len*sizeof(struct subarray));
    for(int i = 0; i < len; i++) {
        cin>>arr[i];
    }
    lineartime(arr, len, final);
    int maxs = 0, left = 0, sum = 0, right = 0;
    for(int i = 0; i < len; i++) {
        sum = final[i].sum;
        if(sum > maxs) {
            maxs = sum;
            left = final[i].leftindex;
            right = final[i].rightindex;
        }
    }
    cout<<"maxsum: "<<maxs<<endl;
    cout<<"Leftindex: "<<left<<endl;
    cout<<"rightindex: "<<right<<endl;
}
