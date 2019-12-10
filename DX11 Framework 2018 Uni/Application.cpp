#include "Application.h"
#include "DDSTextureLoader.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;

    switch (message)
    {
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            EndPaint(hWnd, &ps);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

Application::Application()
{
	_hInst = nullptr;
	_hWnd = nullptr;
	_driverType = D3D_DRIVER_TYPE_NULL;
	_featureLevel = D3D_FEATURE_LEVEL_11_0;
	_pd3dDevice = nullptr;
	_pImmediateContext = nullptr;
	_pSwapChain = nullptr;
	_pRenderTargetView = nullptr;
	_defaultVertexShader = nullptr;
	_defaultPixelShader = nullptr;
	_pVertexLayout = nullptr;
	_pVertexBuffer = nullptr;
	_pIndexBuffer = nullptr;
	_pConstantBuffer = nullptr;
	_WindowHeight = 0;
	_WindowWidth = 0;
	_depthStencilBuffer = nullptr;
	_depthStencilView = nullptr;
	_normalView = nullptr;
	_wireFrame = nullptr;
	textureResourceView = nullptr;
	camManager = nullptr;
	cubeMesh = nullptr;
	cubeMesh2 = nullptr;
	currentCameraNumber = 0;
	fileManager = nullptr;
	gTimer = nullptr;
	lightManager = nullptr;
	objMeshLoader = MeshData();
	shipMesh = nullptr;
	sphereMesh = nullptr;
	textureSamplerState = nullptr;
}

Application::~Application()
{
	Cleanup();
}

HRESULT Application::Initialise(HINSTANCE hInstance, int nCmdShow)
{
    if (FAILED(InitWindow(hInstance, nCmdShow)))
	{
        return E_FAIL;
	}

    RECT rc;
    GetClientRect(_hWnd, &rc);
    _WindowWidth = rc.right - rc.left;
    _WindowHeight = rc.bottom - rc.top;

    if (FAILED(InitDevice()))
    {
        Cleanup();

        return E_FAIL;
    }


	// Initialize the world matrix
	XMStoreFloat4x4(&_world, XMMatrixIdentity());
	
	InitTimer();
	InitObjects();
	InitCamera();
	InitLighting();

	return S_OK;
}

HRESULT Application::InitShadersAndInputLayout()
{
	HRESULT hr;

    // Compile the vertex shader
    ID3DBlob* pVSBlob = nullptr;
    hr = CompileShaderFromFile(L"DX11 Framework.fx", "VS", "vs_4_0", &pVSBlob);

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
	hr = CompileShaderFromFile(L"DX11 Framework.fx", "waveVS", "vs_4_0", &pWaveVSBlob);

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
    hr = CompileShaderFromFile(L"DX11 Framework.fx", "PS", "ps_4_0", &pPSBlob);

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

void Application::InitTimer()
{
	gTimer = new GameTimer();
	gTimer->ResetTimer();
	gTimer->CalculateFrameStats(_hWnd);
}

void Application::InitCamera()
{

	camManager = new cameraManager();

	// Initialize the view matrix
	XMFLOAT3 Eye = XMFLOAT3(0.0f, 0.0f, -3.0f);
	XMFLOAT3 At = XMFLOAT3(0.0f, 0.0f, 1.0f);
	XMFLOAT3 To = XMFLOAT3(0.0f, 0.0f, 1.0f);
	XMFLOAT3 Up = XMFLOAT3(0.0f, 1.0f, 0.0f);
	XMFLOAT3 Right = XMFLOAT3(1.0f, 0.0f, 0.0f);

	cameraVector.push_back(new debugCamera(Eye, To, Up, Right, (float)_WindowWidth, (float)_WindowHeight, 0.0f, 1000.0f));
	cameraVector[0]->UpdateStoredFloats();

	Eye = XMFLOAT3(0.0f, 2.0f, -3.0f);

	cameraVector.push_back(new staticCamera(Eye, At, (float)_WindowWidth, (float)_WindowHeight, 0.0f, 1000.0f));
	cameraVector[1]->UpdateStoredFloats();

	Eye = XMFLOAT3(0.0f, 20.0f, 1.0f);

	cameraVector.push_back(new staticGeneratedCamera(Eye, To, (float)_WindowWidth, (float)_WindowHeight, 0.0f, 1000.0f));
	cameraVector[2]->UpdateStoredFloats();


	Eye = XMFLOAT3(0.0f, 0.0f, 0.0f);
	To = XMFLOAT3(0.0f, 0.0f, -1.0f);

	cameraVector.push_back(new LookAtCam(Eye, At, Up, (float)_WindowWidth, (float)_WindowHeight, 0.0f, 1000.0f));
	cameraVector[3]->setAttachedMesh(shipMesh);
	cameraVector[3]->setAttachedOffset(XMFLOAT3(0, 2, 0));
	cameraVector[3]->setCameraPos(0, 0, 0);
	cameraVector[3]->UpdateStoredFloats();

	camManager->setDefaultCamera(cameraVector[0]);
	camManager->setCurrentCamera(cameraVector[0]);
}

void Application::InitObjects()
{

	fileManager = new saveToFileManager("Assets/ObjectPositions/MeshPos.txt");

	// Whether you would like to load from a file or not.
	fileManager->setLoadObjectsFromFile(false);

	cubeMesh = new cube(_pd3dDevice, L"Assets/Textures/Crate/Crate_COLOR.dds");
	cubeMesh2 = new cube(_pd3dDevice, L"Assets/Textures/Crate/Crate_NRM.dds");
	sphereMesh = new sphere(_pd3dDevice, L"Assets/Textures/Crate/Crate_COLOR.dds");
	shipMesh = new customModel(_pd3dDevice, L"Assets/Textures/Plane/Hercules_COLOR.dds", "Assets/Object Models/Custom/Boat.obj");

	meshVector.push_back(cubeMesh);
	meshVector.push_back(cubeMesh2);
	meshVector.push_back(sphereMesh);
	meshVector.push_back(shipMesh);

	// Generate Ocean
	for (int i = 0; i < 1; i++) {
		meshVector.push_back(new customModel(_pd3dDevice, "Assets/Object Models/Custom/Plane.obj", true, Mesh::meshType::WAVE));
	}

	if (fileManager->getLoadObjectsFromFile()) {

		// Get the loaded positions from the file.
		vector<XMFLOAT3> loadedPositions = fileManager->LoadPositionsFromFile();

		// Load all the positions currently saved, make sure that if some objects arent saved properly, then it will not overrun the vector.
		for (size_t i = 0; i < loadedPositions.size(); i++) {
			if (i < meshVector.size()) {
				meshVector[i]->setPosition(loadedPositions[i]);
				meshVector[i]->setScale(0.3f);
			}
		}

		// Loop through the rest of the mesh vector to reset all the new objects positions to 0 so they can be aligned within the program.
		if (meshVector.size() > loadedPositions.size()) {
			for(size_t i = loadedPositions.size(); i < meshVector.size(); i++){
				meshVector[i]->setPosition(XMFLOAT3(0, 0, 0));
			}
		}

	}
	else {
		// Use this to position objects and save them to the file for later.
		cubeMesh->setPosition(XMFLOAT3(-4.0f, 0.0f, 0.1f));
		cubeMesh->setScale(0.3f);

		cubeMesh2->setPosition(XMFLOAT3(4.0f, 0.0f, 0.1f));
		cubeMesh2->setScale(0.3f);

		sphereMesh->setPosition(XMFLOAT3(0.0f, 2.0f, 30.0f));
		sphereMesh->setScale(0.3f);

		shipMesh->setPosition(XMFLOAT3(0.0f, 0.0f, 20.0f));
		shipMesh->setScale(0.3f);

		meshVector[4]->setPosition(XMFLOAT3(0.0f, -0.8f, 5.0f));
		meshVector[4]->setScale(1.0f);
	}
}

void Application::InitLighting()
{
	lightManager = new lightingManager();
	lightManager->addLight(new directionalLight(camManager->getCurrentCamera()->getCameraPos()));
	lightManager->addLight(new pointLight(XMFLOAT3(0.5f, 1.0f, 0.1f), camManager->getCurrentCamera()->getCameraPos()));
	lightManager->addLight(new spotLight(XMFLOAT3(0.0f, 1.0f, 0.1f), XMFLOAT3(0.0f, -1.0f, -1.0f), camManager->getCurrentCamera()->getCameraPos()));
}


HRESULT Application::InitWindow(HINSTANCE hInstance, int nCmdShow)
{
    // Register class
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_TUTORIAL1);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW );
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = L"TutorialWindowClass";
    wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_TUTORIAL1);
    if (!RegisterClassEx(&wcex))
        return E_FAIL;

    // Create window
    _hInst = hInstance;
    RECT rc = {0, 0, 640, 480};
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
    _hWnd = CreateWindow(L"TutorialWindowClass", L"Engine", WS_OVERLAPPEDWINDOW,
                         CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance,
                         nullptr);
    if (!_hWnd)
		return E_FAIL;

    ShowWindow(_hWnd, nCmdShow);

    return S_OK;
}

HRESULT Application::CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
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

HRESULT Application::InitDevice()
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
    sd.BufferDesc.Width = _WindowWidth;
    sd.BufferDesc.Height = _WindowHeight;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = _hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;

	// Depth buffer setup
	D3D11_TEXTURE2D_DESC depthStencilDesc;
	depthStencilDesc.Width = _WindowWidth;
	depthStencilDesc.Height = _WindowHeight;
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
    ID3D11Texture2D* pBackBuffer = nullptr;
    hr = _pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

    if (FAILED(hr))
        return hr;

    hr = _pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &_pRenderTargetView);
    pBackBuffer->Release();

    if (FAILED(hr))
        return hr;


    _pImmediateContext->OMSetRenderTargets(1, &_pRenderTargetView, _depthStencilView);

    // Setup the viewport
    D3D11_VIEWPORT vp;
    vp.Width = (FLOAT)_WindowWidth;
    vp.Height = (FLOAT)_WindowHeight;
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

void Application::Cleanup()
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

void Application::Update()
{

	gTimer->Tick();

	gTimer->CalculateFrameStats(_hWnd);

	float t = gTimer->getGameTime();

	// TODO: Refactor
	// Camera Movement

	for (size_t i = 0; i < meshVector.size(); i++) {
		meshVector[i]->Update(gTimer->getGameTime());
	}

	shipMesh->UpdateMovement(t);

	if (camManager->getCurrentCamera()->getAttachedMesh() != nullptr) {
		camManager->getCurrentCamera()->setLookAtPos(camManager->getCurrentCamera()->getAttachedMesh()->getPosition().x, camManager->getCurrentCamera()->getAttachedMesh()->getPosition().y, camManager->getCurrentCamera()->getAttachedMesh()->getPosition().z);
		//camManager->getCurrentCamera()->UpdatePositionRelativeToMesh();
	}

	camManager->getCurrentCamera()->updateCameraMovement(cameraVector);

	if (GetAsyncKeyState('1')) {
		shipMesh->setObjectPossesionState(true);
		camManager->setCurrentCamera(cameraVector[1]); // Static Random
	}

	if (GetAsyncKeyState('2')) {
		shipMesh->setObjectPossesionState(true);
		camManager->setCurrentCamera(cameraVector[2]);
	}
	if (GetAsyncKeyState('3')) {
		shipMesh->setObjectPossesionState(true);
		camManager->setCurrentCamera(cameraVector[3]);
	}
	if (GetAsyncKeyState('0')) {
		// So we dont move objects whilst in debug
		for (size_t i = 0; i < meshVector.size(); i++) {
			meshVector[i]->setObjectPossesionState(false);
		}
		camManager->setCurrentCamera(cameraVector[0]); // Debug Camera
	}
}

void Application::Draw()
{
    //
    // Clear the back buffer
    //
    float ClearColor[4] = {0.0f, 0.125f, 0.3f, 1.0f}; // red,green,blue,alpha
    _pImmediateContext->ClearRenderTargetView(_pRenderTargetView, ClearColor);
	_pImmediateContext->ClearDepthStencilView(_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);


	XMFLOAT4X4 camView = camManager->getCurrentCamera()->getViewMatrix();
	XMFLOAT4X4 camProj = camManager->getCurrentCamera()->getProjectionMatrix();

	XMMATRIX world = XMLoadFloat4x4(&_world);
	XMMATRIX view = XMLoadFloat4x4(&camView);
	XMMATRIX projection = XMLoadFloat4x4(&camProj);
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

	cb.gTime = gTimer->getGameTime();
	_pImmediateContext->UpdateSubresource(_pConstantBuffer, 0, nullptr, &cb, 0, 0);

	// Lighting
	lightManager->Draw(_pImmediateContext, _pConstantBuffer, cb, camManager->getCurrentCamera()->getCameraPos());

	for (size_t i = 0; i < meshVector.size(); i++) {
		if (meshVector[i]->getMeshType() != Mesh::meshType::WAVE) {
			meshVector[i]->Draw(_pImmediateContext, _defaultPixelShader, _defaultVertexShader, _pConstantBuffer, cb);
		}
		else {
			meshVector[i]->Draw(_pImmediateContext, _defaultPixelShader, _waveVertexShader, _pConstantBuffer, cb);
		}
	}

	if (GetAsyncKeyState(VK_F1)) {
		_pImmediateContext->RSSetState(_wireFrame);
	}
	if (GetAsyncKeyState(VK_F2)) {
		_pImmediateContext->RSSetState(_normalView);
	}
	
    //
    // Present our back buffer to our front buffer
    //
    _pSwapChain->Present(0, 0);
}