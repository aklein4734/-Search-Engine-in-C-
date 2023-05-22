// Copyright 2023 Adam Klein
// Name: Adam Klein
// UWemail: aklein47@uw.edu

#include "SocketUtil.h"

#include <unistd.h>
#include <assert.h>
#include <string.h>

#include <iostream>

using std::cerr;
using std::endl;

bool LookupName(char* name,
                unsigned short port,
                struct sockaddr_storage* ret_addr,
                size_t* ret_addrlen) {
  struct addrinfo hints, *results;
  int retval;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  // Do the lookup by invoking getaddrinfo().
  if ((retval = getaddrinfo(name, nullptr, &hints, &results)) != 0) {
    std::cerr << "getaddrinfo failed: ";
    std::cerr << gai_strerror(retval) << std::endl;
    return false;
  }

  // Set the port in the first result.
  if (results->ai_family == AF_INET) {
    struct sockaddr_in* v4addr =
            reinterpret_cast<struct sockaddr_in*>(results->ai_addr);
    v4addr->sin_port = htons(port);
  } else if (results->ai_family == AF_INET6) {
    struct sockaddr_in6* v6addr =
            reinterpret_cast<struct sockaddr_in6*>(results->ai_addr);
    v6addr->sin6_port = htons(port);
  } else {
    std::cerr << "getaddrinfo failed to provide an IPv4 or IPv6 address";
    std::cerr << std::endl;
    freeaddrinfo(results);
    return false;
  }

  // Return the first result.
  assert(results != nullptr);
  memcpy(ret_addr, results->ai_addr, results->ai_addrlen);
  *ret_addrlen = results->ai_addrlen;

  // Clean up.
  freeaddrinfo(results);
  return true;
}

bool Connect(const struct sockaddr_storage& addr,
             const size_t& addrlen,
             int* ret_fd) {
  int socket_fd = socket(addr.ss_family, SOCK_STREAM, 0);
  if (socket_fd == -1) {
    std::cerr << "socket() failed: " << strerror(errno) << std::endl;
    return false;
  }

  int res = connect(socket_fd,
                    reinterpret_cast<const sockaddr*>(&addr),
                    addrlen);
  if (res == -1) {
    std::cerr << "connect() failed: " << strerror(errno) << std::endl;
    return false;
  }

  *ret_fd = socket_fd;
  return true;
}

int WrappedRead(int fd, unsigned char* buf, int readlen) {
  int res;
  while (1) {
    res = read(fd, buf, readlen);
    if (res == 0) {
      std::cerr << "socket closed prematurely" << std::endl;
      close(fd);
      return 0;
    }
    if (res == -1) {
      if (errno == EINTR)
        continue;
      std::cerr << "socket read failure: " << strerror(errno) << std::endl;
      close(fd);
      return -1;
    }
    break;
  }
  return res;
}

int WrappedWrite(int fd, unsigned char* buf, int writelen) {
  int wres;
  while (1) {
    wres = write(fd, buf, writelen);
    if (wres == 0) {
      std::cerr << "socket closed prematurely" << std::endl;
      close(fd);
      return 0;
    }
    if (wres == -1) {
      if (errno == EINTR)
        continue;
      std::cerr << "socket write failure: " << strerror(errno) << std::endl;
      close(fd);
      return -1;
    }
    break;
  }
  return wres;
}
