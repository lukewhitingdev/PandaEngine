#pragma once

#include <windows.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>
#include "resource.h"

using namespace DirectX;

class mesh;

struct SimpleVertex
{
    XMFLOAT3 Pos;
    XMFLOAT4 Color;
};

struct ConstantBuffer
{
	XMMATRIX mWorld;
	XMMATRIX mView;
	XMMATRIX mProjection;
};

class Application
{
private:
	HINSTANCE               _hInst;
	HWND                    _hWnd;
	D3D_DRIVER_TYPE         _driverType;
	D3D_FEATURE_LEVEL       _featureLevel;
	ID3D11Device*           _pd3dDevice;
	ID3D11DeviceContext*    _pImmediateContext;
	IDXGISwapChain*         _pSwapChain;
	ID3D11RenderTargetView* _pRenderTargetView;
	ID3D11VertexShader*     _pVertexShader;
	ID3D11PixelShader*      _pPixelShader;
	ID3D11InputLayout*      _pVertexLayout;
	ID3D11Buffer*           _pVertexBuffer;
	ID3D11Buffer*           _pIndexBuffer;
	ID3D11Buffer*           _pConstantBuffer;
	ID3D11DepthStencilView* _depthStencilView;
	ID3D11Texture2D*		_depthStencilBuffer;
	ID3D11RasterizerState*	_wireFrame;
	ID3D11RasterizerState*	_normalView;
	XMFLOAT4X4              _world, _world2; // For the cubes in the world
	XMFLOAT4X4              _view;
	XMFLOAT4X4              _projection;

	// Refactored
	mesh* MeshManager;

private:
	HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);
	HRESULT InitDevice();
	void Cleanup();
	HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
	HRESULT InitShadersAndInputLayout();
	HRESULT InitVertexBuffer();
	HRESULT InitIndexBuffer();
	void initObjects();

	UINT _WindowHeight;
	UINT _WindowWidth;

public:
	Application();
	~Application();

	HRESULT Initialise(HINSTANCE hInstance, int nCmdShow);

	void Update(float deltaTime);
	void Draw();

	// Computes the avg time between frames and the FPS and displays it to the window bar
	// Also called in the main loop in main func.
	void CalculateFrameStats(float gameTime);
};

