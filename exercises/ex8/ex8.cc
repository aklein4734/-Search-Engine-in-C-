// Copyright 2023 Adam Klein
// Name: Adam Klein
// UWemail: aklein47@uw.edu

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <map>

int main(int argc, char* argv[]) {
     // TODO: Write this function
  if (argc != 2) {  // checks for if exactly 1 paramiter was passed in
    std::cerr << "ERROR: incorect number of inputs" << std::endl;
    return EXIT_FAILURE;
  }
  errno = 0;
  std::ifstream file;
  file.open(argv[1], std::ifstream::in);
  if (file.bad()) {
    std::cerr << "Incorect file path passed in" << std::endl;
    file.close();
    return EXIT_FAILURE;
  }
  std::map<std::string, int> map;

  char buf[100];
  while (!feof(file)) {
    if (fgets(buf , 100 , file) == NULL) {
      break;
    }
    fputs(buf, stdout);
  }
  file.close();
  
  return EXIT_SUCCESS;
}