#include "key_cracker.h"
#include <vector>

void vigCipher::KeyCracker::crack(int keyLen) {
    vector<columnInfo> columnsCI(keyLen);

//    for (auto i = 0; i < keyLen; i++) {
//        for (char c : "abcdefghijklmnopqrstuvwxyz") {
//            columnsCI[i].letterMap[c] = 0;
//        }
//    }

    for (int j = 0; j < keyLen; j++) {
        columnInfo& columnInfo1 = columnsCI[j];
        for (size_t k = j; k < encrText.length(); k+=keyLen) {
            columnInfo1.letterMap[encrText[k]].first++;
            columnInfo1.letterCnt++;
        }

        for (auto& p : columnInfo1.letterMap) {
            p.second.second = ((float)p.second.first / (float)columnInfo1.letterCnt);
        }

        for (auto k = 0; k < 26; k++) {
            for (auto& p : columnInfo1.letterMap) {
                columnInfo1.similarityArr[k] += p.second.second * engLettersFreq[(p.first-'a'-k+26)%26+'a'];
            }
        }
    }

    DEBUG("\n");
    for (auto i = 0; i < keyLen; i++) {
        columnInfo& columnInfo1 = columnsCI[i];
        DEBUG("%d:  ", i);
        for (auto j = 0; j < 26; j++) {
            DEBUG("%f,", columnInfo1.similarityArr[j]);
        }
        DEBUG("\n");
    }

    pair<char, float> biggest;
    for (auto i = 0; i < keyLen; i++) {
        for (auto j = 0; j < 26; j++) {
            if (columnsCI[i].similarityArr[j] > biggest.second) {
                biggest.first = j + 'a';
                biggest.second = columnsCI[i].similarityArr[j];
            }
        }
        key.push_back(biggest.first);
        biggest.second = 0;
    }
    DEBUG("KEY:%s\n", key.c_str());
}