#include <iostream>
#include <fstream>

#include "RBTree.h"

int main(int argc, char *argv[]) {
    // argv[1] : name of input file
    ifstream inp(argv[1]);
    ofstream out("ans.out");

    RBTree<int>* tree = new RBTree<int>();

    char t;
    int x;
    while (inp >> t >> x) {
        if (t == 'i')
            tree -> insert(x);
        else if (t == 's')
            out << tree -> search(x) << '\n';
        else
            tree -> erase(x);
    }

    delete tree;

    inp.close();
    out.close();
}
