#if defined(DEVEL) && defined(USE_DIRECTX)

#include "penetration_display.hpp"

namespace ace {
	namespace vehicledamage {
		namespace debug {

			bool penetration_display::init() {
				HRESULT hr = S_OK;
				d3d_display::init();
				// Create DirectXTK objects
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

				_World = XMMatrixIdentity();

				// Initialize the view matrix
				XMVECTOR Eye = XMVectorSet(1.0f, 6.0f, -6.0f, 0.0f);
				XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
				XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
				_View = XMMatrixLookAtLH(Eye, At, Up);

				_BatchEffect->SetView(_View);

				// Initialize the projection matrix
				RECT rc;
				GetClientRect(_hWnd, &rc);
				UINT width = rc.right - rc.left;
				UINT height = rc.bottom - rc.top;
				_Projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, width / (FLOAT)height, 0.01f, 100.0f);

				_BatchEffect->SetProjection(_Projection);
			}

			bool penetration_display::step(void) {

				const XMVECTORF32 xaxis = { 20.f, 0.f, 0.f };
				const XMVECTORF32 yaxis = { 0.f, 0.f, 20.f };
				DrawGrid(*_Batch, xaxis, yaxis, g_XMZero, 20, 20, Colors::Gray);

				//DrawObject(0, *_Batch, *_object, Colors::White);

				return true;
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