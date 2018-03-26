#ifndef TRIE_H
#define TRIE_H

#include "postingList.h"

struct Trie* initTrie();
int pushTrie(struct Trie*,char*,int);
struct postingList* search(struct Trie*,char*);
int get_total_words(struct Trie*);
int printTrie(struct Trie*);
void destroyTrie(struct Trie* );

#endif