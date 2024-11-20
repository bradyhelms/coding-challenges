#include <iostream>
#include <fstream>
#include <unordered_map>
#include <cassert>

void print_map(const std::unordered_map<char, int>& char_freq);
int check_freq(const std::unordered_map<char, int>& char_freq, char ch);
void test1(const std::unordered_map<char, int>& char_freq);

int main(int argc, char** argv) {

  if (argc == 1) {
    std::cout << "Missing input file.\n";
  }

  const std::string filename = argv[argc - 1];
  std::ifstream file(filename);

  if (!file) {
    throw std::runtime_error("Could not open file: " + filename);
  }

  std::unordered_map<char, int> char_freq;

  std::string line;
  while(getline(file, line)) {
    for (char ch : line) {
      char_freq[ch]++;
    }
  }

  test1(char_freq);

  return 0;
}

void print_map(const std::unordered_map<char, int>& char_freq) {
  for (const auto& [ch, freq] : char_freq) {
    std::cout << ch << ": " << freq << '\n';
  }
}

int check_freq(const std::unordered_map<char, int>& char_freq, char ch) {
  auto it = char_freq.find(ch);
  if (it != char_freq.end()) {
    return it->second;
  } else {
    return 0;
  }
}

void test1(const std::unordered_map<char, int>& char_freq) {
  assert(check_freq(char_freq, 'X') == 333);
  assert(check_freq(char_freq, 't') == 223000);
  std::cout << "Tests for step 1 passed." << std::endl;
}
