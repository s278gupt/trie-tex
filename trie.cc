#include <iostream>
#include <sstream>
#include <string>
#include "node.h"
#include "trie.h"

TrieError::TrieError(std::string message):
   message(std::move(message)) {}

const std::string &TrieError::what() const { return message; }

void createTrie(Node *z) {
   int numChildren = z->numChildren;

   // Instantiate all the vector of children nodes
   for (int i = 1; i <= numChildren; i++) {
      string line;
      stringstream ss;
      string cmd;
      if(getline(cin, line)) {
         int num;
         string edge, label;
         ss << line;
         ss >> cmd;
         if (cmd == "edge") {
            ss >> edge >> num;
            if (num == 0) throw TrieError("Edges must have at least one child. Otherwise make it a leaf.");
            Node *n = createNode(z, edge, num, "");
            (z->children).push_back(n);
            cout << "Added " << i << "th child with edge " << edge << " successfully" << endl;
            // Create the subtrie for this child
            createTrie(n);
         } else if (cmd == "leaf") {
            ss >> edge >> label;
            if (label.empty()) throw TrieError("Leaf must have an edge and a label.");
            Node *n = createNode(z, edge, 0, label);
            (z->children).push_back(n);
            cout << "Added leaf " << label << " successfully" << endl;
         } else {
            throw TrieError("Unexpected command " + cmd + ". Expected `edge` or `leaf`.");
         }
      } else {
         int missingChildren = numChildren - i + 1;
         throw TrieError("Input terminated unexpectedly. Expected " + to_string(missingChildren) + " more children.");
      }
   }
}

void deleteTrie(Trie *t) {
   deleteNode(t->root);
   delete t;
}
