//�����v�Z�̃s�N�Z���V�F�[�_�[

#include"common.hlsl"

//�e�N�X�`���摜
Texture2D g_Texture : register(t0);//�e�N�X�`����0��
SamplerState g_SamplerState : register(s0);//�T���v���[��0��

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	float4 normal = normalize(In.Normal);

	float3 eyeVec = In.WorldPosition.xyz - CameraPosition.xyz;
	eyeVec = normalize(eyeVec);

	float3 halfv = eyeVec + Light.Direction.xyz;
	halfv = normalize(halfv);


	float rimLight =- dot(eyeVec, normal.xyz);
	rimLight = pow(rimLight, 3) * 2;
	rimLight = saturate(rimLight);


	outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
	outDiffuse.rgb -= rimLight;

	outDiffuse.a = 1.0;



	
}