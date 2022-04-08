#include <iostream>
#include <fstream>
#include <set>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

const string dir = "struct/";

const int N_TEST = 100;
const int I_MAX = 1000000000;   // 10^9
const int S_MAX = 308915776;    // 26^6
const int SUB[5] = {20, 20, 20, 20, 20};
const int SUB_N[5] = {10, 100, 1000, 100000, 1000000};

struct custom {
    int i;
    string s;

    custom(int i, string s) {
        this -> i = i;
        this -> s = s;
    }

    bool operator < (const custom &other) const {
        if (i != other.i)
            return i < other.i;
        return s < other.s;
    }
};

string int_to_string(int x) {
    string s = "";

    while (x) {
        s = char('a' + (x % 26)) + s;
        x /= 26;
    }

    return s;
}

int main() {
    srand(time(NULL));

    int cur_sub = 0;
    int cur_sub_cnt = 0;

    for (int i = 0; i < N_TEST; ++i) {
        string name = "test";

        if (i < 10) name += "0";
        name += to_string(i);

        ofstream inp(dir + name + ".inp");
        ofstream out(dir + name + ".out");

        set<custom> tree;

        for (int j = 0; j < SUB_N[cur_sub]; ++j) {
            int type = 0;
            do {
                type = rand() % 3;
            } while (tree.empty() && type > 0);

            if (type == 0) {        // insert
                int i = 0;
                string s = " ";
                do {
                    i = rand() % I_MAX;
                    s = int_to_string(rand() % S_MAX + 1);
                } while (tree.count({i, s}) > 0);

                inp << "i " << i << ' ' << s << '\n';

                tree.insert({i, s});
            } else if (type == 1) { // search
                int ans = rand() % 2;

                if (ans == 0) {
                    int i = 0;
                    string s = " ";
                    do {
                        i = rand() % I_MAX;
                        s = int_to_string(rand() % S_MAX + 1);
                    } while (tree.count({i, s}) > 0);

                    inp << "s " << i << ' ' << s << '\n';
                    out << "0\n";
                } else {
                    int i = rand() % I_MAX;
                    string s = int_to_string(rand() % S_MAX + 1);

                    set<custom>::iterator it = tree.lower_bound({i, s});

                    if (it == tree.end()) {
                        i = (*tree.rbegin()).i;
                        s = (*tree.rbegin()).s;
                    } else {
                        i = (*it).i;
                        s = (*it).s;
                    }

                    inp << "s " << i << ' ' << s << '\n';
                    out << "1\n";
                }
            } else if (type == 2) { // delete
                int i = rand() % I_MAX;
                string s = int_to_string(rand() % S_MAX + 1);

                set<custom>::iterator it = tree.lower_bound({i, s});

                if (it == tree.end()) {
                    i = (*tree.rbegin()).i;
                    s = (*tree.rbegin()).s;
                } else {
                    i = (*it).i;
                    s = (*it).s;
                }

                inp << "d " << i << ' ' << s << '\n';

                tree.erase({i, s});
            }
        }

        ++cur_sub_cnt;
        if (cur_sub_cnt == SUB[cur_sub]) {
            ++cur_sub;
            cur_sub_cnt = 0;
        }
    }
}
