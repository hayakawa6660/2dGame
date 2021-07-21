// ピクセルシェーダーの入力
struct PS_INPUT
{
	float4 texCoords0	:	TEXCOORD0;		// テクスチャ座標
	float3 vPosition	:	TEXCOORD1;		// 座標( ビュー空間 )
	float3 norm			:	TEXCOORD2;		// 法線(ビュー空間)
	//float  fog			:	TEXCOORD3;
};

// ピクセルシェーダーの出力
struct PS_OUTPUT
{
	float4 color0           : SV_TARGET0;	// 色
};

// マテリアルパラメータ
struct DX_D3D11_CONST_MATERIAL
{
	float4		diffuse;				// ディフューズカラー
	float4		specular;				// スペキュラカラー
	float4		ambient_Emissive;		// マテリアルエミッシブカラー + マテリアルアンビエントカラー * グローバルアンビエントカラー

	float		power;					// スペキュラの強さ
	float		typeParam0;			// マテリアルタイプパラメータ0
	float		typeParam1;			// マテリアルタイプパラメータ1
	float		typeParam2;			// マテリアルタイプパラメータ2
};

// フォグパラメータ
struct DX_D3D11_VS_CONST_FOG
{
	float		linearAdd;				// フォグ用パラメータ end / ( end - start )
	float		linearDiv;				// フォグ用パラメータ -1  / ( end - start )
	float		density;				// フォグ用パラメータ density
	float		e;						// フォグ用パラメータ 自然対数の低

	float4		color;					// カラー
};

// ライトパラメータ
struct DX_D3D11_CONST_LIGHT
{
	int			type;					// ライトタイプ( DX_LIGHTTYPE_POINT など )
	int3		padding1;				// パディング１

	float3		position;				// 座標( ビュー空間 )
	float		rangePow2;				// 有効距離の２乗

	float3		direction;				// 方向( ビュー空間 )
	float		fallOff;				// スポットライト用FallOff

	float3		diffuse;				// ディフューズカラー
	float		spotParam0;			// スポットライト用パラメータ０( cos( Phi / 2.0f ) )

	float3		specular;				// スペキュラカラー
	float		spotParam1;			// スポットライト用パラメータ１( 1.0f / ( cos( Theta / 2.0f ) - cos( Phi / 2.0f ) ) )

	float4		ambient;				// アンビエントカラーとマテリアルのアンビエントカラーを乗算したもの

	float		attenuation0;			// 距離による減衰処理用パラメータ０
	float		attenuation1;			// 距離による減衰処理用パラメータ１
	float		attenuation2;			// 距離による減衰処理用パラメータ２
	float		padding2;				// パディング２
};

// ピクセルシェーダー・頂点シェーダー共通パラメータ
struct DX_D3D11_CONST_BUFFER_COMMON
{
	DX_D3D11_CONST_LIGHT		light[6];			// ライトパラメータ
	DX_D3D11_CONST_MATERIAL		material;				// マテリアルパラメータ
	DX_D3D11_VS_CONST_FOG		fog;					// フォグパラメータ
};

// 定数バッファピクセルシェーダー基本パラメータ
struct DX_D3D11_PS_CONST_BUFFER_BASE
{
	float4		factorColor;			// アルファ値等

	float		mulAlphaColor;			// カラーにアルファ値を乗算するかどうか( 0.0f:乗算しない  1.0f:乗算する )
	float		alphaTestRef;			// アルファテストで使用する比較値
	float2		padding1;

	int			alphaTestCmpMode;		// アルファテスト比較モード( DX_CMP_NEVER など )
	int3		padding2;

	float4		ignoreTextureColor;	// テクスチャカラー無視処理用カラー
};

// 頂点シェーダー・ピクセルシェーダー共通パラメータ
cbuffer cbD3D11_CONST_BUFFER_COMMON					: register(b0)
{
	DX_D3D11_CONST_BUFFER_COMMON		g_common;
};

// 基本パラメータ
cbuffer cbD3D11_CONST_BUFFER_PS_BASE				: register(b1)
{
	DX_D3D11_PS_CONST_BUFFER_BASE		g_base;
};

//Texture
SamplerState g_diffuseMapSampler	: register(s0);		// ディフューズマップテクスチャ
Texture2D    g_diffuseMapTexture	: register(t0);		// ディフューズマップテクスチャ

// main関数
PS_OUTPUT main(PS_INPUT PSInput)
{
	PS_OUTPUT PSOutput;
	float3 nrm = normalize(PSInput.norm);
	float3 v_to_eye = normalize(-PSInput.vPosition);

	float3 totalDiff = float3(0.f, 0.f, 0.f);
	float3 totalSpec = float3(0.f, 0.f, 0.f);
	float3 lightDir = g_common.light[0].direction;

	float diffAngleGen = saturate(dot(nrm, -lightDir));
	totalDiff += g_common.light[0].diffuse * g_common.material.diffuse.xyz * diffAngleGen + g_common.light[0].ambient.xyz;

	float3 temp = normalize(v_to_eye - lightDir);
	float temp2 = pow(max(0.0f, dot(nrm, temp)), g_common.material.power);
	totalSpec += temp2 * g_common.light[0].specular;

	// TotalDiffuse = ライトディフューズカラー蓄積値 + ( マテリアルのアンビエントカラーとグローバルアンビエントカラーを乗算したものとマテリアルエミッシブカラーを加算したもの )
	totalDiff += g_common.material.ambient_Emissive.xyz;
	// SpecularColor = ライトのスペキュラカラー蓄積値 * マテリアルのスペキュラカラー
	float3 specColor = totalSpec * g_common.material.specular.xyz;
	// 出力カラー = TotalDiffuse * テクスチャカラー + SpecularColor
	float4 texDiff = g_diffuseMapTexture.Sample(g_diffuseMapSampler, PSInput.texCoords0);
	PSOutput.color0.rgb = texDiff.rgb * totalDiff + specColor;
	// フォグ効果
	//PSOutput.color0.rgb = lerp(g_common.fog.color.rgb, PSOutput.color0.rgb, saturate(PSInput.fog));

	// アルファ値 = テクスチャアルファ * マテリアルのディフューズアルファ * 不透明度
	PSOutput.color0.a = texDiff.a * g_common.material.diffuse.a * g_base.factorColor.a;

	return PSOutput;
}