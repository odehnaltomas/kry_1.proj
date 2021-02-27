#include <iostream>
#include "utils.h"
#include <map>
#include "kasiski_test.h"

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

    cout << encrText << endl;

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

    for (auto & iter : distanceCnt) {
        cout << iter.first << "\t" << iter.second << endl;
    }
    /************* KASISKI TEST *************/
    vigCipher::Kasiski kasiskiTest(encrText);
    kasiskiTest.doTest();
    kasiskiTest.printTrigrams();

    return 0;
}
