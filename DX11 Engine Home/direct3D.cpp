#include "direct3D.h"



direct3D::direct3D()
{
	m_swapChain = 0;
	m_Device = 0;
	m_deviceContext = 0;
	m_renderTargetView = 0;
	m_depthStencilBuffer = 0;
	m_depthStencilState = 0;
	m_depthStencilView = 0;
	m_rasterState = 0;
}


direct3D::~direct3D()
{
}

bool direct3D::Init(int wWidth, int wHeight, bool vsync, HWND hwnd, bool fScreen, float sDepth, float sNear)
{
	HRESULT hResult;
	IDXGIFactory* factory;
	IDXGIAdapter* adapter;
	IDXGIOutput* adapterOutput;
	unsigned int numModes;
	unsigned int i;
	unsigned int numerator;
	unsigned int denominator;
	unsigned int stringLength;
	DXGI_MODE_DESC* displayModeList;
	DXGI_ADAPTER_DESC adapterDesc;
	int error;
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	D3D_FEATURE_LEVEL featureLevel;
	ID3D11Texture2D* backBufferPtr;
	D3D11_TEXTURE2D_DESC depthBufferDesc;
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	D3D11_RASTERIZER_DESC rasterDesc;
	D3D11_VIEWPORT Viewport;
	float fieldOfView, screenAspect;

	// Set the local vSync setting
	m_Vsync_enabled = vsync;

	// Generate the DirectX Graphics Factory
	if (FAILED(CreateDXGIFactory(_uuidof(IDXGIFactory), (void**)&factory))) {
		return false;
	}

	// Using the factory to create a adapter for the video card
	if (FAILED(factory->EnumAdapters(0, &adapter))) {
		return false;
	}

	// Add primary monitor to adapter enum
	if (FAILED(adapter->EnumOutputs(0, &adapterOutput))) {
		return false;
	}

	// Get number of modes that fit the DXGI display format (below) for the adapter to output to 
	// Format: DXGI_FORMAT_R8G8B8A8_UNORM
	if(FAILED(adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL))) {
		return false;
	}

	// Create a object to hold the list of display modes the current monitor / video card combination can support
	displayModeList = new DXGI_MODE_DESC[numModes];
	if (!displayModeList) {
		return false;
	}

	// populating the list with adapterOutput display mode info
	if (FAILED(adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList))) {
		return false;
	}

	// Find the display mode on the GPU/Display that fits the current resolution set in the program 
	for (int i = 0; i < numModes; i++) {
		if (displayModeList[i].Width == (unsigned int)wWidth) {
			if (displayModeList[i].Height == (unsigned int)wHeight) {
				numerator = displayModeList[i].RefreshRate.Numerator;
				denominator = displayModeList[i].RefreshRate.Denominator;
			}
		}
	}

	// Get the adapter desc
	if (FAILED(adapter->GetDesc(&adapterDesc))) {
		return false;
	}

	// Store the GPU memory in megabytes
	m_videoCardMemory = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);

	// Convert the name of the video card to a char array and save it
	if (wcstombs_s(&stringLength, m_videoCardDescription, 128, adapterDesc.Description, 128) != 0) {
		return false;
	}

	// Release all GPU related objects since we have gotten everything useful from them

	// Release the displayModeList
	delete[] displayModeList;
	displayModeList = 0;

	// Release the adapterOutput
	adapterOutput->Release();
	adapterOutput = 0;

	// Release the adapter
	adapter->Release();
	adapter = 0;

	// Release the factory
	factory->Release();
	factory = 0;

	// Initalise the swapChain description
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	// Set ammount of back buffers
	swapChainDesc.BufferCount = 1;

	// Set the width and height of the back buffer
	swapChainDesc.BufferDesc.Width = wWidth;
	swapChainDesc.BufferDesc.Height = wHeight;

	// Set 32-Bit surface for the back buffer
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// Set refresh rate
	if (m_Vsync_enabled) {
		swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;
	}
	else {
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	}

	// Set the back buffer usage
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	// give it the handle to the window
	swapChainDesc.OutputWindow = hwnd;

	// Turn multisampling off
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	// Get if in fullscreen or not
	if (fScreen) {
		swapChainDesc.Windowed = false;
	}
	else {
		swapChainDesc.Windowed = true;
	}

	// Set scan line ordering and scaling
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// Reset the back buffer after swapping
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	// Dont set advanced flags
	swapChainDesc.Flags = 0;

	// What version of directX we are using
	featureLevel = D3D_FEATURE_LEVEL_11_0;

	// Create the swapChain, Direct3D Device and Direct3D device context
	// Check if DirectX 11 capable GPU is present
	if (FAILED(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, &featureLevel, 1, D3D11_SDK_VERSION, &swapChainDesc, &m_swapChain, &m_Device, NULL, &m_deviceContext))) {
		// If no DirectX 11 Capable GPU is present use CPU instead
		MessageBox(hwnd, L"No capable DirectX 11 GPU Detected, switching to CPU!", L"Notice", MB_OK);
		if (FAILED(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_REFERENCE, NULL, 0, &featureLevel, 1, D3D11_SDK_VERSION, &swapChainDesc, &m_swapChain, &m_Device, NULL, &m_deviceContext))) {
			return false;
		}
	}

	// Get Pointer to back buffer
	if (FAILED(m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferPtr))) {
		return false;
	}
	if (FAILED(m_Device->CreateRenderTargetView(backBufferPtr, NULL, &m_renderTargetView))) {
		return false;
	}

	// Relase the backbuffer pointer
	backBufferPtr->Release();
	backBufferPtr = 0;

	//Initalize the depth buffer desc
	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

	//Setup depth buffer desc
	depthBufferDesc.Width = wWidth;
	depthBufferDesc.Height = wHeight;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	// Create texture for the depth buffer using the desc
	if (FAILED(m_Device->CreateTexture2D(&depthBufferDesc, NULL, &m_depthStencilBuffer))) {
		return false;
	}

	// Initialise the description of the stencil buffer
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

	//Setup stencil buffer desc
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	// Stencil operations if pixel is front-facing.
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing.
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Create the depth stencil state
	if (FAILED(m_Device->CreateDepthStencilState(&depthStencilDesc, &m_depthStencilState))) {
		return false;
	}

	// Set stencil state
	m_deviceContext->OMSetDepthStencilState(m_depthStencilState, 1);

	//Initalize the depth stencil view
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

	// Set up the depth stencil view description.
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	// Create the stencil depth view
	if (FAILED(m_Device->CreateDepthStencilView(m_depthStencilBuffer, &depthStencilViewDesc, &m_depthStencilView))) {
		return false;
	}

	// Bind the render target view and depth stencil to the output render pipeline
	m_deviceContext->OMGetRenderTargets(1, &m_renderTargetView, &m_depthStencilView);

	// Setup the raster desc /// Controls how the polygons are drawn, wireframe etc
	rasterDesc.AntialiasedLineEnable = false;
	rasterDesc.CullMode = D3D11_CULL_BACK;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;

	// Create the rasterizer state from the desc
	if (FAILED(m_Device->CreateRasterizerState(&rasterDesc, &m_rasterState))){
		return false;
	}

	// Set the rasterizer state
	m_deviceContext->RSSetState(m_rasterState);

	// Viewport setup
	Viewport.Width = (float)wWidth;
	Viewport.Height = (float)wHeight;
	Viewport.MinDepth = 0.0f;
	Viewport.MaxDepth = 1.0f;
	Viewport.TopLeftX = 0.0f;
	Viewport.TopLeftY = 0.0f;

	// Create the viewport
	m_deviceContext->RSSetViewports(1, &Viewport);

	// Projection matrix setup
	fieldOfView = ((float)XM_PI / 4.0f);
	screenAspect = ((float)wWidth / (float)wHeight);

	// Create the projection matrix, enabling 3D rendering
	XMStoreFloat4x4(&m_projectionMatrix, XMMatrixPerspectiveFovLH(fieldOfView, screenAspect, sNear, sDepth));

	// Init world matrix
	XMStoreFloat4x4(&m_worldMatrix, XMMatrixIdentity());

	//TODO: init view matrix

	//Create ortho matrix for 2D rendering
	XMStoreFloat4x4(&m_orthoMatrix, XMMatrixOrthographicLH((float)wWidth, (float)wHeight, sNear, sDepth));

	return true;
}

void direct3D::Shutdown()
{
	// Before shutdown switch to windowed mode to avoid exceptions
	if (m_swapChain)
	{
		m_swapChain->SetFullscreenState(false, NULL);
	}


	// Cleanup all pointers

	if (m_rasterState)
	{
		m_rasterState->Release();
		m_rasterState = 0;
	}

	if (m_depthStencilView)
	{
		m_depthStencilView->Release();
		m_depthStencilView = 0;
	}

	if (m_depthStencilState)
	{
		m_depthStencilState->Release();
		m_depthStencilState = 0;
	}

	if (m_depthStencilBuffer)
	{
		m_depthStencilBuffer->Release();
		m_depthStencilBuffer = 0;
	}

	if (m_renderTargetView)
	{
		m_renderTargetView->Release();
		m_renderTargetView = 0;
	}

	if (m_deviceContext)
	{
		m_deviceContext->Release();
		m_deviceContext = 0;
	}

	if (m_Device)
	{
		m_Device->Release();
		m_Device = 0;
	}

	if (m_swapChain)
	{
		m_swapChain->Release();
		m_swapChain = 0;
	}

	return;
}

void direct3D::BeginScene(float red, float green, float blue, float alpha)
{
	float color[4];

	// setup empty buffer colors.
	color[0] = red;
	color[1] = green;
	color[2] = blue;
	color[3] = alpha;

	// Clear the back buffer
	m_deviceContext->ClearRenderTargetView(m_renderTargetView, color);

	// Clear the depth buffer
	m_deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	return;
}

void direct3D::EndScene()
{
	// Present back buffer to screen
	if (m_Vsync_enabled) {
		// Lock refresh rate
		m_swapChain->Present(1, 0);
	}
	else {
		// dont lock refresh rate
		m_swapChain->Present(0, 0);
	}
	return;
}

ID3D11Device * direct3D::GetDevice()
{
	return m_Device;
}

ID3D11DeviceContext * direct3D::GetDeviceContext()
{
	return m_deviceContext;
}

void direct3D::GetProjectionMatrix(XMFLOAT4X4& ProjectionMatrix)
{
	ProjectionMatrix = m_projectionMatrix;
	return;
}

void direct3D::GetWorldMatrix(XMFLOAT4X4& WorldMatrix)
{
	WorldMatrix = m_worldMatrix;
	return;
}

void direct3D::GetOrthoMatrix(XMFLOAT4X4& OrthoMatrix)
{
	OrthoMatrix = m_orthoMatrix;
	return;
}

void direct3D::GetVideoCardInfo(char * name, int & memory)
{
	strcpy_s(name, 128, m_videoCardDescription);
	memory = m_videoCardMemory;
	return;
}
