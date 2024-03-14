/*Author : Maanas Bhaya, 2203117
To calculate the brightest area in a 2D array.
In this program, for the sake of simplicity, we have assumed the array in the main() function. We can also take inputs from 
the user for each element and then compute the result.*/

#include <iostream>
#include <climits>
using namespace std;

struct subarray
{
  int sum;
  int leftindex;
  int rightindex;
  int indexMax;			//To store the index of the maximum sum among all the sums ending in a particular elemnt.
};

int maximum (int a, int b)
{
  if (a >= b)
	return a;
  else
	return b;
}

int minimum (int i, int j)
{
  if (i <= j)
	return i;
  return j;
}

struct subarray arrayMax (struct subarray a[], int len)			//This is a function to calculate the maximum element in the array S, as S was defined in Q2.
{
  struct subarray max;
  max.sum = INT_MIN;
  max.leftindex = 0;
  max.rightindex = 0;
  int index;

  for (int i = 0; i < len; i++)
	{
	  if (a[i].sum > max.sum)
		{
		  max.sum = a[i].sum;
		  max.leftindex = a[i].leftindex;
		  max.rightindex = a[i].rightindex;
		  max.indexMax = i;
		}
	}
	  return max;
}

  int sumArray (int a[][3], int m, int n)		//A function to calculate the sum of an array
  {
	int sum = 0;
	for (int i = 0; i < m; i++)
	  {
		for (int j = 0; j < n; j++)
		  {
			sum += a[i][j];
		  }
	  }

	return sum;
  }

  void lineartime (int *a, int length, struct subarray *s)      //The lineartime maximum subarray algorithm described in Q2.
  {

	if (length == 1)
	  {
		s[0].sum = a[0];
		s[0].leftindex = 0;
		s[0].rightindex = 0;
		return;
	  }
	lineartime (a, length - 1, s);
	int val = a[length - 1];
	s[length - 1].sum = maximum (val, s[length - 2].sum + val);
	if (s[length - 1].sum == val)
	  {
		s[length - 1].leftindex = length - 1;
		s[length - 1].rightindex = length - 1;
	  }
	else if (s[length - 1].sum == val + s[length - 2].sum)
	  {
		s[length - 1].leftindex = s[length - 2].leftindex;
		s[length - 1].rightindex = length - 1;
	  }
	return;
}

void brightestArea (int a[][3], int m, int n) {
    
    int startrow, startcol, endrow, endcol;
	struct subarray tempresultarray[m];		//This array will store all the subarray sums ending in a particular index i.
	
	for (int i = 0; i < m; i++) {
	    
		struct subarray *tempresult = (struct subarray*)malloc(n * sizeof(struct subarray));
		int temparray[3];			//To store each row of the matrix.
		
		for (int j = 0; j < n; j++)
		{
			temparray[j] = a[i][j];
		}
		cout<<temparray[0]<<"\t"<<temparray[1]<<"\t"<<temparray[2]<<endl;
		lineartime (temparray, n, tempresult);
		//cout<<tempresult[2].sum<<endl;;
		int sumlinear = 0, maxs = INT_MIN, left, right;
		
		for(int k = 0; k < n; k++) {		//Iterating over tempresult.
		
		    sumlinear = tempresult[k].sum;
		    
		    if(sumlinear > maxs) {
		        maxs = sumlinear;
		        left = tempresult[k].leftindex;
		        right = tempresult[k].rightindex;
		    }
		}
		// cout<<maxs<<endl;
		tempresultarray[i].sum = maxs;		//Updating tempresultarray with the max sum in each row.
		tempresultarray[i].leftindex = left;
		tempresultarray[i].rightindex = right;
	  }

	struct subarray maxSubarray = arrayMax (tempresultarray, m);
	int res = maxSubarray.sum;
	startrow = maxSubarray.indexMax;
	endrow = maxSubarray.indexMax;
	startcol = maxSubarray.leftindex;
	endcol = maxSubarray.rightindex;
	// cout<<res<<endl;
	// cout<<maxSubarray.rightindex<<", "<<maxSubarray.leftindex<<", "<<maxSubarray.indexMax<<endl;
	
	for (int i = 0; i < m; i++) {
	    if (i == maxSubarray.indexMax) continue;
	    int sumcmp = 0;
		int temparr[abs(maxSubarray.indexMax - i) + 1][3];
		
		for (int l = minimum(maxSubarray.indexMax, i); l <= maximum(maxSubarray.indexMax, i); l++) {
		    
		    for(int p = minimum (maxSubarray.leftindex,tempresultarray[i].leftindex); p <=maximum(maxSubarray.rightindex,tempresultarray[i].rightindex); p++) {
		        
		        temparr[l - minimum(maxSubarray.indexMax, i)][p - minimum (maxSubarray.leftindex,tempresultarray[i].leftindex)] = a[l][p];
		        sumcmp += a[l][p];
		        // cout<<a[l][p]<<", ";
		    }
		    // cout<<endl;
		}
		//int sumcmp = sumArray(temparr, abs(maxSubarray.indexMax - i) + 1, maximum(maxSubarray.rightindex,tempresultarray[i].rightindex) - minimum (maxSubarray.leftindex,tempresultarray[i].leftindex) + 1);
		// cout <<sumcmp<<endl;
	    if (sumcmp > res) {		//Checking whether this row's max subarray should be included. If it is to be included, we must add the entire rows in between too, which we have implemented in the sumArray function.
	        res = sumcmp;
	        startrow = minimum(maxSubarray.indexMax, i);
	        startcol = minimum(maxSubarray.leftindex, tempresultarray[i].leftindex);
	        endrow = maximum(maxSubarray.indexMax, i);
	        endcol = maximum(maxSubarray.rightindex,tempresultarray[i].rightindex);
	    }
		
	}
	
	cout<<"The brightest area has a sum of: "<<res<<endl;
	cout<<"Starting from(indices start from 0): ("<<startrow<<", "<<startcol<<") to ("<<endrow<<", "<<endcol<<")"<<endl;
}

void subtract128(int a[][3], int m, int n) {		//To do the preprocessing, i.e. subtracting 128 from the elements.
	for(int i = 0; i < m; i++) {
		for(int j = 0; j < n; j++) {
			a[i][j] -= 128;
		}
	}
}


int main () {
    
	int m = 5;
	int n = 3;
	int a[5][3] =
			{ {123, 113, 44}, {159, 114, 32}, {54, 97, 109}, {81, 115, 3},
			{71, 120, 52} };
	
	subtract128(a, m, n);
	brightestArea (a, m, n);
}
