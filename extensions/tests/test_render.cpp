#include <Windows.h>

#include "directx/render_window.hpp"

int WINAPI wWinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow ) {
    ace::debug::render_window::get().init();
    ace::debug::render_window::get().render_loop();
}
