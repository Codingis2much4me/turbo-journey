#include <iostream>
using namespace std;


void add_matrices(int **a, int **b, int **c, int n) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
}

void multiply_matrices(int **a, int **b, int **c, int n) {
    if (n == 2) {
        int p1 = (a[0][0] + a[1][1]) * (b[0][0] + b[1][1]);
        int p2 = (a[1][0] + a[1][1]) * b[0][0];
        int p3 = a[0][0] * (b[0][1] - b[1][1]);
        int p4 = a[1][1] * (b[1][0] - b[0][0]);
        int p5 = (a[0][0] + a[0][1]) * b[1][1];
        int p6 = (a[1][0] - a[0][0]) * (b[0][0] + b[0][1]);
        int p7 = (a[0][1] - a[1][1]) * (b[1][0] + b[1][1]);

        c[0][0] = p1 + p4 - p5 + p7;
        c[0][1] = p3 + p5;
        c[1][0] = p2 + p4;
        c[1][1] = p1 - p2 + p3 + p6;
        return;
    }

    int **a11, **a12, **a21, **a22;
    int **b11, **b12, **b21, **b22;
    int **c11, **c12;
    
    a11 = (int**)malloc((n/2) * sizeof(int*)); a12 = (int**)malloc((n/2) * sizeof(int*)); a21 = (int**)malloc((n/2) * sizeof(int*)); a22 = (int**)malloc((n/2) * sizeof(int*));
    b11 = (int**)malloc((n/2) * sizeof(int*)); b12 = (int**)malloc((n/2) * sizeof(int*)); b21 = (int**)malloc((n/2) * sizeof(int*)); b22 = (int**)malloc((n/2) * sizeof(int*));
    c11 = (int**)malloc((n/2) * sizeof(int*)); c12 = (int**)malloc((n/2) * sizeof(int*));
    for(int i = 0; i < n/2; i++) {
        a11[i] = (int*)malloc((n/2) * sizeof(int)); 
        a12[i] = (int*)malloc((n/2) * sizeof(int)); 
        a21[i] = (int*)malloc((n/2) * sizeof(int));
        a22[i] = (int*)malloc((n/2) * sizeof(int));
        b11[i] = (int*)malloc((n/2) * sizeof(int)); 
        b12[i] = (int*)malloc((n/2) * sizeof(int)); 
        b21[i] = (int*)malloc((n/2) * sizeof(int)); 
        b22[i] = (int*)malloc((n/2) * sizeof(int));
        c11[i] = (int*)malloc((n/2) * sizeof(int)); 
        c12[i] = (int*)malloc((n/2) * sizeof(int));
    }

    for(int i = 0; i < n/2; i++) {
        for(int j = 0; j < n/2; j++) {
            a11[i][j] = a[i][j];
            a12[i][j] = a[i][j + n/2];
            a21[i][j] = a[i + n/2][j];
            a22[i][j] = a[i + n/2][j + n/2];
            
            b11[i][j] = b[i][j];
            b12[i][j] = b[i][j + n/2];
            b21[i][j] = b[i + n/2][j];
            b22[i][j] = b[i + n/2][j + n/2];
        }
    }

    multiply_matrices(a11, b11, c11, n/2);
    multiply_matrices(a12, b21, c12, n/2);
    add_matrices(c11, c12, c11, n/2);
    for(int i = 0; i < n/2; i ++) {
        for(int j = 0; j < n/2; j++) {
            c[i][j] = c11[i][j];
        }
    }

    multiply_matrices(a11, b12, c11, n/2);
    multiply_matrices(a12, b22, c12, n/2);
    add_matrices(c11, c12, c11, n/2);
    for(int i = 0;i < n/2; i ++) {
        for(int j = n/2;j < n;j ++) {
            c[i][j] = c11[i][j-n/2];
        }
    }

    multiply_matrices(a21, b11, c11, n/2);
    multiply_matrices(a22, b21, c12, n/2);
    add_matrices(c11, c12, c11, n/2);
    for(int i = n/2; i < n; i++) {
        for(int j = 0;j < n/2;j ++) {
            c[i][j] = c11[i-n/2][j];
        }
    }
    multiply_matrices(a21, b12, c11, n/2);
    multiply_matrices(a22, b22, c12, n/2);
    add_matrices(c11, c12, c11, n/2);
    for(int i = n/2; i < n; i++) {
        for(int j = n/2; j < n; j++) {
            c[i][j] = c11[i-n/2][j-n/2];
        }
    }


    for(int i = 0; i < n/2; i++) {
        free(a11[i]); free(a12[i]); free(a21[i]); free(a22[i]);
        free(b11[i]); free(b12[i]); free(b21[i]); free(b22[i]);
        free(c11[i]); free(c12[i]);
    }
    free(a11); free(a12); free(a21); free(a22);
    free(b11); free(b12); free(b21); free(b22);
    free(c11); free(c12);
}


int main() {
    int n = 4; // Size of matrices

    // Allocate memory for matrices
    int **a = (int**)malloc(n * sizeof(int*));
    int **b = (int**)malloc(n * sizeof(int*));
    int **c = (int**)malloc(n * sizeof(int*));
    for(int i = 0; i < n; i++) {
        a[i] = (int*)malloc(n * sizeof(int));
        b[i] = (int*)malloc(n * sizeof(int));
        c[i] = (int*)malloc(n * sizeof(int));
    }

    // Input matrices
    cout << "Enter elements of matrix A:" << endl;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
    
    cout << "Enter elements of matrix B:" << endl;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> b[i][j];
        }
    }

    // Multiply matrices
    multiply_matrices(a, b, c, n);

    // Output result
    cout << "Resultant matrix C:" << endl;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cout << c[i][j] << "\t";
        }
        cout << endl;
    }

    // Deallocate memory
    for(int i = 0; i < n; i++) {
        free(a[i]);
        free(b[i]);
        free(c[i]);
    }
    free(a);
    free(b);
    free(c);

    return 0;
}
