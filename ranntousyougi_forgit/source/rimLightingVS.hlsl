//バーテクスシェーダ
#include"common.hlsl"

void main(in VS_IN In, out PS_IN Out)
{

	matrix wvp;
	wvp = mul(World, View);
	wvp = mul(wvp, Projection);
	Out.Position = mul(In.Position, wvp);

	float4 worldNormal, normal;
	normal = float4(In.Normal.xyz, 0.0f);
	worldNormal = mul(normal, World);//法線をワールド変換
	worldNormal = normalize(worldNormal);//正規化する
	
	Out.Normal = worldNormal;

	Out.Diffuse = In.Diffuse;
	
	Out.TexCoord = In.TexCoord;
	
	Out.WorldPosition = mul(In.Position, World);

}

