#include <iostream>
#include <fstream>
#include <getopt.h>
#include <stack>

int main(int argc, char** argv) {

  if (argc == 1) {
    std::cout << "Missing filename argument." << std::endl;
  }

  std::string filename = argv[argc - 1];
  std::ifstream file(filename);

  if (!file) {
    throw std::runtime_error("Could not open file: " + filename);
  }

  std::stack<char> brace_stack;

  bool is_valid_json = false;
  char ch;

  while(file.get(ch)) {
    if (ch == '{') {
      brace_stack.push(ch);
    } else if (ch == '}') {
      if (brace_stack.top() == '{') {
        brace_stack.pop();
      }     
    }
    if (brace_stack.empty()) {
      is_valid_json = true;
    }
  }

  if (brace_stack.empty() && is_valid_json) {
    std::cout << "Valid JSON file!" << std::endl;
    return 0;
  } else {
    std::cout << "Not a valid JSON file!" << std::endl;
    return 1;
  }

  return 0;
}
