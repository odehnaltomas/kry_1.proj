#include "kasiski_test.h"
#include "utils.h"
#include <algorithm>

using namespace std;

void vigCipher::Kasiski::doTest() {
    int keyLen = 3; /** Hypothesized keyword length of cipher. **/

    do_n_graph(3, trigrams);
//    do_n_graph(4, fourgrams);
//    do_n_graph(5, fivegrams);
//    do_n_graph(6, sixgrams);

    map<int, int> dividers;
//    dividers.resize(biggestDistance);
    for (auto & trig : trigrams) {
        for (int distance : trig.second.second) {
            for (int i = 2; i < distance; i++) {
                if ((distance % i) == 0) {
                    dividers[i]++;
                }
            }
        }
    }

    sortMap(dividers, dividersVect);

//    DEBUG("Divisor\tHits\n");
//    for (int i = 0; i < biggestDistance; i++) {
//        if (dividersVect[i].second != 0) {
//            DEBUG("%d\t\t\t%d\n", dividersVect[i].first, dividersVect[i].second);
//        }
//    }
    keyLen = (dividersVect.front().first);
    DEBUG("Kasisky keyword lenght: %d\n", keyLen);

    return;
}

void vigCipher::Kasiski::do_n_graph(int n, map<string, pair<int, set<int>>> &nGraphArr) {
    string nGraph; /** String with 3 characters. **/
    int comp;       /** Variable for string comparing. **/

    for (size_t i = 0; i < encrText.length()-(n-1); i++) {
        nGraph = encrText.substr(i, n);
        /** Check if trigram was already examined **/
        if (nGraphArr.count(nGraph) > 0) {
            continue;
        }
//        DEBUG("trigram: %s\n", trigram.c_str());

        for (size_t j = i+1; j < encrText.length()-(n-1); j++) {
            comp = encrText.compare(j, n, nGraph);
//            DEBUG("Is '%s' == '%s'?\n", trigram.c_str(), encrText.substr(j, 3).c_str());

            /** Check if trigram was found somewhere else in the text. **/
            if (comp == 0) {
                /** Yes it was **/
//                DEBUG("YES\n");
//                DEBUG("First occurence: %lu\n", i);
//                DEBUG("Distance to next occurence: %lu\n", j-i);

                auto iter = nGraphArr.find(nGraph);
                int distance = j-i;
                if (iter == nGraphArr.end()) {
                    /** Check and set new biggest distance **/
                    biggestDistance = (distance > biggestDistance) ? distance : biggestDistance;

                    set<int> set1;
                    set1.insert(distance);
                    pair<int, set<int>> p(i, set1);
                    nGraphArr.insert(pair<string, pair<int, set<int>>>(nGraph, p));
                } else {
                    iter->second.second.insert(distance);
                }
            }
        }
    }
}

bool vigCipher::Kasiski::cmp(pair<int, int>& a, pair<int, int>& b) {
    return a.second > b.second;
}

void vigCipher::Kasiski::sortMap(map<int, int>& m, vector<pair<int, int>>& vect) {
    for (auto& it : m) {
        vect.push_back(it);
    }

    sort(vect.begin(), vect.end(), cmp);
}

/**
 *  Print found trigrams, their first occurrence and distances to other occurrences.
 */
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