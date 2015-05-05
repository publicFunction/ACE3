#include <Windows.h>

#include "directx/render_window.hpp"

int main(int argc, char **argv) {
    ace::debug::render_window::get().init();
    ace::debug::render_window::get().render_loop();
}
