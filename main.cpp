#include <iostream>
#include "utils.h"
#include "kasiski_test.h"
#include "friedman_test.h"
#include "key_cracker.h"
#include <map>

#define get(x) #x

using namespace std;


inline unsigned short mapChar(char x, char y) {
    if ((x < 97 || x > 122) || (y < 97 || y > 122)) {
        return 255;
    }
    x -= 'a';
    y -= 'a';
    DEBUG("x=%u, y=%u\n", x, y);
    return ((x + y) % 26) + 'a';
}

int main(int argc, char **argv) {
    (void) argv;
    string encrText;
    char chr;
    map<int, int> distanceCnt;
    int keyLen = 0;
    string key;

    if (argc != 1) {
        cerr << "Program doesn't take any arguments!\n"
                "Program only takes encrypted english text from standard input.";
        return 1;
    }

//    char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
//    for(char c : alphabet) {
//        DEBUG("%c - %u (%u)\n", c, (unsigned short) c, (unsigned short) (c - 97) );
//    }

//    unsigned short newChar = mapChar('v', 'k');
//    DEBUG("%u - %c\n", newChar, newChar);

    while (cin >> chr) {
        if (!isalpha(chr)) {
            continue;
        }
        encrText += tolower(chr);
    }

//    cout << encrText << endl;

//    map<char, bool> sawChar;
//    for (size_t i = 0; i < encrText.length(); i++) {
//        if (sawChar.count(encrText[i]) > 0) {
//            continue;
//        } else {
//            sawChar.insert(pair<char, bool>(encrText[i], true));
//        }
//        for (size_t j = i+1; j < encrText.length(); j++) {
//            if (encrText[i] == encrText[j]) {
//                size_t distance = j - i;
//                distanceCnt[distance] += 1;
//            }
//        }
//    }
//
//    for (auto & iter : distanceCnt) {
//        cout << iter.first << "\t" << iter.second << endl;
//    }
    /************* KASISKI TEST *************/
    DEBUG("============= KASISKI TEST =============\n");
    vector<pair<int, int>> dividersVect;

    vigCipher::Kasiski kasiskiTest(encrText);
    dividersVect = kasiskiTest.doTest();
//    kasiskiTest.printTrigrams();

    DEBUG("Divisor\t\tHits\n");
    for (auto i = 0; i < 10; i++) {
        if (dividersVect[i].second != 0) {
            DEBUG("%d\t\t\t%d\n", dividersVect[i].first, dividersVect[i].second);
        }
    }

    /************* FRIEDMAN TEST *************/
    DEBUG("============= FRIEDMAN TEST =============\n");
    float friedmanKeyLen;
    vigCipher::Friedman friedmanTest(encrText);
    friedmanKeyLen = friedmanTest.doTest();

    DEBUG("\n");

    vector<pair<int, float>> friedmanKeyCandidates2;
    friedmanKeyCandidates2 = friedmanTest.doColumWiseCI();

    DEBUG("Key len\t\tCoincidence Index\n");
    for (auto i = 0; i < 10; i++) {
        if (friedmanKeyCandidates2[i].second != 0) {
            DEBUG("%d\t\t\t%f\n", friedmanKeyCandidates2[i].first, friedmanKeyCandidates2[i].second);
        }
    }


    for (auto i = 0; i < 10; i++) {
        for (auto j = 0; j < 10; j++) {
//            DEBUG("kas: %d, fried: %d, %f\n", dividersVect[i].first, friedmanKeyCandidates[j].first, friedmanKeyCandidates[j].second);
            if (dividersVect[i].first == friedmanKeyCandidates2[j].first &&
                friedmanKeyCandidates2[j].second > 0.059) {
                if (keyLen == 0 || keyLen > friedmanKeyCandidates2[j].first) {
                    keyLen = dividersVect[i].first;
                }
            }
        }
    }

    DEBUG("KEY LENGTH: %d\n", keyLen);

    vigCipher::KeyCracker keyCracker(encrText);
    key = keyCracker.crack(keyLen);

    cout << friedmanKeyLen << ";" << dividersVect[0].first << ";" << keyLen << ";" << key << endl;
    return 0;
}
