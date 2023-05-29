#include "SocketUtil.h"

#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>

#define buf_size 256

void HandleClient(int c_fd, struct sockaddr* addr, size_t addrlen,
                  int sock_family);

void Usage(char* progname);

// Create a listening socket, accept a connection from a client,
// and write all the data the client sends to stdout.
int main(int argc, char** argv) {
  // TODO: fill in this main method
  if (argc != 2) {
    Usage(argv[0]);
  }

  int sock_family;
  int listen_fd = Listen(argv[1], &sock_family);
  if (listen_fd <= 0) {
    // We failed to bind/listen to a socket.  Quit with failure.
    std::cerr << "Couldn't bind to any addresses." << std::endl;
    return EXIT_FAILURE;
  }

  // Loop forever, accepting a connection from a client and doing
  // an echo trick to it.
  struct sockaddr_storage caddr;
  socklen_t caddr_len = sizeof(caddr);
  int client_fd = accept(listen_fd,
                          reinterpret_cast<struct sockaddr*>(&caddr),
                          &caddr_len);
  if (client_fd < 0) {
    if ((errno == EINTR) || (errno == EAGAIN) || (errno == EWOULDBLOCK))
    std::cerr << "Failure on accept: " << strerror(errno) << std::endl;
  }

  HandleClient(client_fd,
                reinterpret_cast<struct sockaddr*>(&caddr),
                caddr_len,
                sock_family);

  // Close up shop.
  return EXIT_SUCCESS;

}

void HandleClient(int c_fd, struct sockaddr* addr, size_t addrlen,
                  int sock_family) {

  // Loop, reading data and echo'ing it back, until the client
  // closes the connection.
  while (1) {
    unsigned char clientbuf[1024];
    int res = WrappedRead(c_fd, clientbuf, 1024);
    if (res == 0) {
      break;
    }

    if (res == -1) {
      if ((errno == EAGAIN) || (errno == EINTR))
        continue;

      std::cout << " [Error on client socket: ";
      std::cout << strerror(errno) << "]" << std::endl;
      break;
    }
    std::cout << clientbuf;
    WrappedWrite(0, clientbuf, res);
  }

  close(c_fd);
}

void Usage(char* progname) {
  std::cerr << "usage: " << progname << " port" << std::endl;
  exit(EXIT_FAILURE);
}