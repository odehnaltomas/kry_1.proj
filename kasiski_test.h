#ifndef KASISKI_H
#define KASISKI_H

#include <iostream>
#include <map>
#include <string>
#include <set>
#include <vector>
#include <memory>
#endif

using namespace std;

namespace vigCipher {
    class Kasiski {
    public:
        explicit Kasiski(string &text) : encrText{text} {};

        void doTest();

        vector<pair<int, int>> getResult(){return dividersVect;};

        void printTrigrams();
    private:
        const string encrText;
        map<string, pair<int, set<int>>> trigrams;
//        map<string, pair<int, set<int>>> fourgrams;
//        map<string, pair<int, set<int>>> fivegrams;
//        map<string, pair<int, set<int>>> sixgrams;
        int biggestDistance;    /** Save biggest found distance between two same trigrams. **/

        vector<pair<int, int>> dividersVect;

        void do_n_graph(int n, map<string, pair<int, set<int>>> &nGraphArr);

        static bool cmp(pair<int, int>& a, pair<int, int>& b);

        void sortMap(map<int, int>& m, vector<pair<int, int>>& vect);
    };
}
