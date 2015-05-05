#pragma once

#ifdef _DEBUG

#include <windows.h>
#include <d3d11_1.h>
#include <directxcolors.h>
#include <DirectXMath.h>

#include <thread>
#include <memory>

#include "singleton.hpp"

#define IDI_ACE_DEBUG 666

namespace ace {
    namespace debug {

        struct d3d_display_worker;
        class d3d_display {
        public:
            d3d_display();
            ~d3d_display();

            virtual bool run();
            virtual bool render();
            virtual bool step();

			virtual bool create(uint32_t, uint32_t, bool);
            virtual bool init();

            virtual bool destroy();

			void render_worker();

			static LRESULT CALLBACK wndproc(HWND, UINT, WPARAM, LPARAM);
			LRESULT CALLBACK _wndproc(HWND, UINT, WPARAM, LPARAM);
        protected:
            std::shared_ptr<d3d_display_worker> _render_thread;

            HINSTANCE                           _hInst = nullptr;
            HWND                                _hWnd = nullptr;
            D3D_DRIVER_TYPE                     _driverType = D3D_DRIVER_TYPE_NULL;
            D3D_FEATURE_LEVEL                   _featureLevel = D3D_FEATURE_LEVEL_11_0;
            ID3D11Device*                       _pd3dDevice = nullptr;
            ID3D11DeviceContext*                _pImmediateContext = nullptr;
            IDXGISwapChain*                     _pSwapChain = nullptr;
            ID3D11RenderTargetView*             _pRenderTargetView = nullptr;
            ID3D11Texture2D*                    _pDepthStencil = nullptr;
            ID3D11DepthStencilView*             _pDepthStencilView = nullptr;

            ID3D11ShaderResourceView*           _pTextureRV1 = nullptr;
            ID3D11ShaderResourceView*           _pTextureRV2 = nullptr;
            ID3D11InputLayout*                  _pBatchInputLayout = nullptr;

			DirectX::XMMATRIX                   _World;
			DirectX::XMMATRIX                   _View;
			DirectX::XMMATRIX                   _Projection;
        };
        struct d3d_display_worker {
            d3d_display_worker(d3d_display * obj) : thread(&ace::debug::d3d_display::render_worker, obj) {}
            ~d3d_display_worker() { thread.join(); }
            std::thread thread;
        };
    };
};

#endif