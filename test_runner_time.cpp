#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

const string dir = "struct/";
const string runner = "./runner";
const string ans = "ans.out";

const int N_TEST = 100;

bool checkResult(string name) {
    ifstream result(name);
    ifstream answer(ans);

    int x_res = 0, x_ans = 0;
    for (int line = 1; result >> x_res; ++line) {
        if (answer >> x_ans) {
            if (x_res != x_ans) {
                cout << "WRONG ANSWER: Wrong search answer on line " << line << '\n';
                return false;
            }
        } else {
            cout << "WRONG ANSWER: Missing search answers on line " << line << '\n';
            return false;
        }
    }

    cout << "ACCEPTED: All answers are correct\n";

    return true;
}

int main() {
    int totalTime = 0;
    int totalAccepted = 0;

    for (int test = 0; test < N_TEST; ++test) {
        string name = "test";

        if (test < 10) name += "0";
        name += to_string(test);

        name = dir + name + ".inp";

        string cmd = runner + " " + name;

        cout << "Running on test " << test << '\n';

        auto start = high_resolution_clock::now();
        system(cmd.c_str());
        auto stop = high_resolution_clock::now();

        totalAccepted += checkResult(name);

        int runningTime = duration_cast<milliseconds>(stop - start).count();
        cout << "Total running time: " << runningTime << " ms\n\n";
        totalTime += runningTime;
    }

    cout << "Accepted " << totalAccepted << "/" << N_TEST << '\n';
    cout << "Total running time over " << N_TEST << " tests: " << totalTime << " ms\n";
}
