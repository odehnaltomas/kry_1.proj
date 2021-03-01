#pragma once

#include "utils.h"
#include <map>
#include <string>

using namespace std;

namespace vigCipher {
    class KeyCracker {
    public:
        struct columnInfo {
            int letterCnt = 0;
            int sumNi = 0;
            float kappa0;
            map<char, pair<int, float>> letterMap;
            array<float, 26> similarityArr;
        };

        map<char, float> engLettersFreq {{'a', 0.08167}, {'b', 0.01492}, {'c', 0.02782}, {'d', 0.04253}, {'e', 0.12702},
                                         {'f', 0.02228}, {'g', 0.02015}, {'h', 0.06094}, {'i', 0.06966}, {'j', 0.00153},
                                         {'k', 0.00772}, {'l', 0.04025}, {'m', 0.02406}, {'n', 0.06749}, {'o', 0.07507},
                                         {'p', 0.01929}, {'q', 0.00095}, {'r', 0.05987}, {'s', 0.06327}, {'t', 0.09056},
                                         {'u', 0.02758}, {'v', 0.00978}, {'w', 0.02360}, {'x', 0.00150}, {'y', 0.01974},
                                         {'z', 0.00074}};

        typedef struct columnInfo columnInfo;

        explicit KeyCracker(string &text) : encrText{text} {};

        string crack(int keyLen);

    private:
        string encrText;
    };
}