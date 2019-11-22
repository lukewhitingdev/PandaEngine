//--------------------------------------------------------------------------------------
// File: DX11 Framework.fx
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------

Texture2D txDiffuse : register(t0);
SamplerState samLinear : register(s0);

struct DirectionLight
{
    float4 DiffuseMtrl;
    float4 DiffuseLight;
    float3 LightVecW;
    float time;

    float4 AmbientLight;
    float4 AmbientMaterial;

    float4 SpecularMtrl;
    float4 SpecularLight;
    float SpecularPower;
    float4 EyePosW;
};

cbuffer ConstantBuffer : register( b0 )
{
	matrix World;
	matrix View;
	matrix Projection;

    DirectionLight dirLight;
    
}

//--------------------------------------------------------------------------------------
struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR0;
	float3 Norm : NORMAL;
	float3 PosW : POSITION;
	float2 Tex : TEXCOORD0;
};

//--------------------------------------------------------------------------------------
// Vertex Shader -- Gouraud Shading using Diffuse Lighting only
//--------------------------------------------------------------------------------------
VS_OUTPUT VS( float4 Pos : POSITION, float3 NormalL : NORMAL, float2 Tex : TEXCOORD)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	output.Pos = mul(Pos, World);
    output.Pos = mul(output.Pos, View);
    output.Pos = mul(output.Pos, Projection);

	// Convert from local space to world space
	// W Component of vector is 0 as vectors cannot be translated cuz they are vectors
	float3 normalW = mul(float4(NormalL, 0.0f), World).xyz;
	normalW = normalize(normalW);
	output.Norm = normalW;

	// just pass the texture from the input to the pixel shader.
	output.Tex = Tex;

    return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(VS_OUTPUT input) : SV_Target
{

	float4 textureColor = txDiffuse.Sample(samLinear, input.Tex);

    

    float3 toEye = normalize(dirLight.EyePosW - input.Pos.xyz);

	//Compute Reflection Color from the normal of the vertex
	float3 r = reflect(-dirLight.LightVecW, input.Norm);

    // Compute the specular ammount using the dot product of the reflection and the eye
    // if its close to 1 then higher specular since your looking straight at it
    float specularAmmount = pow(max(dot(r, toEye), 0.0f), dirLight.SpecularPower);

	//Compute new color with diffuse lighting enabled
    // Computes the shade with regard to the incoming light direction and nothing else
    float diffuseAmmount = max(dot(dirLight.LightVecW, input.Norm), 0.0f);

	float3 ambient = dirLight.AmbientMaterial * dirLight.AmbientLight;

	float3 specular = specularAmmount * (dirLight.SpecularMtrl * dirLight.SpecularLight).rgb;

	input.Color.rgb = textureColor * (ambient + diffuseAmmount) + specular;
	input.Color.a = dirLight.DiffuseMtrl.a;

    return input.Color;
}
