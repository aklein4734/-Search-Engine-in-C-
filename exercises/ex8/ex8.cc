// Copyright 2023 Adam Klein
// Name: Adam Klein
// UWemail: aklein47@uw.edu

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <map>

// finds wether the in is still good to read and returns the next value
template <typename T> bool ReadValue(std::ifstream& in, T* const output);

int main(int argc, char* argv[]) {
  if (argc != 2) {  // checks for if exactly 1 paramiter was passed in
    std::cerr << "ERROR: incorect number of inputs" << std::endl;
    return EXIT_FAILURE;
  }
  std::ifstream file;
  file.open(argv[1], std::ifstream::in);
  if (file.bad()) {  // sees if the ifsteam is good
    std::cerr << "Incorect file path passed in" << std::endl;
    file.close();
    return EXIT_FAILURE;
  }
  std::map<std::string, int> map;
  std::map<std::string, int>::iterator it;
  std::string *word = new std::string();
  while (ReadValue(file, word)) {
    map[*word]++;
  }
  for (it = map.begin(); it != map.end(); ++it) {
    std::cout << it->first << " " << it->second << std::endl;
  }
  file.close();
  delete word;
  return EXIT_SUCCESS;
}

template <typename T> bool ReadValue(std::ifstream& in, T* const output) {
  if (in.fail()) {  // cheacks if ifstream in fails
    std::cerr << "File read failed" << std::endl;
    in.close();
    exit(EXIT_FAILURE);
  }
  T prev = *output;
  in >> *output;
  // checks to see if pointer is at the same spot
  return in.good() || prev != *output;
}
