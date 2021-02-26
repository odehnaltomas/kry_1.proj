#include <iostream>
#include "utils.h"

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

    cout << encrText;

    return 0;
}
