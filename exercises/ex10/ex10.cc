// Copyright 2023 Adam Klein
// Name: Adam Klein
// UWemail: aklein47@uw.edu

#include "SocketUtil.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

void Usage(char* progname);

#define buf_size 256

// Open a local file, open a socket to a remote process,
// and send the file to other process.
int main(int argc, char** argv) {
  if (argc != 4) {
    Usage(argv[0]);
  }
  unsigned short port = 0;
  if (sscanf(argv[2], "%hu", &port) != 1) {
    Usage(argv[0]);
  }

  // Get an appropriate sockaddr structure.
  struct sockaddr_storage addr;
  size_t addrlen;
  if (!LookupName(argv[1], port, &addr, &addrlen)) {
    Usage(argv[0]);
  }

  int fd;
  if (!Connect(addr, addrlen, &fd)) {
    Usage(argv[0]);
  }
  int file_fd = open(argv[3],  O_RDONLY);
  if (file_fd < 0) {
    close(fd);
    Usage(argv[0]);
  }

  unsigned char buf[buf_size];
  int read = buf_size;
  while (read == buf_size) {
    read = WrappedRead(file_fd, buf, read);
    if (read < 1) {
      close(fd);
      Usage(argv[0]);
    }
    int test = WrappedWrite(fd, buf, read);
    if (test < 1) {
      close(file_fd);
      Usage(argv[0]);
    }
  }

  close(file_fd);
  close(fd);
  return EXIT_SUCCESS;
}

void Usage(char* progname) {
  std::cerr << "usage: " << progname << " hostname port" << std::endl;
  exit(EXIT_FAILURE);
}
