#include <iostream>
#include <sstream>
#include <string>
#include "node.h"
#include "trie.h"

void deleteTrie(Trie *t) {
   deleteNode(t->root);
   delete t;
}

int createTrie(Node *z) {
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
            Node *n = createNode(z, edge, num, "");
            (z->children).push_back(n);
            cout << "Added " << i << "th child with edge " << edge << " successfully" << endl;
            // Create the subtrie for this child
            createTrie(n);
         } else if (cmd == "leaf") {
            ss >> edge >> label;
            Node *n = createNode(z, edge, 0, label);
            (z->children).push_back(n);
            cout << "Added leaf " << label << " successfully" << endl;
         } else {
            cout << "Unexpected command " << cmd << ". Expected `edge` or `leaf`." << endl;
            return 1;
         }
      } else {
         cout << "Input terminated unexpectedly. Expected " << i << "th child" << endl;
         return 1;
      }
   }
   
   return 0;
}
