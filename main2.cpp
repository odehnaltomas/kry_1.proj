#include <iostream>
#include "utils.h"
#include "kasiski_test.h"
#include "friedman_test.h"
#include "key_cracker.h"
#include <map>
#include <thread>

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
    (void) argv;                /** We don't need any input arguments. **/
    string encrText;            /** Contains encrypted input text **/
    char chr;                   /** Help variable to store character form input then to save into encrText **/
    map<int, int> distanceCnt;
    int keyLen = 0;
    string key;

    vector<pair<int, int>> dividersVect;    /** Output of Kasisky test [<key, occurences>,...] **/
    float friedmanKeyLen;                   /** Output of Friedman test **/
    vector<pair<int, float>> friedmanKeyCandidates2;    /** Output of Column wise coincidence index **/

    if (argc != 1) {
        cerr << "Program doesn't take any arguments!\n"
                "Program only takes encrypted english text from standard input.";
        return 1;
    }

    while (cin >> chr) {
        if (!isalpha(chr)) {
            continue;
        }
        encrText += tolower(chr);
    }

    vigCipher::Kasiski kasiskiTest(encrText);
    vigCipher::Friedman friedmanTest(encrText);

    /************* KASISKI TEST *************/
//    dividersVect = kasiskiTest.doTest();
//    kasiskiTest.printTrigrams();
    thread kasiskyThread(&vigCipher::Kasiski::doTest, &kasiskiTest);

    /************* FRIEDMAN TEST *************/
//    friedmanKeyLen = friedmanTest.doTest();

    thread friedmanThread(&vigCipher::Friedman::doTest, &friedmanTest);

    DEBUG("\n");

    /************* COLUMN CI *************/
//    friedmanKeyCandidates2 = friedmanTest.doColumWiseCI();
    thread columnCiThread(&vigCipher::Friedman::doColumWiseCI, &friedmanTest);

    kasiskyThread.join();
    friedmanThread.join();
    columnCiThread.join();

    dividersVect = kasiskiTest.getResult();
    friedmanKeyLen = friedmanTest.getFriedmanKey();
    friedmanKeyCandidates2 = friedmanTest.getColumnCI();


    for (size_t i = 0; i < friedmanKeyCandidates2.size(); i++) {
        for (size_t j = 0; j < friedmanKeyCandidates2.size(); j++) {
//            DEBUG("kas: %d, fried: %d, %f\n", dividersVect[i].first, friedmanKeyCandidates[j].first, friedmanKeyCandidates[j].second);
            if (dividersVect[i].first == friedmanKeyCandidates2[j].first &&
                friedmanKeyCandidates2[j].second > 0.059) {
                if (keyLen == 0 || keyLen > friedmanKeyCandidates2[j].first) {
                    keyLen = dividersVect[i].first;
                }
            }
        }
    }

    DEBUG("============= KASISKI TEST HELP TABLE =============\n");
    DEBUG("Divisor\t\tHits\n");
    for (auto i = 0; i < 40; i++) {
        if (dividersVect[i].second != 0) {
            DEBUG("%d\t\t\t%d\n", dividersVect[i].first, dividersVect[i].second);
        }
    }

    DEBUG("============= FRIEDMAN TEST HELP TABLE =============\n");
    DEBUG("Key len\t\tCoincidence Index\n");
    for (auto i = 0; i < 40; i++) {
        if (friedmanKeyCandidates2[i].second != 0) {
            DEBUG("%d\t\t\t%f\n", friedmanKeyCandidates2[i].first, friedmanKeyCandidates2[i].second);
        }
    }

    DEBUG("KEY LENGTH: %d\n", keyLen);

    vigCipher::KeyCracker keyCracker(encrText);
    keyCracker.crack(keyLen);
    key = keyCracker.getKey();

    cout << friedmanKeyLen << ";" << dividersVect[0].first << ";" << keyLen << ";" << key << endl;
    return 0;
}
