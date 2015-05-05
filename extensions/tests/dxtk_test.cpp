#include <Windows.h>

#include "directx/d3d_display.hpp"

#include "CommonStates.h"
#include "DDSTextureLoader.h"
#include "Effects.h"
#include "GeometricPrimitive.h"
#include "Model.h"
#include "PrimitiveBatch.h"
#include "ScreenGrab.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include "VertexTypes.h"

using namespace ace::debug;
using namespace DirectX;

class d3d_test : public d3d_display {   
public:
    bool step(void) override {

        return true;
    }
	std::unique_ptr<CommonStates>                           _States;
	std::unique_ptr<GeometricPrimitive>                     _Shape;
	std::unique_ptr<PrimitiveBatch<VertexPositionColor>>    _Batch;
	std::unique_ptr<SpriteFont>                             _Font;
};

int main(int argc, char **argv) {
    d3d_test test;
    test.create();
    test.init();

    test.run();

    return -1;
}