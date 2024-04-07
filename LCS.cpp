#include <iostream>
#include <vector>
#include<algorithm>
using namespace std;


int lcs(vector<int>const& a, vector<int>const& b, vector<vector<int>>& c, int i, int j) {
    if(i == 0 || j == 0) return 0;
    
    // for(int i = 1; i <= m; i++) {
    //     for(int j = 1; j <= n; j++ ) {
    //         if(a[i-1] == b[j-1]) {
    //             c[i][j] = c[i-1][j-1] + 1;
    //             //reconstruct_lcs.push_back(a[i-1]);
    //         }
    //         else {
    //             c[i][j] = max(c[i-1][j], c[i][j-1]);
    //         }
    //     }
    // }
    c[i][j - 1] = lcs(a, b, c, i, j -1);
    c[i - 1][j] = lcs(a, b, c, i-1, j);
    if(a[i - 1] == b[j - 1]) c[i][j] = c[i-1][j-1] + 1;
    else c[i][j] = max(c[i-1][j], c[i][j-1]);
    return c[i][j];
}

void reconstruct(vector<int>const& a, vector<int>const& b, vector<vector<int>>const& c){
    int m = a.size();
    int n = b.size();
    int x = m, y = n;
    vector<int>reconstruct_lcs;
    while(x != 0 && y != 0) {
        if(a[x - 1] == b[y - 1]) {
            reconstruct_lcs.push_back(a[x - 1]);
            x = x - 1; 
            y = y - 1;
        }
        else if(c[x][y] == c[x - 1][y]) {
            x = x - 1;
        }
        else if(c[x][y] == c[x][y - 1]) {
            y = y - 1;
        }
    }
    reverse(reconstruct_lcs.begin(), reconstruct_lcs.end());
    
    cout<<"Reconstructed lcs: ";
    for(int i = 0; i < reconstruct_lcs.size();i++) cout<<reconstruct_lcs[i]<<" ";
    cout<<endl;
}

int main() {
    //cout<<"Enter the length of the two vectors: "<<endl;
    int m =7, n=6;
    //cin>>m>>n;
    vector<int> x = {1, 2, 3, 2, 4, 1, 2};
    vector<int> y = {2, 4, 3, 1, 2, 1};
    vector<vector<int>> c(m+1, vector<int>(n+1));
    for(int i = 0; i < m; i++) c[i][0] = 0;
    for(int j = 1; j < n; j++) c[0][j] = 0;
    //cout<<"First sequence: "<<endl;
    //for(int i = 0; i < m; i++) cin>>x[i];
    //cout<<"Second sequence: "<<endl;
    //for(int j = 0; j < n; j++) cin>>y[j];
    int len = lcs(x, y, c, m, n);
    cout<<"length of lis: "<<len<<endl;
    reconstruct(x, y, c);
}
