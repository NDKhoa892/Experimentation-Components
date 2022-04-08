#include <iostream>
#include <fstream>

#include "RBTree.h"

struct custom {
    int i;
    string s;

    custom() {
        i = 0;
        s = " ";
    }

    custom(int i, string s) {
        this -> i = i;
        this -> s = s;
    }

    bool operator < (const custom &other) const {
        if (i != other.i)
            return i < other.i;
        return s < other.s;
    }

    bool operator > (const custom &other) const {
        if (i != other.i)
            return i > other.i;
        return s > other.s;
    }

    bool operator == (const custom &other) const {
        return i == other.i && s == other.s;
    }

    bool operator != (const custom &other) const {
        return i != other.i || s != other.s;
    }
};

int main(int argc, char *argv[]) {
    // argv[1] : name of input file
    ifstream inp(argv[1]);
    ofstream out("ans.out");

    RBTree<custom>* tree = new RBTree<custom>();

    char t;
    int i;
    string s;
    while (inp >> t >> i >> s) {
        if (t == 'i')
            tree -> insert({i, s});
        else if (t == 's')
            out << tree -> search({i, s}) << '\n';
        else
            tree -> erase({i, s});
    }

    delete tree;

    inp.close();
    out.close();
}
