#pragma once
#include <iostream>
#include <map>
#include <string>
#include <set>
#include <vector>
#include <memory>

using namespace std;

namespace vigCipher {
    class Kasiski {
    public:
        string encrText;

        explicit Kasiski(string &text) : encrText{text} {};

        vector<pair<int, int>> doTest();

        void printTrigrams();
    private:
        map<string, pair<int, set<int>>> trigrams;
//        map<string, pair<int, set<int>>> fourgrams;
//        map<string, pair<int, set<int>>> fivegrams;
//        map<string, pair<int, set<int>>> sixgrams;
        int biggestDistance;    /** Save biggest found distance between two same trigrams. **/

        void do_n_graph(int n, map<string, pair<int, set<int>>> &nGraphArr);

        static bool cmp(pair<int, int>& a, pair<int, int>& b);

        void sortMap(map<int, int>& m, vector<pair<int, int>>& vect);
    };
}
