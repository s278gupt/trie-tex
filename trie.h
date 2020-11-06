#ifndef _TRIE_
#define _TRIE_
#include <string>
struct Node;

class TrieError {
   std::string message;
   public:
      TrieError(std::string message);
      const std::string &what() const;
};

struct Trie {
   Node *root;
};

void createTrie(Node *z);
void deleteTrie(Trie *t);

#endif
