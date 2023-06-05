/*
 * Copyright ©2023 Chris Thachuk.  All rights reserved.  Permission is
 * hereby granted to students registered for University of Washington
 * CSE 333 for use solely during Spring Quarter 2023 for purposes of
 * the course.  No other use, copying, distribution, or modification
 * is permitted without prior written consent. Copyrights for
 * third-party components of this work must be honored.  Instructors
 * interested in reusing these course materials should contact the
 * author.
 */

#include <stdio.h>       // for snprintf()
#include <unistd.h>      // for close(), fcntl()
#include <sys/types.h>   // for socket(), getaddrinfo(), etc.
#include <sys/socket.h>  // for socket(), getaddrinfo(), etc.
#include <arpa/inet.h>   // for inet_ntop()
#include <netdb.h>       // for getaddrinfo()
#include <errno.h>       // for errno, used by strerror()
#include <string.h>      // for memset, strerror()
#include <iostream>      // for std::cerr, etc.

#include "./ServerSocket.h"

extern "C" {
  #include "libhw1/CSE333.h"
}

namespace hw4 {

ServerSocket::ServerSocket(uint16_t port) {
  port_ = port;
  listen_sock_fd_ = -1;
}

ServerSocket::~ServerSocket() {
  // Close the listening socket if it's not zero.  The rest of this
  // class will make sure to zero out the socket if it is closed
  // elsewhere.
  if (listen_sock_fd_ != -1)
    close(listen_sock_fd_);
  listen_sock_fd_ = -1;
}

bool ServerSocket::BindAndListen(int ai_family, int* const listen_fd) {
  // Use "getaddrinfo," "socket," "bind," and "listen" to
  // create a listening socket on port port_.  Return the
  // listening socket through the output parameter "listen_fd"
  // and set the ServerSocket data member "listen_sock_fd_"

  // STEP 1:
    // Populate the "hints" addrinfo structure for getaddrinfo().
  // ("man addrinfo")
  struct addrinfo hints;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET6;       // IPv6 (also handles IPv4 clients)
  hints.ai_socktype = SOCK_STREAM;  // stream
  hints.ai_flags = AI_PASSIVE;      // use wildcard "INADDR_ANY"
  hints.ai_flags |= AI_V4MAPPED;    // use v4-mapped v6 if no v6 found
  hints.ai_protocol = IPPROTO_TCP;  // tcp protocol
  hints.ai_canonname = nullptr;
  hints.ai_addr = nullptr;
  hints.ai_next = nullptr;

  // Use argv[1] as the string representation of our portnumber to
  // pass in to getaddrinfo().  getaddrinfo() returns a list of
  // address structures via the output parameter "result".
  struct addrinfo* result;
  char port[6];
  snprintf(port, sizeof(port), "%d", this->port_);
  int res = getaddrinfo(nullptr, port, &hints, &result);

  // Did addrinfo() fail?
  if (res != 0) {
    std::cerr << "getaddrinfo() failed: ";
    std::cerr << gai_strerror(res) << std::endl;
    return -1;
  }

  // Loop through the returned address structures until we are able
  // to create a socket and bind to one.  The address structures are
  // linked in a list through the "ai_next" field of result.
  *listen_fd = -1;
  for (struct addrinfo* rp = result; rp != nullptr; rp = rp->ai_next) {
    *listen_fd = socket(rp->ai_family,
                       rp->ai_socktype,
                       rp->ai_protocol);
    if (*listen_fd == -1) {
      // Creating this socket failed.  So, loop to the next returned
      // result and try again.
      std::cerr << "socket() failed: " << strerror(errno) << std::endl;
      *listen_fd = -1;
      continue;
    }

    // Configure the socket; we're setting a socket "option."  In
    // particular, we set "SO_REUSEADDR", which tells the TCP stack
    // so make the port we bind to available again as soon as we
    // exit, rather than waiting for a few tens of seconds to recycle it.
    int optval = 1;
    setsockopt(*listen_fd, SOL_SOCKET, SO_REUSEADDR,
               &optval, sizeof(optval));

    // Try binding the socket to the address and port number returned
    // by getaddrinfo().
    if (bind(*listen_fd, rp->ai_addr, rp->ai_addrlen) == 0) {
      // Bind worked!  Return to the caller the address family.
      this->sock_family_ = rp->ai_family;
      break;
    } else {
      return false;
    }

    // The bind failed.  Close the socket, then loop back around and
    // try the next address/port returned by getaddrinfo().
    close(*listen_fd);
    *listen_fd = -1;
  }

  // Free the structure returned by getaddrinfo().
  freeaddrinfo(result);

  // If we failed to bind, return failure.
  if (*listen_fd <= 0)
    return false;

  // Success. Tell the OS that we want this to be a listening socket.
  if (listen(*listen_fd, SOMAXCONN) != 0) {
    std::cerr << "Failed to mark socket as listening: ";
    std::cerr << strerror(errno) << std::endl;
    close(*listen_fd);
    return -1;
  }

  // Return to the client the listening file descriptor.
  this->listen_sock_fd_ = *listen_fd;
  return true;
}

bool ServerSocket::Accept(int* const accepted_fd,
                          std::string* const client_addr,
                          uint16_t* const client_port,
                          std::string* const client_dns_name,
                          std::string* const server_addr,
                          std::string* const server_dns_name) const {
  // Accept a new connection on the listening socket listen_sock_fd_.
  // (Block until a new connection arrives.)  Return the newly accepted
  // socket, as well as information about both ends of the new connection,
  // through the various output parameters.

  // STEP 2:

  struct sockaddr_storage caddr;
  socklen_t caddr_len = sizeof(caddr);

  while (1) {
    *accepted_fd = accept(listen_sock_fd_,
                           reinterpret_cast<struct sockaddr*>(&caddr),
                           &caddr_len);
    if (*accepted_fd < 0) {
      if ((errno == EAGAIN) || (errno == EINTR)) {
        continue;
      }
      std::cerr << "Failure on accept: " << strerror(errno) << std::endl;
      close(listen_sock_fd_);
      return false;
    }
    break;
  }

  char client_dns[NI_MAXHOST];
  int check = getnameinfo(reinterpret_cast<struct sockaddr*>(&caddr), caddr_len,
                          client_dns, NI_MAXHOST, NULL, 0, 0);
  *client_dns_name = client_dns;

  if (check < 0) {
    return false;
  }
  if (this->sock_family_ == AF_INET6) {
    char str[INET6_ADDRSTRLEN];
    struct sockaddr_in6* in6 = reinterpret_cast<struct sockaddr_in6*>(&caddr);
    inet_ntop(AF_INET6, &(in6->sin6_addr), str, INET6_ADDRSTRLEN);
    *client_port = in6->sin6_port;
    *client_addr = str;
  } else if (sock_family_ == AF_INET) {
    char str[INET_ADDRSTRLEN];
    struct sockaddr_in* in4 = reinterpret_cast<struct sockaddr_in*>(&caddr);
    inet_ntop(AF_INET, &(in4->sin_addr), str, INET_ADDRSTRLEN);
    *client_port = in4->sin_port;
    *client_addr = str;
  } else {
    return false;
  }

  if (this->sock_family_ == AF_INET6) {
    struct sockaddr_in6 sock;
    socklen_t sock_len = sizeof(sock);
    getsockname(*accepted_fd, reinterpret_cast<struct sockaddr*>(&sock),
                &sock_len);

    char server_dns[NI_MAXHOST];
    check = getnameinfo(reinterpret_cast<struct sockaddr*>(&sock), sock_len,
                        server_dns, NI_MAXHOST, NULL, 0, 0);
    *server_dns_name = server_dns;

    if (check < 0) {
      return false;
    }
    char str[INET6_ADDRSTRLEN];
    inet_ntop(AF_INET6, &sock.sin6_addr, str, INET6_ADDRSTRLEN);
    *server_addr = str;
  } else if (sock_family_ == AF_INET) {
    struct sockaddr_in sock;
    socklen_t sock_len = sizeof(sock);
    getsockname(*accepted_fd, reinterpret_cast<struct sockaddr*>(&sock),
                &sock_len);
    char server_dns[NI_MAXHOST];
    check = getnameinfo(reinterpret_cast<struct sockaddr*>(&sock), sock_len,
                        server_dns, NI_MAXHOST, NULL, 0, 0);
    *server_dns_name = server_dns;

    if (check < 0) {
      return false;
    }
    char str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &sock.sin_addr, str, INET_ADDRSTRLEN);
    *server_addr = str;
  } else {
    return false;
  }

  return true;
}

}  // namespace hw4
