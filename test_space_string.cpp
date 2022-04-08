#include <iostream>
#include <fstream>
#include <chrono>

#include "RBTree.h"

using namespace std;
using namespace std::chrono;

const string dir = "string/";
const string ans = "ans.out";

const int N_TEST = 100;

int main() {
    for (int test = 0; test < N_TEST; ++test) {
        string name = "test";

        if (test < 10) name += "0";
        name += to_string(test);

        ifstream inp(dir + name + ".inp");

        RBTree<string>* tree = new RBTree<string>();

        char t;
        string x;
        while (inp >> t >> x) {
            if (t == 'i')
                tree -> insert(x);
            else if (t == 's')
                tree -> search(x);
            else
                tree -> erase(x);
        }

        delete tree;

        inp.close();
    }
}
