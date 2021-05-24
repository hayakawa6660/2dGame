#include "Shader.h"
#include "Library/Components/PolygonSetComponent/PolygonSetComponent.h"
#include "Library/Common/commonObjects.h"
#include "../../ResourceManager/ResourceManager.h"
#include "Source/System/DebugManager/DebugManager.h"
#include "Source/System/CompressManager/CompressManager.h"

Shader::Shader(SceneBase * _scene) :
	GameObject(nullptr), m_mirrorNum(0), m_loadEnd(false),
	m_lightTarget(VGet(0, 0, 0))
{
	
	{
		CompressManager * c = CommonObjects::GetInstance()->FindGameObject<CompressManager>("CompressManager");
		c->UnCompress("data\\Shader.zip", "Shader");
	}
	//水面用ポリゴンのコンポーネントを生成
	m_polygon = GameObject::AddComponent<PolygonSetComponent>("PolygonSetComponent");
		//シェーダーのファイル場所を指定する
	// ライトの効果を受けず、ディフューズの色のみで判断するシェーダー(フォグ効果あり)
	m_shader[MESH_TYPE::NMESH_NO_LIGHTING_DIFFONLY_FOG].vertFile = "data\\Resource\\Shader\\NormalMesh_Nolighting_DiffOnly_Fog\\ShaderPolygon3DTestVS.vso";
	m_shader[MESH_TYPE::NMESH_NO_LIGHTING_DIFFONLY_FOG].pixlFile = "data\\Resource\\Shader\\NormalMesh_Nolighting_DiffOnly_Fog\\ShaderPolygon3DTestPS.pso";
	// ディフューズ、スぺキュラとノーマルマップ付き剛体メッシュ
	m_shader[MESH_TYPE::NMESH_DIFF_SPEC_NORM].vertFile = "data\\Resource\\Shader\\NormalMesh_NormalMap_Fog\\ShaderPolygon3DTestVS.vso";
	m_shader[MESH_TYPE::NMESH_DIFF_SPEC_NORM].pixlFile = "data\\Resource\\Shader\\NormalMesh_NormalMap_Fog\\ShaderPolygon3DTestPS.pso";
	// 剛体 : ディフューズ、スぺキュラとノーマルマップシェーダー(フォグ効果あり)、影付き
	m_shader[MESH_TYPE::NMESH_DIFF_SPEC_NORM_SHADOW].vertFile = "data\\Resource\\Shader\\NormalMesh_Shadow_Diff_Spec_Normal\\ShaderPolygon3DTestVS.vso";
	m_shader[MESH_TYPE::NMESH_DIFF_SPEC_NORM_SHADOW].pixlFile = "data\\Resource\\Shader\\NormalMesh_Shadow_Diff_Spec_Normal\\ShaderPolygon3DTestPS.pso";
	// 剛体 : ディフューズ、スぺキュラ付きトゥーンシェーダー
	m_shader[MESH_TYPE::NMESH_DIFF_SPEC_TOON].vertFile = "data\\Resource\\Shader\\NormalMesh_Diff_Spec_Toon\\ShaderPolygon3DTestVS.vso";
	m_shader[MESH_TYPE::NMESH_DIFF_SPEC_TOON].pixlFile = "data\\Resource\\Shader\\NormalMesh_Diff_Spec_Toon\\ShaderPolygon3DTestPS.pso";
	// 剛体 : 影シェーダーセットアップ用のノーマルマップ付きシェーダー
	m_shader[MESH_TYPE::NMESH_SHADOW_SETUP_NOT_NORMALMAP].vertFile = "data\\Resource\\Shader\\NormalMesh_ShadowSetUp_NotNormalMap\\ShaderPolygon3DTestVS.vso";
	m_shader[MESH_TYPE::NMESH_SHADOW_SETUP_NOT_NORMALMAP].pixlFile = "data\\Resource\\Shader\\NormalMesh_ShadowSetUp_NotNormalMap\\ShaderPolygon3DTestPS.pso";
	//ピクセルシェーダーは↑でやるため必要ないが、何か必要になるかもしれないので入れておく
	m_shader[MESH_TYPE::NMESH_SHADOW_SETUP_NORMALMAP].vertFile = "data\\Resource\\Shader\\NormalMesh_ShadowSetUp_NormalMap\\ShaderPolygon3DTestVS.vso";
	m_shader[MESH_TYPE::NMESH_SHADOW_SETUP_NORMALMAP].pixlFile = "data\\Resource\\Shader\\NormalMesh_ShadowSetUp_NormalMap\\ShaderPolygon3DTestPS.pso";
	
	// フレネル反射(水)シェーダー
	m_shader[MESH_TYPE::WATER].vertFile = "data\\Resource\\Shader\\FresnelReflection\\ShaderPolygon3DTestVS.vso";
	m_shader[MESH_TYPE::WATER].pixlFile = "data\\Resource\\Shader\\FresnelReflection\\ShaderPolygon3DTestPS.pso";

	ResourceManager *p = CommonObjects::GetInstance()->FindGameObject<ResourceManager>("SystemResource");
	for (auto & it : m_shader)
	{
		//ファイル指定した場所を一括ロード
		p->ShaderLoad(it.second.vertFile, true);
		p->ShaderLoad(it.second.pixlFile, false);
	}
	//トゥーンテクスチャの読み込み
	m_toonTexture.fileName = "data\\Texture\\Shader\\GradTex_2Color.png";
	//m_toonTexture.fileName = "data\\texture\\Shader\\GradTex.png";
	p->TextureLoad(m_toonTexture.fileName);

	//影シェーダー変数の初期化
	SetDrawValidFloatTypeGraphCreateFlag(TRUE);
	SetCreateDrawValidGraphChannelNum(1);
	SetCreateGraphColorBitDepth(16);
	//m_deptHandle = MakeScreen(1024, 1024, FALSE);
	//m_deptHandle = MakeScreen(2048, 2048, FALSE);
	m_deptHandle = MakeScreen(4096, 4096, FALSE);
	SetDrawValidFloatTypeGraphCreateFlag(FALSE);
	SetCreateDrawValidGraphChannelNum(4);
	SetCreateGraphColorBitDepth(32);

	m_cbufferVS = CreateShaderConstantBuffer(sizeof(LIGHT_MATRIX));
	m_cbufferPS = CreateShaderConstantBuffer(sizeof(FLOAT4));
	m_shadowCorrection = 0.08f;

	//深度画像取得時のカメラ設定変数
	m_othroParam = 39.9f;
	m_offsetParam = 64.8f;
	m_farParam = 100.f;

}

Shader::~Shader()
{
	//ハンドルはリソースマネージャーで自動デリートされるのでリストの初期化だけをする。
	m_shader.clear();
	m_polygon = nullptr;
}

void Shader::Update()
{
	if (!m_loadEnd)
	{
		ResourceManager *p = CommonObjects::GetInstance()->FindGameObject<ResourceManager>("SystemResource");
		for (auto &it : m_shader)
		{
			//頂点シェーダーの読み込み
			if (it.second.vertex < 0)
			{
				if (!p->CheckHandle(it.second.vertFile))	//このファイルのロードが終わっているか確認
					return;
				//終わっていたらハンドルを入れる
				it.second.vertex = p->GetHandle(it.second.vertFile);
			}
			//ピクセルシェーダーの読み込み
			if (it.second.pixcel < 0)
			{
				if (!p->CheckHandle(it.second.pixlFile))	//このファイルのロードが終わっているか確認
					return;
				//終わっていたらハンドルを入れる
				it.second.pixcel = p->GetHandle(it.second.pixlFile);
			}
		}
		if (m_toonTexture.handle < 0)
		{
			if (!p->CheckHandle(m_toonTexture.fileName))	//このファイルのロードが終わっているか確認
				return;
			//終わっていたらハンドルを入れる
			m_toonTexture.handle = p->GetHandle(m_toonTexture.fileName);
		}
		//ロードが全て終わっているのが確認できたら次からチェックしない
		m_loadEnd = true;
	}

	Debug::DebugPrintf(200, 500, "SystemShader", "Far : %f", m_farParam);
	Debug::DebugPrintf(200, 520, "SystemShader", "Off : %f", m_offsetParam);
	Debug::DebugPrintf(200, 540, "SystemShader", "Oth : %f", m_othroParam);
	Debug::DebugPrintf(200, 560, "SystemShader", "Test : %f", m_shadowCorrection);

}

void Shader::CBufferUpdate()
{
	//頂点シェーダーに値の書き込み
	//シェーダー側でfloat4x4を設定しているので、こちらでMATRIX二つを内包したLIGHT_MATRIXに変換する
	LIGHT_MATRIX * p = reinterpret_cast<LIGHT_MATRIX*>(GetBufferShaderConstantBuffer(m_cbufferVS));
	p->projection = m_lightMat.projection;
	p->view = m_lightMat.view;
	UpdateShaderConstantBuffer(m_cbufferVS);
	SetShaderConstantBuffer(m_cbufferVS, DX_SHADERTYPE_VERTEX, 4);
	//ピクセルシェーダーに値の書き込み
	if (CheckHitKey(KEY_INPUT_Z))
		m_shadowCorrection += 0.01f;
	if (CheckHitKey(KEY_INPUT_X))
		m_shadowCorrection -= 0.01f;
	//DrawFormatString(600, 60, 0xffffff, "test    : %f", test);	//デバック数値表示
	FLOAT4* f = (FLOAT4 *)GetBufferShaderConstantBuffer(m_cbufferPS);
	f->x = m_shadowCorrection;
	f->y = 0.f;
	f->z = 0.f;
	f->w = 1.f;
	UpdateShaderConstantBuffer(m_cbufferPS);
	SetShaderConstantBuffer(m_cbufferPS, DX_SHADERTYPE_PIXEL, 4);
}

void Shader::SetUpMirror(int _mirrorNum, VECTOR & _cPosition, VECTOR & _cTarget)
{
	SetDrawScreen(m_mirror[_mirrorNum].handle);
	ClearDrawScreen();

	float EyeLength, TargetLength;
	VECTOR MirrorNormal;
	VECTOR *MirrorWorldPosP;
	VECTOR MirrorCameraEyePos, MirrorCameraTargetPos;
	std::array<VECTOR, 4> temp = m_polygon->GetSqarePolygon(_mirrorNum);
	m_mirror[_mirrorNum].Position[0] = temp[0];
	m_mirror[_mirrorNum].Position[1] = temp[1];
	m_mirror[_mirrorNum].Position[2] = temp[2];
	m_mirror[_mirrorNum].Position[3] = temp[3];

	MirrorWorldPosP = m_mirror[_mirrorNum].Position;

	// 鏡の面の法線を算出
	MirrorNormal = VNorm(VCross(VSub(MirrorWorldPosP[1], MirrorWorldPosP[0]), VSub(MirrorWorldPosP[2], MirrorWorldPosP[0])));

	// 鏡の面からカメラの座標までの最短距離、鏡の面からカメラの注視点までの最短距離を算出
	EyeLength = Plane_Point_MinLength(MirrorWorldPosP[0], MirrorNormal, _cPosition);
	TargetLength = Plane_Point_MinLength(MirrorWorldPosP[0], MirrorNormal, _cTarget);

	// 鏡に映る映像を描画する際に使用するカメラの座標とカメラの注視点を算出
	MirrorCameraEyePos = VAdd(_cPosition, VScale(MirrorNormal, -EyeLength * 2.0f));
	MirrorCameraTargetPos = VAdd(_cTarget, VScale(MirrorNormal, -TargetLength * 2.0f));

	// 計算で得られたカメラの座標とカメラの注視点の座標をカメラの設定する
	SetCameraPositionAndTarget_UpVecY(MirrorCameraEyePos, MirrorCameraTargetPos);
	SetCameraNearFar(0.01f, 3000.f);
	// 鏡に映る映像の中での鏡の四隅の座標を算出( 同次座標 )
	for (int i = 0; i < 4; i++)
	{
		//VECTOR pos = ConvWorldPosToViewPos(MirrorWorldPosP[i]);
		m_mirror[_mirrorNum].ScreenPosition[i] = ConvWorldPosToScreenPosPlusW(MirrorWorldPosP[i]);
	}
}

void Shader::MirrorRender(int _mirrorNum)
{
	VERTEX3DSHADER Vert[6];
	VECTOR MirrorNormal;

	// 鏡の面の法線を算出
	MirrorNormal = VNorm(VCross(VSub(m_mirror[_mirrorNum].Position[1], m_mirror[_mirrorNum].Position[0]), VSub(m_mirror[_mirrorNum].Position[2], m_mirror[_mirrorNum].Position[0])));

	// 鏡の描画に使用する頂点のセットアップ
	for (int i = 0; i < 4; i++)
	{
		// 座標をセット
		Vert[i].pos = m_mirror[_mirrorNum].Position[i];

		// 法泉をセット
		Vert[i].norm = MirrorNormal;

		// Diffuse Color をセット
		Vert[i].dif = m_mirror[_mirrorNum].diffuse;

		// 補助座標に鏡に映る視点での射影座標を代入する
		Vert[i].spos.x = m_mirror[_mirrorNum].ScreenPosition[i].x / 1024.f;
		Vert[i].spos.y = m_mirror[_mirrorNum].ScreenPosition[i].y / 512.f;
		Vert[i].spos.z = m_mirror[_mirrorNum].ScreenPosition[i].z;
		Vert[i].spos.w = m_mirror[_mirrorNum].ScreenPosition[i].w;
	}
	Vert[4] = Vert[2];
	Vert[5] = Vert[1];

	// 描画モードをバイリニアフィルタリングに設定
	SetDrawMode(DX_DRAWMODE_BILINEAR);

	// 描画ブレンドモードをセット
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	//// 描画にＺバッファを使用する
	SetUseZBuffer3D(TRUE);

	//// Ｚバッファに書き込みを行う
	SetWriteZBuffer3D(TRUE);

	// 使用する頂点シェーダーをセット
	SetUseVertexShader(m_shader[MESH_TYPE::WATER].vertex);

	// 使用するピクセルシェーダーをセット
	SetUsePixelShader(m_shader[MESH_TYPE::WATER].pixcel);

	// 使用するテクスチャをセット
	SetUseTextureToShader(0, m_mirror[_mirrorNum].handle);

	// フレネル反射の鏡を描画
	DrawPolygon3DToShader(Vert, 2);

	//使用したテクスチャのパスを解除
	SetUseTextureToShader(0, -1);

	//// Ｚバッファに書き込みを行う設定を元に戻す
	SetWriteZBuffer3D(FALSE);

	//// Ｚバッファを使用する設定を元に戻す
	SetUseZBuffer3D(FALSE);

	// 描画ブレンドモードを元に戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	// 描画モードを元に戻す
	SetDrawMode(DX_DRAWMODE_NEAREST);
}

void Shader::MirrorSet(VECTOR & _position, float _radiusX, float _radiusY)
{
	m_polygon->SqareSet(_position, _radiusX, _radiusY);

	m_mirrorNum++;
	Mirror state;
	state.diffuse = { 255, 255, 0, 255 };
	state.handle = MakeScreen(1024, 512, FALSE);

	m_mirror.emplace_back(state);
}

void Shader::SetMeshTypeShader(MESH_TYPE _type)
{
	switch (_type)
	{
	case MESH_TYPE::NO_SHADER:
		MV1SetUseOrigShader(FALSE);
		SetUseTextureToShader(3, -1);	//トゥーンが設定されていた時の解除
		SetUseTextureToShader(4, -1);	//影テクスチャが設定されていた時の解除
		break;
	case MESH_TYPE::NMESH_DIFF_SPEC_TOON:
		MV1SetUseOrigShader(TRUE);
		SetUseTextureToShader(3, m_toonTexture.handle);

		SetUseVertexShader(m_shader[_type].vertex);
		SetUsePixelShader(m_shader[_type].pixcel);
		break;
	case MESH_TYPE::NMESH_SHADOW_SETUP_NOT_NORMALMAP:
		MV1SetUseOrigShader(TRUE);
		SetUseVertexShader(m_shader[_type].vertex);
		break;
	case MESH_TYPE::NMESH_SHADOW_SETUP_NORMALMAP:
		MV1SetUseOrigShader(TRUE);
		SetUseVertexShader(m_shader[_type].vertex);
		break;
	case MESH_TYPE::NMESH_DIFF_SPEC_NORM_SHADOW:
		MV1SetUseOrigShader(TRUE);
		SetUsePixelShader(m_shader[_type].pixcel);
		CBufferUpdate();
		//深度画像をピクセルシェーダーにセット
		SetUseTextureToShader(4, m_deptHandle);
		SetUseVertexShader(m_shader[_type].vertex);

		break;
	default:	//その他特に設定する必要のないシェーダー
		MV1SetUseOrigShader(TRUE);
		SetUseVertexShader(m_shader[_type].vertex);
		SetUsePixelShader(m_shader[_type].pixcel);
		break;
	}
}

void Shader::SetShadowSetUpShader(bool _start)
{
	if (_start)
	{
		SetDrawScreen(m_deptHandle);
		SetBackgroundColor(255, 255, 255);
		ClearDrawScreen();
		SetBackgroundColor(0, 0, 0);
		//カメラの設定をキーボードで設定
		if (CheckHitKey(KEY_INPUT_Q))
			m_othroParam += 0.1f;
		else if (CheckHitKey(KEY_INPUT_A))
			m_othroParam -= 0.1f;
		if (CheckHitKey(KEY_INPUT_W))
			m_offsetParam += 0.1f;
		else if (CheckHitKey(KEY_INPUT_S))
			m_offsetParam -= 0.1f;

		if (CheckHitKey(KEY_INPUT_E))
			m_farParam += 0.1f;
		else if (CheckHitKey(KEY_INPUT_D))
			m_farParam -= 0.1f;
		// カメラをライトの向きに指定し、場所は手動で設定した値にする(後々固定値にする)
		SetupCamera_Ortho(m_othroParam);
		SetCameraNearFar(0.1f, m_farParam);
		VECTOR lightDir = GetLightDirection();
		//VECTOR lightTag = VGet(0.f, 0.f, 0.f);
		VECTOR lightPos = VAdd(m_lightTarget, VScale(lightDir, (-m_offsetParam)));
		SetCameraPositionAndTarget_UpVecY(lightPos, m_lightTarget);
		m_lightMat.view = GetCameraViewMatrix();
		m_lightMat.projection = GetCameraProjectionMatrix();

		MV1SetUseOrigShader(TRUE);
		SetUsePixelShader(m_shader[MESH_TYPE::NMESH_SHADOW_SETUP_NOT_NORMALMAP].pixcel);
	}
	else
	{
		MV1SetUseOrigShader(FALSE);
		SetDrawScreen(DX_SCREEN_BACK);
	}
}