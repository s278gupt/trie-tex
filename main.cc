#include <fstream>
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

struct Trie {
   Node *root;
};

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

void printLatex(Trie *t) {
   ofstream file;
   string filename = "example.txt";
   file.open(filename);
   cout << "Writing to " << filename << endl;
   
   file << "\\begin{center}" << endl;
   file << "\\begin{tikzpicture}[" << endl;
   file << " scale=0.6,font=\\footnotesize," << endl;
   file << " triee/.style={draw=none,fill=white,inner sep=1pt,font=\\scriptsize}" << endl;
   file << "]" << endl;
   
   if (t->root != NULL) {
      file << "\\node(r)[solid node]{}" << endl;
      for (int i = 0; i < (t->root)->numChildren; i++) {
         printNodes(file, ((t->root)->children)[i]);
      }
   }

   file << ";" << endl;
   file << "\\end{tikzpicture}" << endl;
   file << "\\end{center}" << endl;
   file.close();
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
      t->root = createNode(NULL, "", numChildren, "");
      cout << "Added root successfully" << endl;
   } else {
      cout << "Input must start with root command. See `trie-tex help` for more." << endl;
      return 1;
   }

   // Create the rest of the trie
   int success = createTrie(t->root);
   if (success == 0) {
      // Print Latex
      printLatex(t);
   }

   deleteTrie(t);
   return 0;
}
