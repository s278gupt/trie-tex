#ifndef _TRIE_
#define _TRIE_
struct Node;

struct Trie {
   Node *root;
};

void deleteTrie(Trie *t);

int createTrie(Node *z);

#endif
