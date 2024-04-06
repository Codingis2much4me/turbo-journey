#include <iostream>
#include <vector>
#include <climits>
using namespace std;


struct answer {
    int cost;
    int index;
};

struct answer matrixParens(vector<int>const& a, vector<vector<int>>& s) {
    struct answer var;
    int n = a.size() - 1;
    vector<vector<int>>m(n, vector<int>(n));
    //vector<vector<int>>s(n, vector<int>(n));
    for(int i = 0; i < n; i++) {
        m[i][i] = 0;
        s[i][i] = -1;
    }
    for(int l = 1; l < n; l++) {
        for(int p = 0; p < n - l; p++) {
            int j = p + l;
            m[p][j] = INT_MAX;
            for(int k = p; k < j; k++) {
                int q = m[p][k] + m[k+1][j] + a[p] * a[k+1] * a[j+1];
                if(q < m[p][j]) {
                    m[p][j] = q;
                    s[p][j] = k;
                }
            }
        }
    }
    var.cost = m[0][n-1];
    var.index = s[0][n-1];
    return var;
}

int main() {
    cout<<"Enter the number of matrices"<<endl;
    int num;
    cin>>num;
    vector<int> dims(num+1);
    vector<vector<int>>s (num, vector<int>(num));
    vector<int> parens;
    cout<<"Enter a list of (n+1) dimensions: "<<endl;
    for(int i = 0; i <= num; i++) cin>>dims[i];
    struct answer ans;
    ans = matrixParens(dims, s);
    cout<<"The minimum cost is: "<<ans.cost<<endl;
    int index = ans.index;
    // parens.push_back(index);
    parens.push_back(index);
    int index2 = index;
    while(true) {
        index2 = s[index2+1][num - 1];
        if(index2 == -1) break;
        parens.push_back(index2);
    }
    while(true)  {
        index = s[0][index];
        if(index == -1) break;
        parens.push_back(index);
    }
    cout<<"Parens inserted after indices: "<<endl;
    for(int i = 0; i < parens.size(); i++) cout<<parens[i]<<" ";
    
}
