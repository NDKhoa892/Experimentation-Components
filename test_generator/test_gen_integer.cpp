#include <iostream>
#include <fstream>
#include <set>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

const string dir = "integer/";

const int N_TEST = 100;
const int X_MAX = 1000000000;
const int SUB[5] = {20, 20, 20, 20, 20};
const int SUB_N[5] = {10, 100, 1000, 100000, 1000000};

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
        
        set<int> tree;

        for (int j = 0; j < SUB_N[cur_sub]; ++j) {
            int type = 0;
            bool valid = false;
            do {
                type = rand() % 3;
            } while (tree.empty() && type > 0);

            if (type == 0) {        // insert
                int x = 0;
                do {
                    x = rand() % X_MAX;
                } while (tree.count(x) > 0);

                inp << "i " << x << '\n';

                tree.insert(x);
            } else if (type == 1) { // search
                int ans = rand() % 2;

                if (ans == 0) {
                    int x = 0;
                    do {
                        x = rand() % X_MAX;
                    } while (tree.count(x) > 0);

                    inp << "s " << x << '\n';
                    out << "0\n";
                } else {
                    int x = rand() % X_MAX;
                    
                    set<int>::iterator it = tree.lower_bound(x);
                    
                    if (it == tree.end())
                        x = *tree.rbegin();
                    else
                        x = *it;

                    inp << "s " << x << '\n';
                    out << "1\n";
                }
            } else if (type == 2) { // delete
                int x = rand() % X_MAX;
                        
                set<int>::iterator it = tree.lower_bound(x);
                
                if (it == tree.end())
                    x = *tree.rbegin();
                else
                    x = *it;

                inp << "d " << x << '\n';
                
                tree.erase(x);
            }
        }

        ++cur_sub_cnt;
        if (cur_sub_cnt == SUB[cur_sub]) {
            ++cur_sub;
            cur_sub_cnt = 0;
        }
    }
}