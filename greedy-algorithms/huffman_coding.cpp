#include <iostream>
#include <queue>
#include <map>
#include <string>

using namespace std;

struct HuffmanNode {
    char data;
    int freq;
    HuffmanNode *left, *right;
    HuffmanNode(char data, int freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(HuffmanNode* l, HuffmanNode* r) {
        return l->freq > r->freq;
    }
};

void generateCodes(HuffmanNode* root, string code, map<char, string>& huffmanCodes) {
    if (!root) return;
    if (!root->left && !root->right) {
        if (code.empty()) code = "0"; // Handle single node case
        huffmanCodes[root->data] = code;
    }
    generateCodes(root->left, code + "0", huffmanCodes);
    generateCodes(root->right, code + "1", huffmanCodes);
}

HuffmanNode* buildHuffmanTree(map<char, int>& freqMap) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;
    for (auto pair : freqMap) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }
    while (pq.size() > 1) {
        HuffmanNode* left = pq.top(); pq.pop();
        HuffmanNode* right = pq.top(); pq.pop();
        HuffmanNode* newNode = new HuffmanNode('\0', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;
        pq.push(newNode);
    }
    return pq.top();
}

void printCodes(map<char, string>& huffmanCodes) {
    for (auto pair : huffmanCodes) {
        cout << pair.first << " : " << pair.second << endl;
    }
}

int main() {
    int n;
    char ch;
    int freq;
    map<char, int> freqMap;

    cout << "Enter number of characters: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "Enter character and frequency: ";
        cin >> ch >> freq;
        freqMap[ch] = freq;
    }

    HuffmanNode* root = buildHuffmanTree(freqMap);
    map<char, string> huffmanCodes;
    generateCodes(root, "", huffmanCodes);
    cout << "Huffman Codes:" << endl;
    printCodes(huffmanCodes);

    return 0;
}