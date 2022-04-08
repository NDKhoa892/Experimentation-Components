#include <iostream>
#include <fstream>
#include <chrono>

#include "RBTree.h"

using namespace std;
using namespace std::chrono;

const string dir = "struct/";
const string ans = "ans.out";

const int N_TEST = 100;

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

int main() {
    for (int test = 0; test < N_TEST; ++test) {
        string name = "test";

        if (test < 10) name += "0";
        name += to_string(test);

        ifstream inp(dir + name + ".inp");

        RBTree<custom>* tree = new RBTree<custom>();

        char t;
        int i;
        string s;
        while (inp >> t >> i >> s) {
            if (t == 'i')
                tree -> insert({i, s});
            else if (t == 's')
                tree -> search({i, s});
            else
                tree -> erase({i, s});
        }

        delete tree;

        inp.close();
    }
}
