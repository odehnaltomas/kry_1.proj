#include "kasiski_test.h"
#include "utils.h"

using namespace std;

void vigCipher::Kasiski::doTest() {
    string trigram;
    int comp;
    for (size_t i = 0; i < encrText.length()-2; i++) {
        trigram = encrText.substr(i, 3);
        if (trigrams.count(trigram) > 0) {
            continue;
        }
//        DEBUG("trigram: %s\n", trigram.c_str());

        for (size_t j = i+1; j < encrText.length()-2; j++) {
            comp = encrText.compare(j, 3, trigram);
//            DEBUG("Is '%s' == '%s'?\n", trigram.c_str(), encrText.substr(j, 3).c_str());

            if (comp == 0) {
//                DEBUG("YES\n");
//                DEBUG("First occurence: %lu\n", i);
//                DEBUG("Distance to next occurence: %lu\n", j-i);

                auto iter = trigrams.find(trigram);
                if (iter == trigrams.end()) {
                    set<int> set1;
                    set1.insert(j-i);
                    pair<int, set<int>> p(i, set1);
                    trigrams.insert(pair<string, pair<int, set<int>>>(trigram, p));
                } else {
                    iter->second.second.insert(j-i);
                }
            } else {
//                DEBUG("NO\n");
            }
        }


    }
}

void vigCipher::Kasiski::printTrigrams() {
    DEBUG("PRINT TRIGRAMS:\n");
    DEBUG("  Number of trigrams: %lu\n", trigrams.size());
    DEBUG("\tTri:\t1. occur\tNext occur:\n");
    for (auto iter = trigrams.begin(); iter != trigrams.end(); iter++) {
        DEBUG("\t%s\t\t%d\t\t\t", iter->first.c_str(), iter->second.first);
        for (int iterSet : iter->second.second) {
            DEBUG("%d, ", iterSet);
        }
        DEBUG("\n");
    }
}