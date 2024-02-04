//a is the base
//n is the exponent
//mult is a global variable counting the number of multiplications.

#include <iostream>
#include <math.h>
using namespace std;
int mult = 0;
int exp_by_squaring(int a, int n) {
    mult++;
    if(n==0) return 1;
    int c = exp_by_squaring(a, n/2);
    c*=c;
    if(n % 2 == 1){
    c = c * a;
    }
    return c;
}

int main()
{
    cout<<"Which number do you want to exponentiate? : ";
    int a;
    cin>>a;
    cout<<"What power do you want to raise it to? :";
    int n;
    cin>>n;
    int counter = 0;
    while(counter <= n) {
        mult = 0;
        int result = exp_by_squaring(a, counter);
        cout<<counter<<","<<mult<<endl;
        counter ++;
    }

    return 0;
}
