#include <Windows.h>

#include "directx/d3d_display.hpp"

using namespace ace::debug;

int main(int argc, char **argv) {
    d3d_display test;
    test.create();
    test.init();

    test.run();

    return -1;
}