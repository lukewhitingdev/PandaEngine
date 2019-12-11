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

struct PointLight
{
    float4 AmbientLight; // 16
    float4 DiffuseLight; // 16
    float4 SpecularLight; // 16

    // Packed together
    float3 LightPos; // 12
    float LightRange; // 4

    // Packet together
    float3 Attenuation; // 12
    float pad; // 4

};

struct SpotLight
{
    float4 AmbientLight; // 16
    float4 DiffuseLight; // 16
    float4 SpecularLight; // 16

    // Packed together
    float3 LightPos; // 12
    float LightRange; // 4

    // Packed Together
    float3 lightDirection; // 12
    float spotPower; // 4

    // Packet together
    float3 Attenuation; // 12
    float pad; // 4
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

    PointLight pointLight;

    SpotLight spotLight;

    Material globalMaterial;

    float3 EyePosW;
	float gTime;
   
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

void ComputePointLightPS(Material inputMat, PointLight pointLight, float3 normalW, float3 pos, float3 toEye,
                               out float4 ambient, out float4 diffuse, out float4 specular)
{

    // Initialise outputs
    ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
    diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
    specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

    // Vector from world / object to light 
    float3 lightVector = pointLight.LightPos - pos;

    // Distance from world / object
    float distance = length(lightVector);

    // Make sure we arent out of range
    if (distance > pointLight.LightRange)
    {
        return;
    }

    // Normalize the light vector
    lightVector /= distance;

    // Calculate the diffuse ammount
    float diffuseAmmount = dot(lightVector, normalW);

    //Compute Reflection Color from the normal of the vertex
    float3 ref = reflect(-lightVector, normalW);

    float specularAmmount = pow(max(dot(ref, toEye), 0.0f), globalMaterial.mSpecular.w);

    ambient = globalMaterial.mAmbient * pointLight.AmbientLight;

     // Avoid wierd bugs
    if (diffuseAmmount > 0.0f)
    {
        diffuse = diffuseAmmount * inputMat.mDiffuse * pointLight.DiffuseLight;

        specular = specularAmmount * inputMat.mSpecular * pointLight.SpecularLight;
    }

    // Attenuation

    float attenuation = 1.0f / dot(pointLight.Attenuation, float3(1.0f, distance, distance * distance));

    diffuse *= attenuation;
    specular *= attenuation;
}

void ComputeSpotLightPS(Material inputMat, SpotLight spotLight, float3 normalW, float3 pos, float3 toEye,
                               out float4 ambient, out float4 diffuse, out float4 specular)
{
    // Initialise outputs
    ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
    diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
    specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

    // Vector from world / object to light 
    float3 lightVector = spotLight.LightPos - pos;

    // Distance from world / object
    float distance = length(lightVector);

    // Make sure we arent out of range
    if (distance > spotLight.LightRange)
    {
        return;
    }

    // Normalize the light vector
    lightVector /= distance;

    // Calculate the diffuse ammount
    float diffuseAmmount = dot(lightVector, normalW);

    //Compute Reflection Color from the normal of the vertex
    float3 ref = reflect(-lightVector, normalW);

    float specularAmmount = pow(max(dot(ref, toEye), 0.0f), globalMaterial.mSpecular.w);

    ambient = globalMaterial.mAmbient * spotLight.AmbientLight;

     // Avoid wierd bugs
    if (diffuseAmmount > 0.0f)
    {
        diffuse = diffuseAmmount * inputMat.mDiffuse * spotLight.DiffuseLight;

        specular = specularAmmount * inputMat.mSpecular * spotLight.SpecularLight;
    }

    // Scale spotlight by the spotlight power 
    float spot = pow(max(dot(-lightVector, spotLight.lightDirection), 0.0f), spotLight.spotPower);

    // Attenuate byt the increased spotlight power
    float attenuation = spot / dot(spotLight.Attenuation, float3(1.0f, distance, distance * distance));

    diffuse *= attenuation;
    specular *= attenuation;

}

void computeWaves(float waveLength, float steepness, float4 inputPos, float3 inputNorm,
								out float4 outputPos, out float3 outputNorm)
{
	
	float4 Pos = inputPos;
	
	float2 waveDir = { 1.0f, 1.0f };
	
	// Compute Wavelength  (k)
	float WaveLength = 2 * 3.14 / waveLength;
	
	// Calculate phase speed (c)
	float phaseSpeed = sqrt(9.8 / WaveLength);
	
	// Make the amplitude relative to the steepness to allow manipulation.
	float amplitude = steepness / WaveLength;
	
	// Normalize the waveDirection (d)
	float2 direction = normalize(waveDir);
	
	// Make the wavey ness (f)
	float wave = WaveLength * (dot(direction, Pos.xz) - phaseSpeed * gTime);

	// Compute xy
	Pos.x += amplitude * cos(wave);
	Pos.y = amplitude * sin(wave);
	
	// Compute normals
	float3 tangent = float3(1 - direction.x * direction.x * (steepness * sin(wave)),
							direction.x * (steepness * cos(wave)),
							-direction.x * direction.y * (steepness * sin(wave)));
	float3 binormal = float3(-direction.x * direction.y * (steepness * sin(wave)),
							direction.y * (steepness * cos(wave)),
							1 - direction.y * direction.y * (steepness * sin(wave)));
	
	float3 normal = normalize(cross(binormal, tangent));
	
	
	// Output
	outputPos = Pos;
	outputNorm = normal;

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
	VS_OUTPUT output = (VS_OUTPUT) 0;
	
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

VS_OUTPUT waveVS(float4 Pos : POSITION, float3 NormalL : NORMAL, float2 Tex : TEXCOORD)
{
    VS_OUTPUT output = (VS_OUTPUT) 0;
    
    computeWaves(5, 0.1,
				Pos, NormalL
				,Pos, NormalL);
	
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

    float4 ambientSum = float4(0.0f, 0.0f, 0.0f, 0.0f);
    float4 diffuseSum = float4(0.0f, 0.0f, 0.0f, 0.0f);
    float4 specularSum = float4(0.0f, 0.0f, 0.0f, 0.0f);

	if (dirLight.AmbientLight.x >= 0.0f) {
		ComputeDirectionalLightPS(globalMaterial, dirLight, input.Norm, toEye,
			ambient, diffuse, specular);

		ambientSum += ambient;
		diffuseSum += diffuse;
		specularSum += specular;


	}

	if (pointLight.AmbientLight.x >= 0.0f) {
		ComputePointLightPS(globalMaterial, pointLight, input.Norm, input.PosW, toEye,
			ambient, diffuse, specular);

		ambientSum += ambient;
		diffuseSum += diffuse;
		specularSum += specular;
	}

	if (spotLight.AmbientLight.x >= 0.0f) {
		ComputeSpotLightPS(globalMaterial, spotLight, input.Norm, input.PosW, toEye,
			ambient, diffuse, specular);

		ambientSum += ambient;
		diffuseSum += diffuse;
		specularSum += specular;
	}

    input.Color.rgb = textureColor.rgb * (ambientSum.xyz + diffuseSum.xyz) + specularSum.xyz;
	input.Color.a = globalMaterial.mDiffuse.a;

    return input.Color;
}


