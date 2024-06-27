#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct tnode {
    int data;
    struct tnode* left;
    struct tnode* right;
};

struct answer {
    struct tnode* parent;
    int direction;
};

struct reconstruct {
    int value;
    int index;
};

int min(int a, int b) {
    if(a <= b) return a;
    return b;
}

struct tnode* add(int val, struct tnode* root) {
    if(root == NULL) {
        struct tnode* temp = (struct tnode*)malloc(sizeof(struct tnode));
        temp->left = NULL;
        temp->right = NULL;
        temp->data = val;
        return temp;
    }
    if(val < root->data) root->left = add(val, root->left);
    else root->right = add(val, root->right);
    return root;
}

struct answer* searchKey(struct tnode* root, int val) {
    struct answer* ans = (struct answer*)malloc(sizeof(struct answer));
    ans->parent = NULL;
    ans->direction = 0;
    if(root == NULL) return ans;
    if(val == root->data) {
        ans->parent = NULL;
        ans->direction = 0;
        return ans;
    }
    else if(root->left != NULL && val == root->left->data) {
        ans->parent = root;
        ans->direction = -1;
        return ans;
    }
    else if(root->right != NULL && val == root->right->data) {
        ans->parent = root;
        ans->direction  = 1;
        return ans;
    }
    else {
        if (val < root->data) return searchKey(root->left, val);
        else return searchKey(root->right, val);
    }
    return ans;
}

void printTree(struct tnode* root) {
    if(root == NULL) return;
    cout<<root->data<<" ";
    printTree(root->left);
    printTree(root->right);
}

struct tnode* rotateTree(struct tnode* parent, struct tnode* child, int dir) {
    struct tnode* val1 = NULL;
    if(child == NULL) return NULL;
    if(dir == 1) { //right rotation wrt child
        val1 = child->left;
        child->left = val1->right;
        val1->right = child;
        if(parent != NULL) {
            if(parent->left == child) parent->left = val1;
            else parent->right = val1;
        }
    }
    if(dir == -1) {
        val1 = child->right;
        child->right = val1->left;
        val1->left = child;
        if(parent != NULL) {
            if(parent->left == child) parent->left = val1;
            else parent->right = val1;
        }
    }
    return val1;
}

struct tnode* adjustTree(struct tnode* root, struct reconstruct **s, vector<int>const& a, int start, int end) {
    if(start > end || root == NULL) return root;
    int ultnode = a[s[start][end].index];
    if(ultnode == root->data) return root;
    struct answer* temporary;
    temporary = searchKey(root, root->data);
    struct tnode* temp = temporary->parent;
    cout << " * " <<'\n';
    while(true) {
        temporary = searchKey(root, ultnode);
        if(temporary->parent == root) break;
        else if(temporary->direction == 1) {
            temporary->parent = rotateTree(searchKey(root, temporary->parent->data)->parent, temporary->parent, -1);
        }
        else if(temporary->direction == -1) {
            temporary->parent = rotateTree(searchKey(root, temporary->parent->data)->parent, temporary->parent, 1);
        }else break;
    }
    if(temporary->direction == 1) {
        temporary->parent = rotateTree(NULL, temporary->parent, -1);
    }
    else if(temporary->direction == -1) {
        temporary->parent = rotateTree(NULL, temporary->parent, 1);
    }
    return temporary->parent;
    //delete temporary;
}
struct reconstruct constructMatrix(struct tnode* root, int freq[4][2], struct reconstruct **s, vector<int>const& a) {
    for(int i = 0; i < 4; i++) {
        s[i][i].value = freq[i][1];
        s[i][i].index = freq[i][0] -1;
    }
    for(int p = 1; p < 4; p++) {
        for(int i = 0; i < 4 - p; i++) {
            int j = i + p;
            int sum = 0;
            for(int k = i; k <= j; k++) {
                sum += freq[k][1];
            }
            s[i][j].value = INT_MAX;
            int temp;
            for(int m = i; m <= j; m++) {
                if (m == 0) temp = sum + s[m+1][j].value;
                else if(m == j) temp = sum + s[i][m - 1].value;
                else temp = sum + s[i][m-1].value + s[m+1][j].value;
                if(temp < s[i][j].value) {
                    s[i][j].value = temp;
                    s[i][j].index = m;
                    cout<<i<<", "<<j<<" "<<temp<<endl;
                }
            }
        }
    }
    cout<<"Matrix: "<<endl;
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j< 4; j++) {
            cout<<"("<<s[i][j].value<<","<<s[i][j].index<<")\t";
        }
        cout<<endl;
    }
    return s[0][3];
}

struct tnode* optimizeTree(struct tnode* root, struct reconstruct **s, vector<int>const& a, int start, int end) {
    cout << start << ' ' << end << '\n';
    if(start > end) return NULL;
    if(start == end) return root;
    int ultnodeindex = s[start][end].index;
    cout << ultnodeindex << '\n';
    root = adjustTree(root, s, a, start, end);
    printTree(root);
    if(root != NULL){
        root->left = optimizeTree(root->left, s, a, start, ultnodeindex-1);
        root->right = optimizeTree(root->right, s, a, ultnodeindex+1, end);
    }
    return root;
}

int main() {
    cout<<"Create the BST: "<<endl;
    struct tnode* root = NULL;
    int val;
    vector<int>values;
    while(true) {
        cout<<"keep entering values...Enter negative to exit" <<endl;
        cin>>val;
        if(val < 0) break;
        root = add(val, root);
        values.push_back(val);
    }
    cout<<"See your entered tree!"<<endl;
    printTree(root);
    cout<<"Search for a key? "<<endl;
    int searchval;
    cin>>searchval;
    struct answer* a = (struct answer*)malloc(sizeof(struct answer));
    a->parent = NULL;
    a->direction = 0;
    a = searchKey(root, searchval);
    cout<<"Found a key?: "<<a->parent<<" "<<a->direction;
    // cout<<"Rotate the tree? "<<endl;
    // cout<<"Direction: "<<endl;
    // int direc;
    // cin>>direc;
    // root->right = rotateTree(root, root->right, direc);
    // cout<<"New root data!: "<<root->data<<endl;
    //printTree(root);
    int freq[4][2] = { {1, 15}, {2, 5}, {3, 22}, {4, 30}};
    cout<<"Hello1"<<endl;
    struct reconstruct **sol = (struct reconstruct**) malloc(4 * sizeof(struct reconstruct*));
    for(int i = 0; i < 4; i++) {
        sol[i] = (struct reconstruct*)malloc(4 * sizeof(struct reconstruct));
    }
    cout<<"The minimum cost is: "<<endl;
    struct reconstruct r = constructMatrix(root, freq, sol, values);
    cout<<r.value<<" and the new root should be: "<<values[r.index];
    cout<<"Hello";
    root = optimizeTree(root, sol, values, 0, values.size() - 1);
    //adjustTree(root, sol, values, 0, values.size() - 1);
    cout<<"New root data: "<<root->data<<endl;
    printTree(root);
}