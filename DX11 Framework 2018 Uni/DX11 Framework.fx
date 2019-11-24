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
    float4 AmbientLight; // 16
    float4 DiffuseLight; // 16
    float4 SpecularLight; // 16

    // Packed together
    float3 LightVecW; // 12
    float SpecularPower; // 4


};

struct Material
{
    float4 mSpecular;
    float4 mAmbient;
    float4 mDiffuse;
};

cbuffer ConstantBuffer : register( b0 )
{
	matrix World;
	matrix View;
	matrix Projection;

    DirectionLight dirLight;

    Material globalMaterial;

    float4 EyePosW;
    
}

//--------------------------------------------------------------------------------------------------------------
// Helper Functions
//--------------------------------------------------------------------------------------------------------------

void ComputeDirectionalLightPS(Material inputMat, DirectionLight dirLight, float3 normalW, float3 toEye,
                               out float4 ambient, out float4 diffuse, out float4 specular)
{

    // Initialise outputs
    ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
    diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
    specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

    // Get the diffuse ammount
    float diffuseAmmount = max(dot(dirLight.LightVecW, normalW), 0.0f);

    //Compute Reflection Color from the normal of the vertex
    float3 ref = reflect(-dirLight.LightVecW, normalW);

    float specularAmmount = pow(max(dot(ref, toEye), 0.0f), dirLight.SpecularPower);

    // Multiply the ambient material by the ammount of ambient light the directional light emmits
    ambient = inputMat.mAmbient * dirLight.AmbientLight;
    // Avoid wierd bugs
    if (diffuseAmmount > 0.0f)
    {
        diffuse = diffuseAmmount * inputMat.mDiffuse * dirLight.DiffuseLight;

        specular = specularAmmount * inputMat.mSpecular * dirLight.SpecularLight;
    }
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

    float3 toEye = normalize(EyePosW.xyz - input.Pos.xyz);

    float4 ambient;
    float4 diffuse;
    float4 specular;

    ComputeDirectionalLightPS(globalMaterial, dirLight, input.Norm, toEye, 
                              ambient, diffuse, specular);



    input.Color.rgb = textureColor.rgb * (ambient.xyz + diffuse.xyz) + specular.xyz;
	input.Color.a = globalMaterial.mDiffuse.a;

    return input.Color;
}


