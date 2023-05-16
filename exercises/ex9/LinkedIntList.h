// Copyright 2023 Adam Klein
// Name: Adam Klein
// UWemail: aklein47@uw.edu

#ifndef LINKEDINTLIST_H_
#define LINKEDINTLIST_H_

#include <memory>
#include "IntList.h"

namespace intlist333 {

// LinkedIntList is an implementation of
// the IntList abstract class. Implemented using
// a doubly linked list
class LinkedIntList : public IntList {
 public:
  // Destructor should be kept default
  // since smart pointers should clean
  // everything up for us
  virtual ~LinkedIntList() = default;

  // creates a new LinkedIntList
  LinkedIntList() {num_elements_ = 0;}

  // disabling copy constuctor
  LinkedIntList(const LinkedIntList&) = delete;

  // disables = operator
  LinkedIntList& operator=(const LinkedIntList&) = delete;

  // returns the amount of elements in the LinkedIntList
  int num_elements() const override {return num_elements_;}

  // adds a node to the front of the LinkedIntList with the payloads value
  void Push(const int payload) override;

  // adds a node to the back of the LinkedIntList with the payloads value
  void Append(const int payload) override;

  // removes the node at the front of the LinkedIntList and
  // returns the value through the payload_ptr and returns
  // true if a node is removed otherwise false
  bool Pop(int* const payload_ptr) override;

  // removes the node at the back of the LinkedIntList and
  // returns the value through the payload_ptr and returns
  // true if a node is removed otherwise false
  bool Slice(int* const payload_ptr) override;


 private:
  int num_elements_;
  // Note that these should be modified
  // to use smart pointers at some point
  struct Node {
    int payload;
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> prev;
  };
  std::shared_ptr<Node> head_;
  std::shared_ptr<Node> tail_;
};

}  // namespace intlist333

#endif  // LINKEDINTLIST_H_
