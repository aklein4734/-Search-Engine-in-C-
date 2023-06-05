/*
 * Copyright ©2023 Chris Thachuk.  All rights reserved.  Permission is
 * hereby granted to the students registered for University of Washington
 * CSE 333 for use solely during Spring Quarter 2023 for purposes of
 * the course.  No other use, copying, distribution, or modification
 * is permitted without prior written consent. Copyrights for
 * third-party components of this work must be honored.  Instructors
 * interested in reusing these course materials should contact the
 * author.
 */

#include <stdio.h>
#include <string>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

extern "C" {
  #include "libhw2/FileParser.h"
}

#include "./HttpUtils.h"
#include "./FileReader.h"

using std::string;

namespace hw4 {

bool FileReader::ReadFile(string* const contents) {
  string full_file = basedir_ + "/" + fname_;

  // Read the file into memory, and store the file contents in the
  // output parameter "str."  Be careful to handle binary data
  // correctly; i.e., you probably want to use the two-argument
  // constructor to std::string (the one that includes a length as a
  // second argument).
  //
  // You might find ::ReadFileToString() from HW2 useful here. Remember that
  // this function uses malloc to allocate memory, so you'll need to use
  // free() to free up that memory after copying to the string output
  // parameter.
  //
  // Alternatively, you can use a unique_ptr with a malloc/free
  // deleter to automatically manage this for you; see the comment in
  // HttpUtils.h above the MallocDeleter class for details.

  // STEP 1:
  struct stat file_stat;
  char* buf;
  int result, fd;
  ssize_t num_read;
  size_t left_to_read;


  if (lstat(full_file.c_str(), &file_stat) == -1) {
    return false;
  }

  if (!S_ISREG(file_stat.st_mode)) {
    return false;
  }

  fd = open(full_file.c_str(), O_RDONLY);
  if (fd == -1) {
    return false;
  }


  buf = reinterpret_cast<char *>(malloc(file_stat.st_size));
  if (buf == NULL) {
    return false;
  }


  left_to_read = file_stat.st_size;
  num_read = 0;
  while (left_to_read > 0) {
    result = read(fd, buf + (file_stat.st_size - left_to_read),
                  left_to_read);
    if (result == -1) {
      if (errno != EINTR && errno != EAGAIN) {
        free(buf);
        return false;
      }
      // EINTR happened, so do nothing and try again
      continue;
    } else if (result == 0) {
    // EOF reached, so stop reading
    break;
    }
    left_to_read -= result;
    num_read += result;
  }
  if (num_read != file_stat.st_size) {
    return false;
  }
  close(fd);
  string temp = "";
  temp.append(buf, num_read);

  *contents = temp;
  free(buf);
  return true;
}

}  // namespace hw4
