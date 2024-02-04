#include <iostream>

using namespace std;
int mults = 0;

void matrixprod(int a[][2], int b[][2]) {           //defining how to multiply two matrices
    int result[2][2] = {{0, 0}, {0, 0}};
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            for(int k = 0; k < 2; k++) {
                result[i][j] += a[i][k] * b[k][j];
                mults++;
            }
        }
    }
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            a[i][j] = result[i][j];
        }
    }
}

//Now it's time for the O(log n) algorithm

void exp_by_squaring_matrices(int a[][2], int k) {
    int temp[2][2];
    
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            temp[i][j] = a[i][j];
        }
    }
    if(k == 0 || k==1) return;
    exp_by_squaring_matrices(temp, k/2);
    matrixprod(temp, temp);
    if(k % 2 == 1)
    matrixprod(temp, a);
    
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            a[i][j] = temp[i][j];
        }
    }
} 

int main() {
    cout<<"Enter the value of n: "<<endl;
    int N;
    cin>>N;
    int n = 0;
    
    while(n <= N) {
        mults = 0;
        if (n==0 || n==1) cout << n << "," << mults<< endl;
        else{
            int a[2][2] = {{1, 1}, {1, 0}};
            //matrixpow()do something....
            exp_by_squaring_matrices(a, n-1);
            int fib_n = a[0][0];
            cout<<n<<","<<mults<<endl;
            
        }
        
        n++;
        //cout<<n<<","<<fib_n<<endl;
    }
    
}
