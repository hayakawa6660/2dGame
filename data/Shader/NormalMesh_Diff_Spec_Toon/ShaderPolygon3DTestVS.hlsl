// 頂点シェーダーの入力
struct VS_INPUT
{
	float3 pos				: POSITION;		// 座標( ローカル空間 )
	float3 norm				: NORMAL;		// 法線( ローカル空間 )
	float4 diffuse			: COLOR0;		// ディフューズカラー
	float4 specular			: COLOR1;		// スペキュラカラー
	float4 texCoords0		: TEXCOORD0;	// テクスチャ座標
	float4 texCoords1		: TEXCOORD1;	// サブテクスチャ座標
};

// 頂点シェーダーの出力
struct VS_OUTPUT
{
	float2 texCoords0	:	TEXCOORD0;		// テクスチャ座標
	float3 vPosition	:	TEXCOORD1;		// 座標(ビュー空間)
	float3 norm			:	TEXCOORD2;		// 法線(ビュー空間)
	float4 pos			:	SV_POSITION;	// 座標(プロジェクション空間)
	//float4 spos			:	TEXCOORD3;		// 予備座標
};

// 基本パラメータ
struct DX_D3D11_VS_CONST_BUFFER_BASE
{
	float4		antiViewportMatrix[4];		// アンチビューポート行列
	float4		projectionMatrix[4];		// ビュー　→　プロジェクション行列
	float4		viewMatrix[3];				// ワールド　→　ビュー行列
	float4		localWorldMatrix[3];		// ローカル　→　ワールド行列

	float4		toonOutLineSize;			// トゥーンの輪郭線の大きさ
	float		DdiffuseSource;				// ディフューズカラー( 0.0f:マテリアル  1.0f:頂点 )
	float		specularSource;				// スペキュラカラー(   0.0f:マテリアル  1.0f:頂点 )
	float		mulSpecularColor;			// スペキュラカラー値に乗算する値( スペキュラ無効処理で使用 )
	float		padding;
};

// その他の行列
struct DX_D3D11_VS_CONST_BUFFER_OTHERMATRIX
{
	float4		shadowMapLightViewProjectionMatrix[3][4];			// シャドウマップ用のライトビュー行列とライト射影行列を乗算したもの
	float4		textureMatrix[3][2];								// テクスチャ座標操作用行列
};

// 基本パラメータ
cbuffer cbD3D11_CONST_BUFFER_VS_BASE			: register(b1)
{
	DX_D3D11_VS_CONST_BUFFER_BASE				g_base;
};

// その他の行列
cbuffer cbD3D11_CONST_BUFFER_VS_OTHERMATRIX		: register(b2)
{
	DX_D3D11_VS_CONST_BUFFER_OTHERMATRIX		g_otherMatrix;
};



// main関数
VS_OUTPUT main(VS_INPUT VSInput)
{
	VS_OUTPUT VSOutput;


	// 頂点座標変換 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++( 開始 )

	// ローカル座標のセット
	float4 localPosition;
	localPosition.xyz = VSInput.pos ;
	localPosition.w = 1.0f ;

	// 座標計算( ローカル→ビュー→プロジェクション )
	float4 worldPosition;
	worldPosition.x = dot(localPosition, g_base.localWorldMatrix[0]);
	worldPosition.y = dot(localPosition, g_base.localWorldMatrix[1]);
	worldPosition.z = dot(localPosition, g_base.localWorldMatrix[2]);
	worldPosition.w = 1.0f;
	float4 viewPosition;
	viewPosition.x = dot(worldPosition, g_base.viewMatrix[0]);
	viewPosition.y = dot(worldPosition, g_base.viewMatrix[1]);
	viewPosition.z = dot(worldPosition, g_base.viewMatrix[2]);
	viewPosition.w = 1.0f;

	VSOutput.pos.x = dot(viewPosition, g_base.projectionMatrix[0]) ;
	VSOutput.pos.y = dot(viewPosition, g_base.projectionMatrix[1]) ;
	VSOutput.pos.z = dot(viewPosition, g_base.projectionMatrix[2]) ;
	VSOutput.pos.w = dot(viewPosition, g_base.projectionMatrix[3]) ;

	// 頂点座標変換 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++( 終了 )

	// 法線をビュー空間の角度に変換 =====================================================( 開始 )

	// 法線をビューベクトルに変換
	float3 worldNrm;
	worldNrm.x = dot(VSInput.norm, g_base.localWorldMatrix[0].xyz);
	worldNrm.y = dot(VSInput.norm, g_base.localWorldMatrix[1].xyz);
	worldNrm.z = dot(VSInput.norm, g_base.localWorldMatrix[2].xyz);
	float3 viewNrm;
	viewNrm.x = dot(worldNrm, g_base.viewMatrix[0].xyz);
	viewNrm.y = dot(worldNrm, g_base.viewMatrix[1].xyz);
	viewNrm.z = dot(worldNrm, g_base.viewMatrix[2].xyz);

	// 法線をビュー空間の角度に変換 =====================================================( 終了 )


	// 出力パラメータセット ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++( 開始 )

		// テクスチャ座標変換行列による変換を行った結果のテクスチャ座標をセット
	VSOutput.texCoords0.x = dot(VSInput.texCoords0, g_otherMatrix.textureMatrix[0][0]);
	VSOutput.texCoords0.y = dot(VSInput.texCoords0, g_otherMatrix.textureMatrix[0][1]);

	// 頂点座標を保存
	VSOutput.vPosition = viewPosition.xyz;
	// 法線を保存
	VSOutput.norm = viewNrm;

	// 出力パラメータセット ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++( 終了 )


	// 出力パラメータを返す
	return VSOutput ;
}