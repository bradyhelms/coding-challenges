#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <getopt.h>

unsigned int flags = 0;
constexpr unsigned int BYTES = 1 << 0;
constexpr unsigned int LINES = 1 << 1;
constexpr unsigned int WORDS = 1 << 2;
constexpr unsigned int CHARS = 1 << 3;

int count_words(std::string line);

int main(int argc, char** argv) {

  int opt;
  std::string filename = argv[argc - 1];

  while ((opt = getopt(argc, argv, "clwm:")) != -1) {
    switch(opt) {
      case 'c':
        flags |= BYTES;
        break;
      case 'l':
        flags |= LINES;
        break;
      case 'w':
        flags |= WORDS;
        break;
      case 'm':
        flags |= CHARS;
        break;
      default:
        std::cout << "No command line args given." << std::endl;
    }
  }

  // Try opening file
  std::ifstream file(filename);
  // This is for character count
  std::wifstream wfile(filename);
  wfile.imbue(std::locale(""));
  

  if (!file) {
    throw std::runtime_error("Could not open file: " + filename);
  }

  int byte_count, line_count, word_count;
  byte_count = line_count = word_count = 0;

  char byte;
  while (file.get(byte)) {
    byte_count++;
  }

  // Close and reopen to loop over again
  file.close();
  std::ifstream ffile(filename);

  std::string line;
  while (getline(ffile, line)) {
    line_count++;
    word_count += count_words(line);
  }

  if (flags == 0) {
    std::cout << line_count << " " 
              << word_count << " " 
              << byte_count << " "
              << filename   << std::endl;
  } else if (flags & BYTES) {
    std::cout << byte_count << " " << filename << std::endl;
  } else if (flags & LINES) {
    std::cout << line_count << " " << filename << std::endl;
  } else if (flags & WORDS) {
    std::cout << word_count << " " << filename << std::endl;
  }

  if (flags & CHARS) {
    wchar_t ch;
    int char_count = 0;
    while (wfile.get(ch)) {
      char_count++;
    }

    std::cout << char_count << " " << filename << std::endl;
  }

  file.close();
  return 0;
}

int count_words(std::string line) {
  int word_count = 0;
  std::string word;
  std::stringstream stream(line);

  while (stream >> word) {
    ++word_count;
  }

  return word_count;
}
