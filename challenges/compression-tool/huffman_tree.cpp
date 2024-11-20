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

struct comp {
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

void decode(Node* root, int *index, std::string str) {
  if (root == nullptr) {
    return;
  }

  if (!root->left && !root->right) {
    std::cout << root->ch;
    return;
  }

  index++;

  if (str[index] == '0') {
    decode(root->left, index, str);
  } else {
    decode(root->right, index, str);
  }
}

void build_huff_tree(std::unordered_map<char, int> char_freq, std::string text) {
  std::priority_queue<Node*, std::vector<Node*>, comp> pq;

  for (auto pair : char_freq) {
    pq.push(new_node(pair.first, pair.second, nullptr, nullptr));
  }

  while (pq.size() != 1) {
    Node* left = pq.top();
    pq.pop();

    Node* right = pq.top();
    pq.pop();

    int sum = left->freq + right ->freq;
    pq.push(new_node('\0', sum, left, right));
  }

  Node* root = pq.top();

  std::unordered_map<char, std::string> huffman_code;
  encode(root, "", huffman_code);
}
