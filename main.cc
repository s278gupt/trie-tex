#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "node.h"
#include "trie.h"
using namespace std;

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
