#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

struct Node {
   Node *parent;
   string edge;
   int numChildren;
   string label;
   vector<Node*> children;
};

Node *createNode(Node *parent, string edge, int numChildren, string label) {
   Node *n = new Node;
   n->parent = parent;
   n->edge = edge;
   n->numChildren = numChildren;
   n->label = label;
   return n;
}

void deleteNode(Node *z) {
   if (z != NULL) {
      for (auto &child : z->children) {
         deleteNode(child);
      }
      delete z;
   }
}

void printNodes(Node *z) {
   for (int i = 0; i < z->numChildren; i++) {
      cout << (z->children)[i]->label << endl; 
   }

   for (int i = 0; i < z->numChildren; i++) {
      printNodes((z->children)[i]); 
   }
}

struct Trie {
   Node *root;
};

void deleteTrie(Trie *t) {
   deleteNode(t->root);
   delete t;
}

int createTrie(Node *z) {
   int numChildren = z->numChildren;
   cout << "number of children: " << numChildren << endl;

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
            // implement
            ss >> edge >> num;
            Node *n = createNode(z, edge, num, "internal");
            (z->children).push_back(n);
            cout << "Added " << i << "th child with edge " << edge << " successfully" << endl;
         } else if (cmd == "leaf") {
            // implement
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

   // Create the subtries of each child
   for (int i = 0; i < numChildren; i++) {
      createTrie((z->children)[i]);
   }
   
   return 0;
}

void printTrie(Trie *t) {
   if (t->root != NULL) {
      cout << (t->root)->label << endl;
      printNodes(t->root);
   }
}

int main() {
   Trie *t = new Trie;

   string line;
   string cmd;
   int numChildren;

   // Ensure first cmd is "root X"
   getline(cin, line);
   stringstream ss(line);
   ss >> cmd;
   if (cmd == "root") {
      ss >> numChildren;
      t->root = createNode(NULL, "", numChildren, "root");
      cout << "Added root successfully" << endl;
   } else {
      cout << "Input must start with root command. See `trie-tex help` for more." << endl;
      return 1;
   }

   // Create the rest of the trie
   int success = createTrie(t->root);
   if (success == 0) {
      // Print trie
      printTrie(t);
   }

   deleteTrie(t);
   return 0;
}
