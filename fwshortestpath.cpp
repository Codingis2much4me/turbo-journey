#include <iostream>
#include <climits>
#include <vector>
#include <algorithm>
using namespace std;

void fw(int **w_adj, int **d, int **p, int n) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(w_adj[i][j] != 0) d[i][j] = w_adj[i][j];
            else if(i == j) d[i][j] = 0;
            else d[i][j] = INT_MAX;
        }
        p[i][i] = i;
    }
    
    for(int k = 0; k < n; k++) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j< n; j++) {
                if(d[i][k] < INT_MAX && d[k][j] < INT_MAX && i != k && j != k) {
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
                    if(d[i][j] == d[i][k] + d[k][j]) {
                        p[i][j] = k;
                    }
                    else p[i][j] = i;
                }
            }
        }
    }
}

int main() {
    cout<<"Enter the number of nodes in the graph: "<<endl;
    int nodes;
    cin>>nodes;
    int** wa = (int**)malloc(nodes * sizeof(int*));
    int** ancestors = (int**)malloc(nodes*sizeof(int*));
    int **distance = (int**)malloc(nodes * sizeof(int*));
    for(int i = 0; i < nodes; i++) {
        wa[i] = (int*)malloc(nodes * sizeof(int));
        ancestors[i] = (int*)malloc(nodes * sizeof(int));
        distance[i] = (int*)malloc(nodes* sizeof(int));
    }
    cout<<"Enter the adjacency matrix for entries: "<<endl;
    for(int i = 0; i < nodes; i++) {
        for(int j = 0; j < nodes; j++) {
            cout<<i<<", "<<j<<" : ";
            cin>>wa[i][j];
        }
    }
    fw(wa, distance, ancestors, nodes);
    while(true) {
        cout<<endl;
        vector<int>reconstruct;
        cout<<"Want to the know the shortest path? Enter the indices of i and j: "<<endl;
        int i;
        cout<<"i: ";
        cin>>i;
        cout<<endl<<"j: ";
        int j;
        cin>>j;
        if(i <= -1 || j <= -1) break;
        cout<<endl<<"The length of the shortest path between the vertices is: "<<distance[i][j]<<endl;
        cout<<"Path of the vertices is: ";
        cout<<i<<" ";
        while(ancestors[i][j] != i) {
            reconstruct.push_back(ancestors[i][j]);
            j = ancestors[i][j];
        }
        reverse(reconstruct.begin(), reconstruct.end());
        
        for(int i = 0; i < reconstruct.size(); i++) cout<<reconstruct[i]<<" ";
        cout<<j;
    }
}
