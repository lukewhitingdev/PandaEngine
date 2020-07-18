#pragma once
#include <windows.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include "window.h"
#include "cameraManager.h"
#include "lightingManager.h"
#include "objectManager.h"
#include "GameTimer.h"

namespace PandaEngine {
	class renderer
	{
	private:
		ID3D11Device*			_pd3dDevice;
		ID3D11DeviceContext*	_pImmediateContext;
		IDXGISwapChain*			_pSwapChain;
		ID3D11RenderTargetView* _pRenderTargetView;
		ID3D11VertexShader*		_defaultVertexShader;
		ID3D11PixelShader*		_defaultPixelShader;
		ID3D11PixelShader*		_defaultNoTexPixelShader;
		ID3D11VertexShader*		_waveVertexShader;
		ID3D11InputLayout*		_pVertexLayout;
		ID3D11Buffer*			_pVertexBuffer;
		ID3D11Buffer*			_pIndexBuffer;
		ID3D11Buffer*			_pConstantBuffer;
		ID3D11DepthStencilView* _depthStencilView;
		ID3D11Texture2D*		_depthStencilBuffer;
		ID3D11RasterizerState*	_wireFrame;
		ID3D11RasterizerState*	_normalView;
		DirectX::XMFLOAT4X4		_world;
		DirectX::XMFLOAT4X4		_view;
		DirectX::XMFLOAT4X4		_projection;
		D3D_DRIVER_TYPE         _driverType;
		D3D_FEATURE_LEVEL       _featureLevel;

		bool drawTextures;

		// Set specific components
		window*				_window;
		objectManager*		_objectManager;
		lightingManager*	_lightingManager;
		cameraManager*		_cameraManager;
		GameTimer*			_gameTimer;

		ID3D11ShaderResourceView* textureResourceView;
		ID3D11SamplerState* textureSamplerState;

		HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
		HRESULT InitShadersAndInputLayout();
		HRESULT InitDevice();
	public:
		renderer(window* window);
		~renderer();

		void addObjectManager(objectManager* manager) { _objectManager = manager; _objectManager->setDevice(_pd3dDevice); };
		void addLightingManager(lightingManager* manager) { _lightingManager = manager; };
		void addCameraManager(cameraManager* manager) { _cameraManager = manager; };
		void addGameTimer(GameTimer* timer) { _gameTimer = timer; };

		HRESULT Initialise();
		void Draw();
	};
}

