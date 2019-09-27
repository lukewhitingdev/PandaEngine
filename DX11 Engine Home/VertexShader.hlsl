cbuffer MatrixBuffer {
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

struct VertexInput {
	float4 position : POSITION;
	float4 color : COLOR;
};

struct PixelInput {
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

// Vertex Shader

PixelInput ColorVertexShader(VertexInput input) {
	PixelInput output;

	// Change the position vector to be 4 units long to allow it to work with matrix's
	input.position.w = 1.0f;

	// Calculate the position of the vertex against the other matrix's
	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	// Store the input color for the pixel shader
	output.color = input.color;

	return output;
}