#pragma once

#ifdef _DEBUG

#include <windows.h>
#include <d3d11_1.h>
#include <directxcolors.h>

#include <thread>
#include <memory>

#include "singleton.hpp"

#define IDI_ACE_DEBUG 666

namespace ace {
    namespace debug {

        struct render_window_loop;

        class render_window : 
            public singleton<render_window> {
        public:
            render_window();
            ~render_window();

            HRESULT             init_window(HINSTANCE hInstance, int nCmdShow);
            HRESULT             init_device();
            void                cleanup_device();
            LRESULT CALLBACK    _wndproc(HWND, UINT, WPARAM, LPARAM);
            
            void                init();
            void                render();
            void                render_loop();
        public:
            std::shared_ptr<render_window_loop> _render_loop_thread;

            HINSTANCE               hInst = nullptr;
            HWND                    hWnd = nullptr;
            D3D_DRIVER_TYPE         driverType = D3D_DRIVER_TYPE_NULL;
            D3D_FEATURE_LEVEL       featureLevel = D3D_FEATURE_LEVEL_11_0;
            ID3D11Device*           pd3dDevice = nullptr;
            ID3D11Device1*          pd3dDevice1 = nullptr;
            ID3D11DeviceContext*    pImmediateContext = nullptr;
            ID3D11DeviceContext1*   pImmediateContext1 = nullptr;
            IDXGISwapChain*         pSwapChain = nullptr;
            IDXGISwapChain1*        pSwapChain1 = nullptr;
            ID3D11RenderTargetView* pRenderTargetView = nullptr;

            
        };

        struct render_window_loop {
            render_window_loop(render_window * obj) : thread(&ace::debug::render_window::render_loop, obj) {}
            ~render_window_loop() { thread.join(); }
            std::thread thread;
        };

    };
};

#endif