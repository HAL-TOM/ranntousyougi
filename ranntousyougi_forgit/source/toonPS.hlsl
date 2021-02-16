//光源計算のピクセルシェーダー

#include"common.hlsl"

//テクスチャ画像
Texture2D g_Texture : register(t0);//テクスチャの0番
SamplerState g_SamplerState : register(s0);//サンプラーの0番

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	float4 normal = normalize(In.Normal);

	float3 eyeVec = In.WorldPosition.xyz - CameraPosition.xyz;
	eyeVec = normalize(eyeVec);


	float3 halfv = eyeVec + Light.Direction.xyz;
	halfv = normalize(halfv);




	outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
	outDiffuse.a = In.Diffuse.a;

	float light = 0.5 - dot(normal.xyz, Light.Direction.xyz)*0.5;

	float specular2 = -dot(halfv, normal.xyz);
	specular2 = saturate(specular2);

	float lightdate = specular2;

	if (0.98 < specular2)
	{
		lightdate = 1.0;
	}
	else if (0.2 < specular2)
	{
		lightdate = -0.1;

	}
	else if (0.02 < specular2)
	{
		lightdate = -0.4;

	}
	else
	{
		lightdate = -0.4;

	}
	outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);

	
	outDiffuse.rgb += lightdate;
	outDiffuse.a = 1.0;



	
}