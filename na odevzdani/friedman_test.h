#ifndef FRIEDMAN_H
#define FRIEDMAN_H

#include <string>
#include <map>
#include <vector>
#include <mutex>
#endif

using namespace std;

namespace vigCipher {
    class Friedman {
    public:
        explicit Friedman(string &text) : encrText(text) {
            m_key.lock();
        };

        void doTest();
        void doColumWiseCI();

        float getFriedmanKey() {return friedmanKeyLen;};
        vector<pair<int, float>> getColumnCI() {return keyLenCandidates;};

    private:
        const string encrText;
        struct columnInfo {
            int letterCnt = 0;
            int sumNi = 0;
            float kappa0;
            map<char, int> letterMap; // Frequency of letters of english alphabet
        };
        typedef struct columnInfo columnInfo;
        float friedmanKeyLen;
        vector<pair<int, float>> keyLenCandidates;
        mutex m_key;

        static bool cmp(pair<int, float>& a, pair<int, float>& b);

        void sortMap(map<int, float>& m, vector<pair<int, float>>& vect);
    };
}