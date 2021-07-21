// ピクセルシェーダーの入力
struct PS_INPUT
{
	float4 spos			:	TEXCOORD0;		// 予備座標
	float3 vPosition	:	TEXCOORD1;		// 座標(ビュー空間)
	float3 norm			:	TEXCOORD2;		// 法線(ビュー空間)
	float4 dif			:	COLOR0;			// ディフューズカラー
};

// ピクセルシェーダーの出力
struct PS_OUTPUT
{
	float4 color0           : SV_TARGET0;	// 色
} ;

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
SamplerState	g_mirrorSampler	: register(s0);		// 反射テクスチャサンプラー
Texture2D		g_mirrorTexture	: register(t0);		// 反射テクスチャ

// main関数
PS_OUTPUT main( PS_INPUT PSInput)
{
	PS_OUTPUT PSOutput;
	float2 texCoords;
	float4 texColor;
	float refractiveRatio;

	// テクスチャ座標の算出
	texCoords.x = PSInput.spos.x / PSInput.spos.w;
	texCoords.y = PSInput.spos.y / PSInput.spos.w;

	// 鏡に映すテクスチャから色を取得
	texColor = g_mirrorTexture.Sample(g_mirrorSampler, texCoords);
	// ディフューズカラーと乗算して出力にセット
	PSOutput.color0 = texColor * PSInput.dif;

	// 水の屈折率 = 1.333    空気の屈折率 = 1.000293
	refractiveRatio = 1.001f / 1.000293f;

	// フレネル反射率計算( マルペケつくろーどっとコム様のフレネル反射解説から引用 )
	float A = refractiveRatio;
	float B = dot(-normalize(PSInput.vPosition), normalize(PSInput.norm));
	float C = sqrt(1.0f - A * A * (1 - B * B));
	//0以下になる場合があるっぽいので一応チェックして0以下なら補正する
	float Rs = (A * B - C) * (A * B - C) / ((A * B + C) * (A * B + C));
	float Rp = (A * C - B) * (A * C - B) / ((A * C + B) * (A * C + B));
	float alpha = (Rs + Rp) / 2.0f;
	alpha = min(alpha + 0.40f, 1.0f);
	// アルファ値をセット
	PSOutput.color0.a = alpha;

	return PSOutput;
}