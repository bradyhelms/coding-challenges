#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>

struct Node {
  char ch;
  int freq;
  Node* left;
  Node* right;
};

Node* new_node(char ch, int freq, Node* left, Node* right) {
  Node* node = new Node();

  node->ch = ch;
  node->freq = freq;
  node->left = left;
  node->right = right;

  return node;
}

struct compare {
  bool operator()(Node* l, Node* r) {
    return l->freq > r->freq;
  }
};

void encode(Node* root, std::string str, std::unordered_map<char, std::string>& huffman) {
  if (root == nullptr) {
    return;
  }

  if (!root->left && !root->right) {
    huffman[root->ch] = str;
  }

  encode(root->left, str + "0", huffman);
  encode(root->right, str + "1", huffman);
}

void decode(Node* root, int *index, std::string str);
