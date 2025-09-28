#include <bits/stdc++.h>
using namespace std;

int main() {
    string stringA, stringB;
    cout << "Enter first string: ";
    cin >> stringA;
    cout << "Enter second string: ";
    cin >> stringB;
    
    int lengthA = stringA.length();
    int lengthB = stringB.length();
    
    vector<vector<int>> table(lengthA + 1, vector<int>(lengthB + 1, 0));
    int longestLength = 0;
    pair<int, int> endPos = {0, 0};
    
    for (int row = 1; row <= lengthA; ++row) {
        for (int col = 1; col <= lengthB; ++col) {
            if (stringA[row - 1] == stringB[col - 1]) {
                table[row][col] = table[row - 1][col - 1] + 1;
                if (table[row][col] > longestLength) {
                    longestLength = table[row][col];
                    endPos = {row, col};
                }
            }
        }
    }
    
    cout << "Lookup Table:" << endl;
    for (int row = 0; row <= lengthA; ++row) {
        for (int col = 0; col <= lengthB; ++col) {
            cout << table[row][col] << " ";
        }
        cout << endl;
    }
    
    string theSubstring = "";
    if (longestLength > 0) {
        int endRow = endPos.first;
        int endCol = endPos.second;
        for (int step = 0; step < longestLength; ++step) {
            theSubstring = stringA[endRow - 1 - step] + theSubstring;
        }
    }
    
    cout << "Longest common substring length: " << longestLength << endl;
    cout << "One such substring: " << theSubstring << endl;
    
    return 0;
}