//--------------------------------------------------------------------------------------
// File: DX11 Framework.fx
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
cbuffer ConstantBuffer : register( b0 )
{
	matrix World;
	matrix View;
	matrix Projection;

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
}

//--------------------------------------------------------------------------------------
struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR0;
};

//--------------------------------------------------------------------------------------
// Vertex Shader -- Gouraud Shading using Diffuse Lighting only
//--------------------------------------------------------------------------------------
VS_OUTPUT VS( float4 Pos : POSITION, float3 NormalL : NORMAL )
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	output.Pos = mul(Pos, World);

	float3 toEye = normalize(EyePosW - output.Pos.xyz);

    output.Pos = mul( output.Pos, View );
    output.Pos = mul( output.Pos, Projection );

	// Convert from local space to world space
	// W Component of vector is 0 as vectors cannot be translated cuz they are vectors
	float3 normalW = mul(float4(NormalL, 0.0f), World).xyz;
	normalW = normalize(normalW);

	//Compute Reflection Color
	float3 r = reflect(-LightVecW, normalW);

	float specularAmmount = pow(max(dot(r, toEye), 0.0f), SpecularPower);

	//Compute new color with diffuse lighting enabled
	float diffuseAmmount = max(dot(LightVecW, normalW), 0.0f);

	float3 ambient = AmbientMaterial * AmbientLight;

	float3 specular = specularAmmount * (SpecularMtrl * SpecularLight).rgb;

	output.Color.rbg = diffuseAmmount + ambient + specular;
	output.Color.a = DiffuseMtrl.a;

    return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS( VS_OUTPUT input ) : SV_Target
{
    return input.Color;
}
