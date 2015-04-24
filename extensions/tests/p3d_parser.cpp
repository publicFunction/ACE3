#include "ace_common.h"
#include "p3d\parser.hpp"


int main(int argc, char **argv) {
    ace::p3d::parser _parser;

    if (argc < 2) {
        printf("Usage: %s [file.p3d]", argv[0]);
        return -1;
    }
    _parser.load(argv[1]);

    getchar();

    return 0;
} 