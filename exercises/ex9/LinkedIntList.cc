// Copyright 2023 Adam Klein
// Name: Adam Klein
// UWemail: aklein47@uw.edu

#include "LinkedIntList.h"

namespace intlist333 {

  void LinkedIntList::Append(const int payload) {
    std::shared_ptr<Node> node (new Node());
    node->payload = payload;
    if (this->num_elements_ == 0) {
      this->head_ = node;
      this->tail_ = node;
    } else {
      this->tail_->next = node;
      node->prev = this->tail_;
      this->tail_ = node;
    }
    this->num_elements_++;
  }

  void LinkedIntList::Push(const int payload) {
    std::shared_ptr<Node> node (new Node());
    node->payload = payload;
    if (this->num_elements_ == 0) {
      this->head_ = node;
      this->tail_ = node;
    } else {
      this->head_->prev = node;
      node->next = this->head_;
      this->head_ = node;
    }
    this->num_elements_++;
  }

  bool LinkedIntList::Pop(int* const payload_ptr) {
    if (this->num_elements_ == 0) {
      return false;
    }
    *payload_ptr = this->head_->payload;
    this->num_elements_--;
    if (this->num_elements_ == 0) {
      this->head_ = nullptr;
      this->tail_ = nullptr;
      return true;
    }
    this->head_ = this->head_->next;
    this->head_->prev.reset();
    return true;
  }

  bool LinkedIntList::Slice(int* const payload_ptr) {
    if (this->num_elements_ == 0) {
      return false;
    }
    *payload_ptr = this->tail_->payload;
    this->num_elements_--;
    if (this->num_elements_ == 0) {
      this->head_ = nullptr;
      this->tail_ = nullptr;
      return true;
    }
    this->tail_ = this->tail_->prev.lock();
    this->tail_->next = nullptr;
    return true;
  }

}   // namespace intlist333
