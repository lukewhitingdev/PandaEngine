#include "renderer.h"
#include "Structures.h"

PandaEngine::renderer::renderer(window* window)
{
	_window = window;
	_pd3dDevice = nullptr;
	_pImmediateContext = nullptr;
	_pSwapChain = nullptr;
	_pRenderTargetView = nullptr;
	_defaultVertexShader = nullptr;
	_defaultPixelShader = nullptr;
	_defaultNoTexPixelShader = nullptr;
	_waveVertexShader = nullptr;
	_pVertexLayout = nullptr;
	_pVertexBuffer = nullptr;
	_pIndexBuffer = nullptr;
	_pConstantBuffer = nullptr;
	_depthStencilView = nullptr;
	_depthStencilBuffer = nullptr;
	_wireFrame = nullptr;
	_normalView = nullptr;
	_world = XMFLOAT4X4();
	_view = XMFLOAT4X4();
	_projection = XMFLOAT4X4();
	_driverType = D3D_DRIVER_TYPE();
	_featureLevel = D3D_FEATURE_LEVEL();
	textureResourceView = nullptr;
	textureSamplerState = nullptr;
	drawTextures = true;
	_cameraManager = nullptr;
	_gameTimer = nullptr;
	_lightingManager = nullptr;
	_objectManager = nullptr;
}

PandaEngine::renderer::~renderer()
{
	if (_pImmediateContext) _pImmediateContext->ClearState();

	if (_pConstantBuffer) _pConstantBuffer->Release();
	if (_pVertexBuffer) _pVertexBuffer->Release();
	if (_pIndexBuffer) _pIndexBuffer->Release();
	if (_pVertexLayout) _pVertexLayout->Release();
	if (_defaultVertexShader) _defaultVertexShader->Release();
	if (_defaultPixelShader) _defaultPixelShader->Release();
	if (_pRenderTargetView) _pRenderTargetView->Release();
	if (_pSwapChain) _pSwapChain->Release();
	if (_pImmediateContext) _pImmediateContext->Release();
	if (_pd3dDevice) _pd3dDevice->Release();
	if (_depthStencilView) _depthStencilView->Release();
	if (_depthStencilBuffer) _depthStencilBuffer->Release();
	if (_wireFrame) _wireFrame->Release();
	if (_normalView) _normalView->Release();
}

HRESULT PandaEngine::renderer::Initialise()
{
	HRESULT result;
	result = InitDevice();
	result = InitShadersAndInputLayout();
	return result;
}

HRESULT PandaEngine::renderer::CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
	HRESULT hr = S_OK;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined(DEBUG) || defined(_DEBUG)
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob* pErrorBlob;
	hr = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel,
		dwShaderFlags, 0, ppBlobOut, &pErrorBlob);

	if (FAILED(hr))
	{
		if (pErrorBlob != nullptr)
			OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());

		if (pErrorBlob) pErrorBlob->Release();

		return hr;
	}

	if (pErrorBlob) pErrorBlob->Release();

	return S_OK;
}

HRESULT PandaEngine::renderer::InitShadersAndInputLayout()
{
	HRESULT hr;

	// Compile the vertex shader
	ID3DBlob* pVSBlob = nullptr;
	hr = CompileShaderFromFile(L"Shader.fx", "VS", "vs_4_0", &pVSBlob);

	if (FAILED(hr))
	{
		MessageBox(nullptr,
			L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
		return hr;
	}

	// Create the vertex shader
	hr = _pd3dDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &_defaultVertexShader);

	if (FAILED(hr))
	{
		pVSBlob->Release();
		return hr;
	}

	// Compile the wave vertex shader
	ID3DBlob* pWaveVSBlob = nullptr;
	hr = CompileShaderFromFile(L"Shader.fx", "waveVS", "vs_4_0", &pWaveVSBlob);

	if (FAILED(hr))
	{
		MessageBox(nullptr,
			L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
		return hr;
	}

	// Create the vertex shader
	hr = _pd3dDevice->CreateVertexShader(pWaveVSBlob->GetBufferPointer(), pWaveVSBlob->GetBufferSize(), nullptr, &_waveVertexShader);

	if (FAILED(hr))
	{
		pWaveVSBlob->Release();
		return hr;
	}

	// Compile the pixel shader
	ID3DBlob* pPSBlob = nullptr;
	hr = CompileShaderFromFile(L"Shader.fx", "PS", "ps_4_0", &pPSBlob);

	if (FAILED(hr))
	{
		MessageBox(nullptr,
			L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
		return hr;
	}

	// Create the pixel shader
	hr = _pd3dDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &_defaultPixelShader);
	pPSBlob->Release();

	if (FAILED(hr))
		return hr;

	// Compile the pixel shader
	ID3DBlob* pnoTexPSBlob = nullptr;
	hr = CompileShaderFromFile(L"Shader.fx", "noTexPS", "ps_4_0", &pnoTexPSBlob);

	if (FAILED(hr))
	{
		MessageBox(nullptr,
			L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
		return hr;
	}

	// Create the pixel shader
	hr = _pd3dDevice->CreatePixelShader(pnoTexPSBlob->GetBufferPointer(), pnoTexPSBlob->GetBufferSize(), nullptr, &_defaultNoTexPixelShader);
	pnoTexPSBlob->Release();

	if (FAILED(hr))
		return hr;

	// Define the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	UINT numElements = ARRAYSIZE(layout);

	// Create the input layout
	hr = _pd3dDevice->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(),
		pVSBlob->GetBufferSize(), &_pVertexLayout);
	pVSBlob->Release();

	if (FAILED(hr))
		return hr;

	// Set the input layout
	_pImmediateContext->IASetInputLayout(_pVertexLayout);

	return hr;
}

HRESULT PandaEngine::renderer::InitDevice()
{
	HRESULT hr = S_OK;

	UINT createDeviceFlags = 0;

#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};

	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};

	UINT numFeatureLevels = ARRAYSIZE(featureLevels);
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = _window->getWindowWidth();
	sd.BufferDesc.Height = _window->getWindowHeight();
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = _window->gethWnd();
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	// Depth buffer setup
	D3D11_TEXTURE2D_DESC depthStencilDesc;
	depthStencilDesc.Width = _window->getWindowWidth();
	depthStencilDesc.Height = _window->getWindowHeight();
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	//Sample state setup
	D3D11_SAMPLER_DESC sampleDesc;
	ZeroMemory(&sampleDesc, sizeof(sampleDesc));
	sampleDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampleDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampleDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampleDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampleDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampleDesc.MinLOD = 0;
	sampleDesc.MaxLOD = D3D11_FLOAT32_MAX;



	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		_driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain(nullptr, _driverType, nullptr, createDeviceFlags, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &sd, &_pSwapChain, &_pd3dDevice, &_featureLevel, &_pImmediateContext);
		_pd3dDevice->CreateTexture2D(&depthStencilDesc, nullptr, &_depthStencilBuffer);
		if (_depthStencilBuffer != nullptr) {
			_pd3dDevice->CreateDepthStencilView(_depthStencilBuffer, nullptr, &_depthStencilView);
		}
		if (SUCCEEDED(hr))
			break;
	}

	if (FAILED(hr))
		return hr;

	// Create a render target view
	ID3D11Texture2D* _pBackBuffer = nullptr;
	hr = _pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&_pBackBuffer);

	if (FAILED(hr))
		return hr;

	hr = _pd3dDevice->CreateRenderTargetView(_pBackBuffer, nullptr, &_pRenderTargetView);
	_pBackBuffer->Release();

	if (FAILED(hr))
		return hr;


	_pImmediateContext->OMSetRenderTargets(1, &_pRenderTargetView, _depthStencilView);

	// Setup the viewport
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)_window->getWindowWidth();
	vp.Height = (FLOAT)_window->getWindowHeight();
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	_pImmediateContext->RSSetViewports(1, &vp);

	InitShadersAndInputLayout();

	// Set primitive topology
	_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Create the constant buffer
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstantBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	hr = _pd3dDevice->CreateBuffer(&bd, nullptr, &_pConstantBuffer);

	// RenderState setup
	// Wireframe
	D3D11_RASTERIZER_DESC RenderDesc;
	ZeroMemory(&RenderDesc, sizeof(D3D11_RASTERIZER_DESC));
	RenderDesc.FillMode = D3D11_FILL_WIREFRAME;
	RenderDesc.CullMode = D3D11_CULL_NONE;
	hr = _pd3dDevice->CreateRasterizerState(&RenderDesc, &_wireFrame);

	//Normal View
	ZeroMemory(&RenderDesc, sizeof(D3D11_RASTERIZER_DESC));
	RenderDesc.FillMode = D3D11_FILL_SOLID;
	RenderDesc.CullMode = D3D11_CULL_BACK;
	hr = _pd3dDevice->CreateRasterizerState(&RenderDesc, &_normalView);

	_pd3dDevice->CreateSamplerState(&sampleDesc, &textureSamplerState);

	if (FAILED(hr))
		return hr;

	return S_OK;
}

void PandaEngine::renderer::Draw()
{
	//
	// Clear the back buffer
	//
	float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red,green,blue,alpha
	_pImmediateContext->ClearRenderTargetView(_pRenderTargetView, ClearColor);
	_pImmediateContext->ClearDepthStencilView(_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	XMMATRIX world = XMMATRIX();
	XMMATRIX view = XMMATRIX();
	XMMATRIX projection = XMMATRIX();

	if (_cameraManager) {
		XMFLOAT4X4 camView = _cameraManager->getCurrentCamera()->getViewMatrix();
		XMFLOAT4X4 camProj = _cameraManager->getCurrentCamera()->getProjectionMatrix();
		world = XMLoadFloat4x4(&_world);
		view = XMLoadFloat4x4(&camView);
		projection = XMLoadFloat4x4(&camProj);
	}
	else {
		world = XMLoadFloat4x4(&_world);
	}
	//
	// Update variables
	//
	ConstantBuffer cb;
	cb.mWorld = XMMatrixTranspose(world);
	cb.mView = XMMatrixTranspose(view);
	cb.mProjection = XMMatrixTranspose(projection);

	_pImmediateContext->VSSetShader(_defaultVertexShader, nullptr, 0);
	_pImmediateContext->VSSetConstantBuffers(0, 1, &_pConstantBuffer);
	_pImmediateContext->PSSetConstantBuffers(0, 1, &_pConstantBuffer);
	_pImmediateContext->PSSetSamplers(0, 1, &textureSamplerState);
	_pImmediateContext->PSSetShaderResources(0, 1, &textureResourceView);
	_pImmediateContext->PSSetShader(_defaultPixelShader, nullptr, 0);


	// Game Timer
	if(_gameTimer)
		cb.gTime = _gameTimer->getGameTime();

	// Lighting
	if(_lightingManager)
		_lightingManager->Draw(_pImmediateContext, _pConstantBuffer, cb, _cameraManager->getCurrentCamera()->getCameraPos());

	// Objects
	if (_objectManager) {
		for (size_t i = 0; i < _objectManager->objectCount(); i++) {
			if (drawTextures) {
				if (_objectManager->getObjectAtIndex(i)->getMeshComponent()->getMeshType() != Mesh::meshType::WAVE) {
					_objectManager->getObjectAtIndex(i)->Draw(_pImmediateContext, _defaultPixelShader, _defaultVertexShader, _pConstantBuffer, cb);
				}
				else {
					_objectManager->getObjectAtIndex(i)->Draw(_pImmediateContext, _defaultPixelShader, _waveVertexShader, _pConstantBuffer, cb);
				}
			}
			else {
				if (_objectManager->getObjectAtIndex(i)->getMeshComponent()->getMeshType() != Mesh::meshType::WAVE) {
					_objectManager->getObjectAtIndex(i)->Draw(_pImmediateContext, _defaultNoTexPixelShader, _defaultVertexShader, _pConstantBuffer, cb);
				}
				else {
					_objectManager->getObjectAtIndex(i)->Draw(_pImmediateContext, _defaultNoTexPixelShader, _waveVertexShader, _pConstantBuffer, cb);
				}
			}
		}
	}

	// Rudementary input to be refactored.
	if (GetAsyncKeyState(VK_F1)) {
		_pImmediateContext->RSSetState(_wireFrame);
	}
	if (GetAsyncKeyState(VK_F2)) {
		_pImmediateContext->RSSetState(_normalView);
	}
	if (GetAsyncKeyState(VK_F7)) {
		drawTextures = true;
	}
	if (GetAsyncKeyState(VK_F8)) {
		drawTextures = false;
	}

	if (_UIManager)
		_UIManager->Draw();

	_pImmediateContext->UpdateSubresource(_pConstantBuffer, 0, nullptr, &cb, 0, 0);

	//
	// Present our back buffer to our front buffer
	//
	_pSwapChain->Present(0, 0);
}