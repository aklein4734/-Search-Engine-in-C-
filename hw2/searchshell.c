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

// Feature test macro for strtok_r (c.f., Linux Programming Interface p. 63)
#define _XOPEN_SOURCE 600
#define  _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#include "libhw1/CSE333.h"
#include "./CrawlFileTree.h"
#include "./DocTable.h"
#include "./MemIndex.h"



//////////////////////////////////////////////////////////////////////////////
// Helper function declarations, constants, etc
static void Usage(void);
static void ProcessQueries(DocTable* dt, MemIndex* mi);
static int GetNextLine(FILE* f, char** ret_str);


//////////////////////////////////////////////////////////////////////////////
// Main
int main(int argc, char** argv) {
  if (argc != 2) {
    Usage();
  }
  DocTable *table;
  MemIndex *index;
  fprintf(stdout, "Indexing '%s'\n", argv[1]);
  if (!CrawlFileTree(argv[1], &table, &index)) {
    Usage();
  }
  ProcessQueries(table, index);
  DocTable_Free(table);
  MemIndex_Free(index);
  fprintf(stdout, "shutting down...\n");
  // Implement searchshell!  We're giving you very few hints
  // on how to do it, so you'll need to figure out an appropriate
  // decomposition into functions as well as implementing the
  // functions.  There are several major tasks you need to build:
  //
  //  - Crawl from a directory provided by argv[1] to produce and index
  //  - Prompt the user for a query and read the query from stdin, in a loop
  //  - Split a query into words (check out strtok_r)
  //  - Process a query against the index and print out the results
  //
  // When searchshell detects end-of-file on stdin (cntrl-D from the
  // keyboard), searchshell should free all dynamically allocated
  // memory and any other allocated resources and then exit.
  //
  // Note that you should make sure the fomatting of your
  // searchshell output exactly matches our solution binaries
  // to get full points on this part.
  return EXIT_SUCCESS;
}


//////////////////////////////////////////////////////////////////////////////
// Helper function definitions

static void Usage(void) {
  fprintf(stderr, "Usage: ./searchshell <docroot>\n");
  fprintf(stderr,
          "where <docroot> is an absolute or relative " \
          "path to a directory to build an index under.\n");
  exit(EXIT_FAILURE);
}

static void ProcessQueries(DocTable* table, MemIndex* index) {
  char *buf = NULL;
  int size;
  LinkedList *words = LinkedList_Allocate();

  printf("enter query:\n");
  // Gets next line in stdin
  size = GetNextLine(stdin, &buf);
  // Cheacks to see if there are more queries
  while (size != -1) {
    char *cur_ptr = buf;
    char *word_start = buf;

    // works through the buf and finds words to add to the query
    // and saves them in a LinkedList
    while (*cur_ptr != '\n') {
      if (*cur_ptr != ' ') {  // did not find a new word
        *cur_ptr = tolower(*cur_ptr);
      } else {  // might have found new word
        *cur_ptr = '\0';
        int word_size = cur_ptr - word_start;

        if (word_size > 0) {  // sees if it is a word
          // found new word and mallocs space for it
          // and puts it into a LinkedList
          char *word = malloc(word_size + 1);
          Verify333(word != NULL);  // verify malloc worked
          for (int i = 0; i < word_size + 1; i++) {
            word[i] = word_start[i];
          }
          LinkedList_Append(words, word);
        }
        word_start = cur_ptr + 1;
      }
      cur_ptr++;
    }
    // cheaks the end to make sure there arn't any more words
    *cur_ptr = '\0';
    int word_size = cur_ptr - word_start;

    if (word_size > 0) {  // if so adds it to the LinkedList
      char *word = malloc(word_size + 1);
      Verify333(word != NULL);
      for (int i = 0; i < word_size + 1; i++) {
        word[i] = word_start[i];
      }
      LinkedList_Append(words, word);
    }

    // finds how many words are in the query
    int query_size = LinkedList_NumElements(words);
    char **query = (char **) malloc(sizeof(char *) * query_size);
    Verify333(query != NULL);

    // transfers the words in the LinkedList into the query
    for (int i = 0; i < query_size; i++) {
      char *word;
      LinkedList_Pop(words, (LLPayload_t *)&word);
      query[i] = word;
    }

    // does the query
    LinkedList *results = MemIndex_Search(index, query, query_size);

    // frees the array
    for (int i = 0; i < query_size; i ++) {
      free(query[i]);
    }
    free(query);

    // sees if the query got any results
    if (results != NULL) {
      LLIterator *itr = LLIterator_Allocate(results);
      while (LLIterator_IsValid(itr)) {
        SearchResult *sr;
        LLIterator_Get(itr, (LLPayload_t *) &sr);
        char *name = DocTable_GetDocName(table, sr->doc_id);
        fprintf(stdout, "  %s (%d)\n", name, sr->rank);
        LLIterator_Next(itr);
      }
      LLIterator_Free(itr);
      LinkedList_Free(results, (LLPayloadFreeFnPtr)free);
    }

    // starts the next loop
    free(buf);
    printf("enter query:\n");
    size = GetNextLine(stdin, &buf);
  }
  LinkedList_Free(words, free);
  free(buf);
}

static int GetNextLine(FILE *f, char **ret_str) {
  size_t buf_size = 0;
  return getline(ret_str, &buf_size, f);
}
