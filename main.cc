#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Node {
   Node *parent;
   string edge;
   vector<Node*> children;
};

Node *createNode(Node *parent, string edge) {
   Node *n = new Node;
   n->parent = parent;
   n->edge = edge;
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

struct Trie {
   Node *root;
};

void deleteTrie(Trie *t) {
   deleteNode(t->root);
   delete t;
}

int main() {
   Trie *t = new Trie;
   t->root = createNode(NULL, "a");
   Node *n = createNode(t->root, "b");
   ((t->root)->children).push_back(n);

   cout << (t->root)->edge << endl;
   cout << ((t->root)->children)[0]->edge << endl;
   
   deleteTrie(t);
   return 0;
}
