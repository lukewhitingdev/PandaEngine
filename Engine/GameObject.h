#pragma once
#include "Mesh.h"

class GameObject
{

public:
	
	// Used to update the GameObject and its components.
	void Update(float deltaTime);

	// Used to draw the GameObject's mesh and other visual components.
	void Draw(ID3D11DeviceContext* context, ID3D11PixelShader* pixelShader, ID3D11VertexShader* vertexShader, ID3D11Buffer* constantBuffer, ConstantBuffer& cb);

	// Used to change or in the current GameObject's mesh.
	void changeMesh(Mesh mesh) { _mesh = &mesh; };					

private:
	Mesh* _mesh = nullptr;								// Handles Appearance and Mesh generation.


};

