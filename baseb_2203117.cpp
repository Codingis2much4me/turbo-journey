#include <iostream>
#include <cmath>
using namespace std;

char letter_array[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};			//This array stores the representations of the digits in case the base exceeds 10

int* base_b(int b, int n, char arr[], int& len) {					//We pass address of length as a parameter as it is modified.
    float length = log(n);
    float divi = log(b);
    int num_bits = floor(length / divi) + 1;					//The formula to get the number of bits required.
    len  = num_bits;												//Updating len
	
    cout<<"Number of bits reqd are: "<<num_bits<<endl;
	
    arr = (char*)malloc(num_bits*sizeof(char));
    int *a = (int*) malloc(num_bits*sizeof(int));

    int counter = num_bits -1;
    while(n != 0) {
        int d = n % b;
        arr[counter] = letter_array[d];
        a[counter] = d;
        counter--;
        n /= b;
    }
    
    for(int i = 0; i < num_bits; i++) {
        cout<<arr[i];
    }
    cout<<endl;
    return a;
}

int* addition(int b, int x , int y, int add_array[]) {
    char* x_rep;
    char* y_rep;
    int *x_num;
    int *y_num;
    int x_length = 0;
    int y_length = 0;
    x_num = base_b(b, x, x_rep, x_length);
    y_num = base_b(b, y, y_rep, y_length);
    
    //cout<<x_length<<","<<y_length<<endl;
    int length;
    int counter_add;
    int sum;
    
    if(x_length > y_length) {
        length = x_length;
    }
    else {
        length = y_length;
    }
    length +=1;							//As the length of the additionArray can be at most 1 more than max of the input lengths.
    counter_add = length;
    
    add_array = (int*)malloc((length) * sizeof(int));
    
    int counter_x = x_length;
    int counter_y = y_length;
	
    int carry_from_prev = 0;			//Initialising initial carry to be zero.
	
    while(counter_x >=0 || counter_y >= 0) {
        sum =  carry_from_prev;
        if(counter_x >= 0) sum += x_num[counter_x--];
        if(counter_y >= 0) sum += y_num[counter_y--];
        
        if(sum < b) {
            add_array[counter_add--] = sum;
            carry_from_prev = 0;
        }
        else {
            cout<<"Carry encountered..."<<endl;
            int* temp;
            char* temp_rep;
            int temp_len = 0;
            temp = base_b(b, sum, temp_rep, temp_len);
            sum = temp[1];
            carry_from_prev = temp[0];				//If a carry is present then it will be the MSB, or the first digit in the array.
            add_array[counter_add--] = sum;
        }
    }
    
    add_array[counter_add] = carry_from_prev;			//For storing the (m+1)th bit, if carry is present after m additions.
    
    cout<<"Final result(still in base b; space separated integers) is :"<<endl;
    for(int i = 0; i < length; i++) {
        cout<<add_array[i]<<" ";
    }
    cout<<endl;
    return add_array;
    
}

int main(){
    int number1, number2; 
    int* sum_array;
    cout<<"Enter two positive integers: "<<endl;
    cin>>number1>>number2;
    cout<<"Enter the base : "<<endl;
    int base;
    cin>>base;
    
    sum_array = addition(base, number1, number2, sum_array);
    
    free(sum_array);
}