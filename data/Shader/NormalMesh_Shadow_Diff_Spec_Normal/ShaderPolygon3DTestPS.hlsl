// ピクセルシェーダーの入力
struct PS_INPUT
{
	float2 texCoords0	:	TEXCOORD0;		// テクスチャ座標
	float3 vPosition	:	TEXCOORD1;		// 座標( ビュー空間 )
	float3 tan			:	TEXCOORD2;		// 接線(ビュー空間)
	float3 binorm		:	TEXCOORD3;		// 従法線(ビュー空間)
	float3 norm			:	TEXCOORD4;		// 法線(ビュー空間)
	float4 spos			:	TEXCOORD5;		// 予備座標
	float  fog : TEXCOORD6;
	float4 diffuse		:	COLOR0;			// ディフューズカラー
	float4 specular		:	COLOR1;			// スぺキュラカラー
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

cbuffer DEPTH_CONST				: register(b4)
{
	float4 test;
};
//Texture
SamplerState g_diffuseMapSampler	: register(s0);		// ディフューズマップテクスチャ
Texture2D    g_diffuseMapTexture	: register(t0);		// ディフューズマップテクスチャ
SamplerState g_normalMapSampler		: register(s1);		// 法線マップテクスチャ
Texture2D    g_normalMapTexture		: register(t1);		// 法線マップテクスチャ
SamplerState g_specularMapSampler	: register(s2);		// スぺキュラマップテクスチャ
Texture2D    g_specularMapTexture	: register(t2);		// スぺキュラマップテクスチャ
//SamplerState g_toonMapSampler		: register(s3);		// トゥーンマップテクスチャ
//Texture2D    g_toonMapTexture		: register(t3);		// トゥーンマップテクスチャ
SamplerState g_shadowMapSampler		: register(s4);		// トゥーンマップテクスチャ
Texture2D    g_shadowMapTexture		: register(t4);		// トゥーンマップテクスチャ


// main関数
PS_OUTPUT main(PS_INPUT PSInput)
{
	PS_OUTPUT PSOutput;
	// 接線・従法線・法線を正規化
	float3 VNrm = normalize(PSInput.norm);
	float3 VTan = normalize(PSInput.tan);
	float3 VBin = normalize(PSInput.binorm);
	// 頂点座標から視点へのベクトルを接底空間に投影した後正規化して保存
	float3 TempF3;
	TempF3.x = dot(VTan, -PSInput.vPosition.xyz);
	TempF3.y = dot(VBin, -PSInput.vPosition.xyz);
	TempF3.z = dot(VNrm, -PSInput.vPosition.xyz);
	float3 V_to_Eye = normalize(TempF3);
	// 法線の 0～1 の値を -1.0～1.0 に変換する
	float3 Normal = (g_normalMapTexture.Sample(g_normalMapSampler, PSInput.texCoords0.xy) - float3(0.5f, 0.5f, 0.5f)) * 2.0f;
	// ディフューズカラーとスペキュラカラーの蓄積値を初期化
	float3 TotalDiffuse = float3(0.0f, 0.0f, 0.0f);
	float3 TotalSpecular = float3(0.0f, 0.0f, 0.0f);

	// ディレクショナルライトの処理 +++++++++++++++++++++++++++++++++++++++++++++++++++++( 開始 )
	// ライト方向ベクトルの計算
	TempF3 = g_common.light[0].direction;
	// ライトのベクトルを接地空間に変換
	float3 lLightDir;
	lLightDir.x = dot(VTan, TempF3);
	lLightDir.y = dot(VBin, TempF3);
	lLightDir.z = dot(VNrm, TempF3);
	// DiffuseAngleGen = ディフューズ角度減衰率計算(減衰無し)
	float DiffuseAngleGen = saturate(dot(Normal, -lLightDir));
	// ディフューズカラー蓄積値 += ライトのディフューズカラー * マテリアルのディフューズカラー * ディフューズカラー角度減衰率 + ライトのアンビエントカラーとマテリアルのアンビエントカラーを乗算したもの 
	TotalDiffuse += g_common.light[0].diffuse * g_common.material.diffuse.xyz * DiffuseAngleGen + g_common.light[0].ambient;
	// スペキュラカラー計算
	// ハーフベクトルの計算
	TempF3 = normalize(V_to_Eye - lLightDir);
	// Temp = pow( max( 0.0f, N * H ), g_Common.Material.Power )
	float4 Temp = pow(max(0.0f, dot(Normal, TempF3)), g_common.material.power);
	float3 TextureSpecular = g_specularMapTexture.Sample(g_specularMapSampler, PSInput.texCoords0);
	// スペキュラカラー蓄積値 += Temp * ライトのスペキュラカラー
	TotalSpecular += Temp * g_common.light[0].specular * TextureSpecular;
	// ディレクショナルライトの処理 +++++++++++++++++++++++++++++++++++++++++++++++++++++( 終了 )

	// 出力カラー計算 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++( 開始 )
	// TotalDiffuse = ライトディフューズカラー蓄積値 + ( マテリアルのアンビエントカラーとグローバルアンビエントカラーを乗算したものとマテリアルエミッシブカラーを加算したもの )
	TotalDiffuse += g_common.material.ambient_Emissive.xyz;
	// SpecularColor = ライトのスペキュラカラー蓄積値 * マテリアルのスペキュラカラー
	float3 SpecularColor = TotalSpecular * g_common.material.specular.xyz;
	// 出力カラー = TotalDiffuse * テクスチャカラー + SpecularColor
	float4 TextureDiffuseColor = g_diffuseMapTexture.Sample(g_diffuseMapSampler, PSInput.texCoords0);

	float4 outColor;
	outColor.rgb = TextureDiffuseColor.rgb * TotalDiffuse + SpecularColor;
	// フォグ効果
	outColor.rgb = lerp(g_common.fog.color.rgb, outColor.rgb, saturate(PSInput.fog));
	// アルファ値 = テクスチャアルファ * マテリアルのディフューズアルファ * 不透明度
	outColor.a = TextureDiffuseColor.a * g_common.material.diffuse.a * g_base.factorColor.a;

	float2 DepthTexCoord;
	DepthTexCoord.x = (PSInput.spos.x + 1.0f) / 2.0f;
	DepthTexCoord.y = 1.0f - (PSInput.spos.y + 1.0f) / 2.0f;

	float DepthTexture = g_shadowMapTexture.Sample(g_shadowMapSampler, DepthTexCoord);
	if (PSInput.spos.z > DepthTexture + test.r)
	{
		outColor.rgb *= 0.8f;
	}

	PSOutput.color0 = outColor;

	//PSOutput.color0 = PSInput.spos;
	// 出力カラー計算 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++( 終了 )
	return PSOutput;
}