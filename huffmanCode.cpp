#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <map>
using namespace std;


struct tnode {
    struct tnode* left;
    struct tnode* right;
    char data;
};


struct minHeapNode {
    char data;
    struct minHeapNode *left, *right;
    unsigned frequency;
};

struct minHeap {
    unsigned size;
    unsigned capacity;
    struct minHeapNode** array;
};

struct tnode* createNode(char item) {
    struct tnode* node = (struct tnode*)malloc(sizeof(struct tnode));
    node->data = item;
    node->left = NULL;
    node->right = NULL;
    return node;
}

struct minHeapNode* createHuffmanNode(char item, int freq) {
    struct minHeapNode* newNode = (struct minHeapNode*)malloc(sizeof(struct minHeapNode));
    newNode->data = item;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->frequency = freq;
    return newNode;
}

void swapNodes(struct minHeapNode** a, struct minHeapNode** b) {
    struct minHeapNode* t = *a;
    *a = *b;
    *b = t;
}

struct minHeap* createMinHeap(unsigned capacity) {
    struct minHeap* newHeap = (struct minHeap*)malloc(sizeof(struct minHeap));
    newHeap->size = 0;
    newHeap->capacity = capacity;
    newHeap->array = (struct minHeapNode**)malloc(newHeap->capacity * sizeof(struct minHeapNode*));
    return newHeap;
}


void heapify(struct minHeap* heap, int idx) {
    int smallest = idx;
    int left = 2*idx + 1;
    int right = 2 * idx + 2;
    if(left < heap->size && heap->array[left]->frequency < heap->array[smallest]->frequency)
    smallest = left;
    
    if(right < heap->size && heap->array[right]->frequency < heap->array[smallest]->frequency)
    smallest = right;
    
    if(smallest != idx) {
        swapNodes(&heap->array[smallest], &heap->array[idx]);
        heapify(heap,smallest);
    }
}

bool checkSize(struct minHeap* heap) {
    return (heap->size == 1);
}



void insertHeap(struct minHeap* heap, struct minHeapNode* node) {
    ++heap->size;
    int i = heap->size - 1;
    while(i && node->frequency < heap->array[(i - 1)/2]->frequency) {
        heap->array[i] = heap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    heap->array[i] = node;
}

struct minHeapNode* extractMin(struct minHeap* heap) {
    //if(heap->head == NULL) return NULL;
    struct minHeapNode* temp = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1];
    --heap->size;
    heapify(heap, 0);
    return temp;
}

void buildHeap(struct minHeap* heap) {
    int n = heap->size - 1;
    int i;
    for(i = (n - 1) / 2; i >= 0; --i) {
        heapify(heap, i);
    }
}

struct minHeap* createAndBuildHeap(map<char, int>&freq) {
    struct minHeap* heap = createMinHeap(freq.size());
    int i = 0;
    for(auto j:freq) {
        heap->array[i++] = createHuffmanNode(j.first, j.second);
    }
    
    heap->size = freq.size();
    buildHeap(heap);
    return heap;
}

struct tnode* randomCodeTree(char symbolSet[], int n) {
    vector<char>leftSet, rightSet;
    struct tnode* root = createNode('N');
    if(n== 1) {
        root->data = symbolSet[0];
        return root;
    }
    else if(n==0) return NULL;
    root->data = 'N';
    leftSet.push_back(symbolSet[0]);
    rightSet.push_back(symbolSet[1]);
    for(int i = 2; i < n; i++) {
        float coin = static_cast<float>(rand()) / RAND_MAX;
        if(coin >= 0.5) rightSet.push_back(symbolSet[i]);
        else leftSet.push_back(symbolSet[i]);
    }
    
    root->left = randomCodeTree(&leftSet[0], leftSet.size());
    root->right = randomCodeTree(&rightSet[0], rightSet.size());
    return root;
}


void printTreeInorder(struct tnode* root) {
    if(root == NULL) return;
    printTreeInorder(root->left);
    cout<<root->data<<" ";
    printTreeInorder(root->right);
}

void printTreePreorder(struct tnode* root) {
    if(root == NULL) return;
    cout<<root->data<<" ";
    printTreePreorder(root->left);
    printTreePreorder(root->right);
}

void printFinalTree(struct minHeapNode* root) {
    if(root == NULL) return;
    cout<<root->data<<", "<<root->frequency<<endl;
    printFinalTree(root->left);
    printFinalTree(root->right);
}

void printHeap(struct minHeap* heap) {
    cout<<"Heap size is: "<<heap->size<<endl;
    for(int i = 0; i < heap->size; i++) {
        cout<<heap->array[i]->data<<" ";
    }
    cout<<endl;
}

void createCodeTable(struct tnode* root, vector<char>&codebuf, vector<char>&code_char, vector<vector<char>>&code) {
    if (root == NULL) return;
    if (root->left == NULL && root->right == NULL) {
        code_char.push_back(root->data);
        code.push_back(codebuf);
        return;
    }
    else {
        if(root->left != NULL) {
            codebuf.push_back('0');
            createCodeTable(root->left, codebuf, code_char, code);
        }
        codebuf.pop_back();
        if(root->right != NULL) {
            codebuf.push_back('1');
            createCodeTable(root->right, codebuf, code_char, code);
        }
        codebuf.pop_back();
    }
    
    
}

void createHuffmanCodeTable(struct minHeapNode* root, vector<char>&codebuf, vector<char>&code_char, vector<vector<char>>&code) {
    if (root == NULL) return;
    if(root->left) {
        codebuf.push_back('0');
        createHuffmanCodeTable(root->left, codebuf, code_char, code);
    }
    if(root->left) codebuf.pop_back();
    if(root->right) {
        codebuf.push_back('1');
        createHuffmanCodeTable(root->right, codebuf, code_char, code);
    }
    if(root->right) codebuf.pop_back();
    if(!(root->left) && !(root->right)) {
        code_char.push_back(root->data);
        code.push_back(codebuf);
    }
}

void createFrequencyTable(ifstream &inputFile, map<char, int>&table) {
    string line;
    cout<<"String read from file: ";
    while(getline(inputFile, line)) {
        stringstream ss(line);
        string word;
        while(ss>>word) {
            cout<<word<<" ";
            for(auto j : word) {
                table[j]++;
            }
        }
    }
    cout<<endl;
    cout<<"Frequency Table!: "<<endl;
    for(auto it: table) {
        cout<<it.first<<" "<<it.second<<endl;
    }
   
}

struct minHeapNode* createHuffmanTree(map<char, int>& freq) {
    
    struct minHeapNode *left, *right, *parent;
    
    struct minHeap* heap = createAndBuildHeap(freq);

    while (!checkSize(heap)) {
        left = extractMin(heap);
        right = extractMin(heap);
        cout<<left->data<<" "<<left->frequency<<", "<<right->data<<" "<<right->frequency<<endl;
        
        parent = createHuffmanNode('N', left->frequency+right->frequency);
        parent->left = left;
        parent->right = right;
        insertHeap(heap, parent);
        printHeap(heap);
    }
    // cout<<endl<<"printing the heap: "<<endl;
    // printHeap(heap);
    return extractMin(heap);
}

void createMap(map<char, vector<char>>&final, vector<vector<char>>const &code, vector<char>const &codechar) {
    //vector<char> temp;
    for(int i = 0; i < codechar.size(); i++) {
        final[codechar[i]] = code[i];
    }
    
    cout<<"printing the map: "<<endl;
    for(auto j:final) {
        cout.put(j.first)<<" ";
        for(int k = 0; k < j.second.size(); k++) {
            cout.put(j.second[k]);
        }
        cout<<endl;
    }
}

void encode(ifstream &inputFile, fstream &outputFile, const map<char, vector<char>> &final) {
    string line;
    
    while (getline(inputFile, line)) {
        for (char j : line) {
            if (j == ' ') {
                // Encode spaces if necessary
                outputFile.put(' ');
                continue;
            }
                
            auto it = final.find(j);
            if (it != final.end()) {
                for (char code : it->second) {
                    outputFile.put(code);
                }
            } else {
                // Handle characters not found in the final map
                cerr << "Character '" << j << "' not found in encoding map." << endl;
                // You might want to handle this error differently
            }
        }
        
    }
}

void createReverseMap(map<char, vector<char>>const& final, map<vector<char>, char> &finalreverse) {
    for(auto j: final) {
        finalreverse[j.second] = j.first;
    }
    
    cout<<"Created Reverse Map: "<<endl;
    for(auto j: finalreverse) {
        for(int k = 0; k < j.first.size(); k++) {
            cout<<j.first[k];
        }
        cout<<" : ";
        cout.put(j.second)<<endl;
    }
}

void decode(fstream &encoded, ofstream &decoded, map<vector<char>, char>const& finalreverse) {
    vector<char>temp;
    string line;
    while(getline(encoded, line)) {
        for(char ch: line) {
            if(ch == ' ') {
                decoded.put(' ');
                temp.clear();
                continue;
            }
            temp.push_back(ch);
            auto it = finalreverse.find(temp);
            if(it != finalreverse.end()) {
                decoded.put(it->second);
                temp.clear();
            }
            else continue;
        }
    }
}


int main() {
    ifstream inputFile("sentence.txt");
    fstream outputFile("encoded.txt");
    ofstream decodedFile("decoded.txt");
    if(!(inputFile)) {
        cerr<<"Error while opening file. "<<endl;
        return 1;
    }
    
    if(!(outputFile)) {
        cerr<<"Error while writing to file."<<endl;
    }
    
    int n = 5;
    srand(time(NULL));
    // int i = 1;
    // char symbolSet[5] = {'A', 'B', 'C', 'D', 'E'};
    // struct tnode* root = randomCodeTree(symbolSet, n);
    // cout<<"The generated code tree is: "<<endl;
    // printTreeInorder(root);
    // cout<<endl;
    // printTreePreorder(root);
    vector<char>buf;
    vector<char>codechar;
    vector<vector<char>> code;
    // createCodeTable(root, buf, codechar, code);
    
    // cout<<"printing the code table..."<<endl;
    // for(int i = 0; i < codechar.size(); i++) {
    //     cout.put(codechar[i])<<":"<<"\t";
    //     for(int j = 0; j < code[i].size(); j++) {
    //         cout.put(code[i][j]);
    //     }
    //     cout<<endl;
    // }
    
    map<char, int>mp;
    createFrequencyTable(inputFile, mp);
    
    inputFile.close();
    
    struct minHeapNode* newroot = createHuffmanTree(mp);
    printFinalTree(newroot);
    createHuffmanCodeTable(newroot, buf, codechar, code);
    cout<<endl;
    
    inputFile.open("sentence.txt");
    if(!(inputFile)) {
        cerr<<"Error when reopening the file"<<endl;
        return 1;
    }
    else {
        cout<<"File reopened successfully"<<endl;
    }
    
    map<char, vector<char>>final;
    createMap(final, code, codechar);
    encode(inputFile, outputFile, final);
    
    cout<<"printing the huffman code table..."<<endl;
    for(int i = 0; i < codechar.size(); i++) {
        cout.put(codechar[i])<<":"<<"\t";
        for(int j= 0; j < code[i].size();j++) {
            cout.put(code[i][j]);
        }
        cout<<endl;
    }
    
    inputFile.close();
    outputFile.close();
    
    map<vector<char>, char> finalreverse;
    createReverseMap(final, finalreverse);
    outputFile.open("encoded.txt");
    if(!(outputFile)) {
        cerr<<"Unable to reopen file. "<<endl;
        return 1;
    }
    else {
        cout<<"File reopened successfully"<<endl;
    }
    
    decode(outputFile, decodedFile, finalreverse);
    
    outputFile.close();
    decodedFile.close();
}
