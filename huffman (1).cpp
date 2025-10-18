#include <bits/stdc++.h>
using namespace std;

struct Node {
    char data;
    int freq;
    Node *left, *right;
    
    Node(char d, int f) {
        data = d;
        freq = f;
        left = right = NULL;
    }
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

void printCodes(Node* root, string code = "") {
    if (root == NULL) return;
    
    if (root->left == NULL && root->right == NULL) {
        cout << code << " ";
        return;
    }
    
    printCodes(root->left, code + "0");
    printCodes(root->right, code + "1");
}

int main() {
    string s = "abcdef";
    int f[] = {5, 9, 12, 13, 16, 45};
    int n = s.length();
    
    priority_queue<Node*, vector<Node*>, Compare> pq;
    
    for (int i = 0; i < n; i++) {
        Node* node = new Node(s[i], f[i]);
        pq.push(node);
    }
    
    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();
        
        Node* parent = new Node('\0', left->freq + right->freq);
        parent->left = left;
        parent->right = right;
        
        pq.push(parent);
    }
    
    Node* root = pq.top();
    
    printCodes(root);
    
    return 0;
}