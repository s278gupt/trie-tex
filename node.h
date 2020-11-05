#ifndef _NODE_
#define _NODE_
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Node {
   Node *parent;
   string edge;
   int numChildren;
   string label;
   vector<Node*> children;
};


Node *createNode(Node *parent, string edge, int numChildren, string label);
void printNodes(ofstream &file, Node *z);
void deleteNode(Node *z);

#endif
