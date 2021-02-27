#pragma once
#include <iostream>
#include <map>
#include <string>
#include <set>

using namespace std;

namespace vigCipher {
    class Kasiski {
    public:
        string encrText;

        explicit Kasiski(string &text) : encrText{text} {};

        void doTest();

        void printTrigrams();
    private:
        map<string, pair<int, set<int>>> trigrams;
    };
}
