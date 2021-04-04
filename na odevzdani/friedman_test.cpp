#include "friedman_test.h"
#include "utils.h"
#include <algorithm>
#include <cmath>

void vigCipher::Friedman::doTest() {
    map<char, int> letterFreq;
    map<char, int> letterFreq2;
    map<int, float> keyCandidates;
    float kappP = 0.0667;
    float kappR = (float)1/26;
    float kapp0;
    float key;

    /** Initialize values of map to 0. And set keys in alphabetical order. **/
    for (char c : "abcdefghijklmnopqrstuvwxyz") {
        letterFreq[c] = 0;
    }

//    for (pair<const char, int>& p : letterFreq) {
//        DEBUG("%c - %d\n", p.first, p.second);
//    }

    for (const char & c : encrText) {
        letterFreq[c]++;
    }

    int sumNi = 0;
    int sum = 0;
    for (pair<const char, int>& p : letterFreq) {
        sumNi += p.second*(p.second-1);
//        DEBUG("%c - %d\n", p.first, p.second);
        sum += p.second;
    }
    DEBUG("Sum of letters: %d\n", sum);
//    DEBUG("Size of text: %lu\n", encrText.length());

    kapp0 = (float)sumNi/(float)(sum*(sum-1));
    DEBUG("Kappa 0: %f\n", kapp0);

    key = (kappP - kappR) / (kapp0 - kappR);
//    key = ((kappP - kappR) * sum) / ((sum - 1) * kapp0 - (sum * kappR) + kappP);
    DEBUG("Estimated key length: %f\n", key);

    friedmanKeyLen = key;
    m_key.unlock();
}


void vigCipher::Friedman::doColumWiseCI() {
    map<int, vector<columnInfo>> columnsCI;
//    map<int, float> keyCandidates;
    map<int, float> avgCis;
    m_key.lock();
    int maxKeyLen = (int) ceil(friedmanKeyLen) * 2;
//    int maxKeyLen = 200;
    m_key.unlock();


    for (auto i = 1; i < maxKeyLen; i++) {
        columnsCI[i].resize(i);
        for (char c : "abcdefghijklmnopqrstuvwxyz") {
            columnsCI[i][i-1].letterMap[c] = 0;
        }
    }

    for (auto i = 1; i < maxKeyLen; i++) {
        for (auto j = 0; j < i; j++) {
            columnInfo& columnInfo1 = columnsCI[i][j];
            for (size_t k = j; k < encrText.length(); k+=i) {
                columnInfo1.letterMap[encrText[k]]++;
                columnInfo1.letterCnt++;
            }

            for (pair<const char, int>& p : columnInfo1.letterMap) {
                columnInfo1.sumNi += p.second*(p.second-1);
            }

            columnInfo1.kappa0 = (float)columnInfo1.sumNi/(float)(columnInfo1.letterCnt*(columnInfo1.letterCnt-1));
        }
    }

    float sumCi = 0;
    for (auto i = 1; i < maxKeyLen; i++) {
        for (auto j = 0; j < i; j++) {
            sumCi += columnsCI[i][j].kappa0;
        }
        avgCis[i] = sumCi / (float)columnsCI[i].size();
        sumCi = 0;
    }

//    DEBUG("Key len:\tAverage CI:\tCoincidenceIndexes:\n");
//    for (auto i = 1; i < 31; i++) {
//        DEBUG("%d\t\t\t%f\t", i, avgCis[i]);
//        for (auto j = 0; j < i; j++) {
//            DEBUG("%f  ", columnsCI[i][j].kappa0);
//        }
//        DEBUG("\n");
//    }

    sortMap(avgCis, keyLenCandidates);
}


bool vigCipher::Friedman::cmp(pair<int, float>& a, pair<int, float>& b) {
    return a.second > b.second;
}

void vigCipher::Friedman::sortMap(map<int, float>& m, vector<pair<int, float>>& vect) {
    for (auto& it : m) {
        vect.push_back(it);
    }

    sort(vect.begin(), vect.end(), cmp);
}