#if defined(DEVEL) && defined(USE_DIRECTX)

#include "penetration_display.hpp"
#include "controller.hpp"
#include "game.hpp"

namespace ace {
    namespace vehicledamage {
        namespace debug {
            penetration_display::penetration_display() :
                dispatcher() {
                _active_vehicle = nullptr;

                add("register_vehicle", std::bind(&ace::vehicledamage::debug::penetration_display::register_vehicle, this, std::placeholders::_1, std::placeholders::_2));
                add("show_hit", std::bind(&ace::vehicledamage::debug::penetration_display::show_hit, this, std::placeholders::_1, std::placeholders::_2));
            }

            bool penetration_display::show_hit(const arguments &args, std::string &result) {
                std::lock_guard<std::mutex> _lock(_render_lock);

                _active_hits.push_back(gamehit::create(args));

                return true;
            }
            bool penetration_display::register_vehicle(const arguments &args, std::string &result) {
                std::lock_guard<std::mutex> _lock(_render_lock);

                uint32_t id = args[0];
                
                _active_vehicle = ace::vehicledamage::controller::get().vehicles[id];

                return true;
            }

            bool penetration_display::init() {
                HRESULT hr = S_OK;
                d3d_display::init();

                std::lock_guard<std::mutex> _lock(_render_lock);
                _States.reset(new CommonStates(_pd3dDevice));
                _FXFactory.reset(new EffectFactory(_pd3dDevice));
                _Batch.reset(new PrimitiveBatch<VertexPositionColor>(_pImmediateContext));
                //_Font.reset(new SpriteFont(_pd3dDevice, L"italic.spritefont"));
  
                _BatchEffect.reset(new BasicEffect(_pd3dDevice));
                _BatchEffect->SetVertexColorEnabled(true);

                {
                    void const* shaderByteCode;
                    size_t byteCodeLength;

                    _BatchEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

                    hr = _pd3dDevice->CreateInputLayout(VertexPositionColor::InputElements,
                        VertexPositionColor::InputElementCount,
                        shaderByteCode, byteCodeLength,
                        &_pBatchInputLayout);
                    if (FAILED(hr))
                        return hr;
                }
                _BatchEffect->SetView(XMLoadFloat4x4(&_View));
                _BatchEffect->SetProjection(XMLoadFloat4x4(&_Projection));
            }

            bool penetration_display::step(void) {

                const XMVECTORF32 xaxis = { 20.f, 0.f, 0.f };
                const XMVECTORF32 yaxis = { 0.f, 0.f, 20.f };
                DrawGrid(*_Batch, xaxis, yaxis, g_XMZero, 20, 20, Colors::Gray);

                if (_active_vehicle) {
                    DrawObject(0, *_Batch, *_active_vehicle->object, Colors::White);
                }
                if(_active_hits.size() > 0)
                    DrawHits(0, *_Batch, Colors::Red);

                _BatchEffect->SetView(XMLoadFloat4x4(&_View));
                _BatchEffect->SetProjection(XMLoadFloat4x4(&_Projection));

                return true;
            }

            void penetration_display::DrawHits(uint32_t lod, PrimitiveBatch<VertexPositionColor>& batch, GXMVECTOR color) {

                batch.Begin();

                for (gamehit_p & hit : _active_hits) {
                    ace::vector3<float> hit_from, hit_to;

                    hit_from = hit->impactposition;
                    hit_to = hit_from + (hit->impactvelocity * 5);

                    XMVECTORF32 from = { hit_from.x(), hit_from.y(), hit_from.z() };
                    XMVECTORF32 to = { hit_to.x(), hit_to.y(), hit_to.z() };

                    VertexPositionColor v1(from, color);
                    VertexPositionColor v2(to, color);

                    batch.DrawLine(v1, v2);
                }


                batch.End();

            }
            void penetration_display::DrawObject(uint32_t lod, PrimitiveBatch<VertexPositionColor>& batch, ace::simulation::object & obj, GXMVECTOR color) {

                batch.Begin();

                for (auto & face : obj.lods[lod]->faces) {
                    XMVECTORF32 v[3] = {
                        { face->vertices[0]->x(), face->vertices[0]->z(), face->vertices[0]->y() },
                        { face->vertices[1]->x(), face->vertices[1]->z(), face->vertices[1]->y() },
                        { face->vertices[2]->x(), face->vertices[2]->z(), face->vertices[2]->y() }
                    };

                    VertexPositionColor v1(v[0], color);
                    VertexPositionColor v2(v[1], color);
                    VertexPositionColor v3(v[2], color);

                    batch.DrawLine(v1, v2);
                    batch.DrawLine(v2, v3);
                    batch.DrawLine(v3, v1);
                    //batch.DrawTriangle(v1, v2, v3);
                }

                batch.End();
            }
            void penetration_display::DrawGrid(PrimitiveBatch<VertexPositionColor>& batch, FXMVECTOR xAxis, FXMVECTOR yAxis, FXMVECTOR origin, size_t xdivs, size_t ydivs, GXMVECTOR color) {
                _BatchEffect->Apply(_pImmediateContext);

                _pImmediateContext->IASetInputLayout(_pBatchInputLayout);

                batch.Begin();

                xdivs = std::max<size_t>(1, xdivs);
                ydivs = std::max<size_t>(1, ydivs);

                for (size_t i = 0; i <= xdivs; ++i) {
                    float fPercent = float(i) / float(xdivs);
                    fPercent = (fPercent * 2.0f) - 1.0f;
                    XMVECTOR vScale = XMVectorScale(xAxis, fPercent);
                    vScale = XMVectorAdd(vScale, origin);

                    VertexPositionColor v1(XMVectorSubtract(vScale, yAxis), color);
                    VertexPositionColor v2(XMVectorAdd(vScale, yAxis), color);
                    batch.DrawLine(v1, v2);
                }

                for (size_t i = 0; i <= ydivs; i++) {
                    FLOAT fPercent = float(i) / float(ydivs);
                    fPercent = (fPercent * 2.0f) - 1.0f;
                    XMVECTOR vScale = XMVectorScale(yAxis, fPercent);
                    vScale = XMVectorAdd(vScale, origin);

                    VertexPositionColor v1(XMVectorSubtract(vScale, xAxis), color);
                    VertexPositionColor v2(XMVectorAdd(vScale, xAxis), color);
                    batch.DrawLine(v1, v2);
                }

                batch.End();
            }
        }
    }
}


#endif