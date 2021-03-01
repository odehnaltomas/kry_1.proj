#pragma once
#include <string>
#include <map>
#include <vector>

using namespace std;

namespace vigCipher {
    class Friedman {
    public:
        string encrText;

        struct columnInfo {
            int letterCnt = 0;
            int sumNi = 0;
            float kappa0;
            map<char, int> letterMap;
        };

        typedef struct columnInfo columnInfo;

        explicit Friedman(string &text) : encrText{text} {};

        float doTest();

        vector<pair<int, float>> doColumWiseCI();

    private:
        static bool cmp(pair<int, float>& a, pair<int, float>& b);

        void sortMap(map<int, float>& m, vector<pair<int, float>>& vect);
    };
}