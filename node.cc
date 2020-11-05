#include <fstream>
#include <string>
#include <vector>
#include "node.h"
using namespace std;

Node *createNode(Node *parent, string edge, int numChildren, string label) {
   Node *n = new Node;
   n->parent = parent;
   if (edge == "$") {
      edge = "\\$";
   }
   n->edge = edge;
   n->numChildren = numChildren;
   if ((!label.empty()) && (label.back() == '$')) {
      label.pop_back();
      label.append("\\$");
   }
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

void printNodes(ofstream &file, Node *z) {
   if (z == NULL) return;
   
   if ((z->label).empty()) {
      // z is an internal node
      file <<  "child{node[solid node]{}" << endl;
   } else {
      // z is a leaf
      file <<  "child{node[leaf node]{" << z->label << "}" << endl;
   }

   // print children
   for (int i = 0; i < z->numChildren; i++) {
      printNodes(file, (z->children)[i]);
   }

   file << "edge from parent node[triee]{$" << z->edge << "$}" << endl;
   file << "}" << endl;
}
