#pragma once
// Libaries for direct3D
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")

#include <Windows.h>
#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <DirectXMath.h>
using namespace DirectX;

class direct3D
{
public:
	direct3D();
	~direct3D();
	bool Init(int wWidth, int wHeight, bool vsync, HWND hwnd, bool fScreen, float sDepth, float sNear);
	void Shutdown();

	void BeginScene(float red, float green, float blue, float alpha);
	void EndScene();

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();

	void GetProjectionMatrix(XMFLOAT4X4& ProjectionMatrix);
	void GetWorldMatrix(XMFLOAT4X4& WorldMatrix);
	void GetOrthoMatrix(XMFLOAT4X4& OrthoMatrix);

	void GetVideoCardInfo(char* name, int& memory);

private:
	bool m_Vsync_enabled;
	int m_videoCardMemory;
	char m_videoCardDescription[128];
	IDXGISwapChain* m_swapChain;
	ID3D11Device* m_Device;
	ID3D11DeviceContext* m_deviceContext;
	ID3D11RenderTargetView* m_renderTargetView;
	ID3D11Texture2D* m_depthStencilBuffer;
	ID3D11DepthStencilState* m_depthStencilState;
	ID3D11DepthStencilView* m_depthStencilView;
	ID3D11RasterizerState* m_rasterState;
	XMFLOAT4X4 m_projectionMatrix;
	XMFLOAT4X4 m_worldMatrix;
	XMFLOAT4X4 m_orthoMatrix;
};

