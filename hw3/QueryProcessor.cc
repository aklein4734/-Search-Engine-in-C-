/*
 * Copyright ©2023 Justin Hsia.  All rights reserved.  Permission is
 * hereby granted to students registered for University of Washington
 * CSE 333 for use solely during Winter Quarter 2023 for purposes of
 * the course.  No other use, copying, distribution, or modification
 * is permitted without prior written consent. Copyrights for
 * third-party components of this work must be honored.  Instructors
 * interested in reusing these course materials should contact the
 * author.
 */

#include "./QueryProcessor.h"

#include <iostream>
#include <algorithm>
#include <list>
#include <string>
#include <vector>


extern "C" {
  #include "./libhw1/CSE333.h"
}

using std::list;
using std::sort;
using std::string;
using std::vector;

namespace hw3 {

QueryProcessor::QueryProcessor(const list<string>& index_list, bool validate) {
  // Stash away a copy of the index list.
  index_list_ = index_list;
  array_len_ = index_list_.size();
  Verify333(array_len_ > 0);

  // Create the arrays of DocTableReader*'s. and IndexTableReader*'s.
  dtr_array_ = new DocTableReader* [array_len_];
  itr_array_ = new IndexTableReader* [array_len_];

  // Populate the arrays with heap-allocated DocTableReader and
  // IndexTableReader object instances.
  list<string>::const_iterator idx_iterator = index_list_.begin();
  for (int i = 0; i < array_len_; i++) {
    FileIndexReader fir(*idx_iterator, validate);
    dtr_array_[i] = fir.NewDocTableReader();
    itr_array_[i] = fir.NewIndexTableReader();
    idx_iterator++;
  }
}

QueryProcessor::~QueryProcessor() {
  // Delete the heap-allocated DocTableReader and IndexTableReader
  // object instances.
  Verify333(dtr_array_ != nullptr);
  Verify333(itr_array_ != nullptr);
  for (int i = 0; i < array_len_; i++) {
    delete dtr_array_[i];
    delete itr_array_[i];
  }

  // Delete the arrays of DocTableReader*'s and IndexTableReader*'s.
  delete[] dtr_array_;
  delete[] itr_array_;
  dtr_array_ = nullptr;
  itr_array_ = nullptr;
}

// This structure is used to store a index-file-specific query result.
typedef struct {
  DocID_t doc_id;  // The document ID within the index file.
  int     rank;    // The rank of the result so far.
} IdxQueryResult;

vector<QueryProcessor::QueryResult>
QueryProcessor::ProcessQuery(const vector<string>& query) const {
  Verify333(query.size() > 0);

  // STEP 1.
  // (the only step in this file)
  vector<QueryProcessor::QueryResult> final_result;
  for (int i = 0; i < array_len_; i++) {
    int size = query.size();
    vector<IdxQueryResult> t;
    bool no_results = false;
    for (int j = 0; j < size; j++) {
      auto test = itr_array_[i]->LookupWord(query[j]);
      if (test == nullptr) {
        no_results = true;
        break;
      }
      auto thing = test->GetDocIDList();
      if (j == 0) {
        for (auto doc : thing) {
          IdxQueryResult te;
          te.doc_id = doc.doc_id;
          te.rank = doc.num_positions;
          t.push_back(te);
        }
      } else {
        auto itr = t.begin();
        while (itr != t.end()) {
          bool check = true;
          for (auto doc : thing) {
            if (doc.doc_id == itr->doc_id) {
              check = false;
              itr->rank += doc.num_positions;
              break;
            }
          }
          if (check) {
            itr = t.erase(itr);
          } else {
            itr++;
          }
        }
      }
      delete test;
    }
    if (!no_results) {
      for (auto itr = t.begin(); itr < t.end(); itr++) {
        QueryResult temp;
        temp.rank = itr->rank;
        string file;
        dtr_array_[i]->LookupDocID(itr->doc_id, &file);
        temp.document_name = file;
        final_result.push_back(temp);
      }
    }
  }


  // Sort the final results.
  sort(final_result.begin(), final_result.end());
  return final_result;
}

}  // namespace hw3
