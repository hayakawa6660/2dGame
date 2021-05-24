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
	//���ʗp�|���S���̃R���|�[�l���g�𐶐�
	m_polygon = GameObject::AddComponent<PolygonSetComponent>("PolygonSetComponent");
		//�V�F�[�_�[�̃t�@�C���ꏊ���w�肷��
	// ���C�g�̌��ʂ��󂯂��A�f�B�t���[�Y�̐F�݂̂Ŕ��f����V�F�[�_�[(�t�H�O���ʂ���)
	m_shader[MESH_TYPE::NMESH_NO_LIGHTING_DIFFONLY_FOG].vertFile = "data\\Resource\\Shader\\NormalMesh_Nolighting_DiffOnly_Fog\\ShaderPolygon3DTestVS.vso";
	m_shader[MESH_TYPE::NMESH_NO_LIGHTING_DIFFONLY_FOG].pixlFile = "data\\Resource\\Shader\\NormalMesh_Nolighting_DiffOnly_Fog\\ShaderPolygon3DTestPS.pso";
	// �f�B�t���[�Y�A�X�؃L�����ƃm�[�}���}�b�v�t�����̃��b�V��
	m_shader[MESH_TYPE::NMESH_DIFF_SPEC_NORM].vertFile = "data\\Resource\\Shader\\NormalMesh_NormalMap_Fog\\ShaderPolygon3DTestVS.vso";
	m_shader[MESH_TYPE::NMESH_DIFF_SPEC_NORM].pixlFile = "data\\Resource\\Shader\\NormalMesh_NormalMap_Fog\\ShaderPolygon3DTestPS.pso";
	// ���� : �f�B�t���[�Y�A�X�؃L�����ƃm�[�}���}�b�v�V�F�[�_�[(�t�H�O���ʂ���)�A�e�t��
	m_shader[MESH_TYPE::NMESH_DIFF_SPEC_NORM_SHADOW].vertFile = "data\\Resource\\Shader\\NormalMesh_Shadow_Diff_Spec_Normal\\ShaderPolygon3DTestVS.vso";
	m_shader[MESH_TYPE::NMESH_DIFF_SPEC_NORM_SHADOW].pixlFile = "data\\Resource\\Shader\\NormalMesh_Shadow_Diff_Spec_Normal\\ShaderPolygon3DTestPS.pso";
	// ���� : �f�B�t���[�Y�A�X�؃L�����t���g�D�[���V�F�[�_�[
	m_shader[MESH_TYPE::NMESH_DIFF_SPEC_TOON].vertFile = "data\\Resource\\Shader\\NormalMesh_Diff_Spec_Toon\\ShaderPolygon3DTestVS.vso";
	m_shader[MESH_TYPE::NMESH_DIFF_SPEC_TOON].pixlFile = "data\\Resource\\Shader\\NormalMesh_Diff_Spec_Toon\\ShaderPolygon3DTestPS.pso";
	// ���� : �e�V�F�[�_�[�Z�b�g�A�b�v�p�̃m�[�}���}�b�v�t���V�F�[�_�[
	m_shader[MESH_TYPE::NMESH_SHADOW_SETUP_NOT_NORMALMAP].vertFile = "data\\Resource\\Shader\\NormalMesh_ShadowSetUp_NotNormalMap\\ShaderPolygon3DTestVS.vso";
	m_shader[MESH_TYPE::NMESH_SHADOW_SETUP_NOT_NORMALMAP].pixlFile = "data\\Resource\\Shader\\NormalMesh_ShadowSetUp_NotNormalMap\\ShaderPolygon3DTestPS.pso";
	//�s�N�Z���V�F�[�_�[�́��ł�邽�ߕK�v�Ȃ����A�����K�v�ɂȂ邩������Ȃ��̂œ���Ă���
	m_shader[MESH_TYPE::NMESH_SHADOW_SETUP_NORMALMAP].vertFile = "data\\Resource\\Shader\\NormalMesh_ShadowSetUp_NormalMap\\ShaderPolygon3DTestVS.vso";
	m_shader[MESH_TYPE::NMESH_SHADOW_SETUP_NORMALMAP].pixlFile = "data\\Resource\\Shader\\NormalMesh_ShadowSetUp_NormalMap\\ShaderPolygon3DTestPS.pso";
	
	// �t���l������(��)�V�F�[�_�[
	m_shader[MESH_TYPE::WATER].vertFile = "data\\Resource\\Shader\\FresnelReflection\\ShaderPolygon3DTestVS.vso";
	m_shader[MESH_TYPE::WATER].pixlFile = "data\\Resource\\Shader\\FresnelReflection\\ShaderPolygon3DTestPS.pso";

	ResourceManager *p = CommonObjects::GetInstance()->FindGameObject<ResourceManager>("SystemResource");
	for (auto & it : m_shader)
	{
		//�t�@�C���w�肵���ꏊ���ꊇ���[�h
		p->ShaderLoad(it.second.vertFile, true);
		p->ShaderLoad(it.second.pixlFile, false);
	}
	//�g�D�[���e�N�X�`���̓ǂݍ���
	m_toonTexture.fileName = "data\\Texture\\Shader\\GradTex_2Color.png";
	//m_toonTexture.fileName = "data\\texture\\Shader\\GradTex.png";
	p->TextureLoad(m_toonTexture.fileName);

	//�e�V�F�[�_�[�ϐ��̏�����
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

	//�[�x�摜�擾���̃J�����ݒ�ϐ�
	m_othroParam = 39.9f;
	m_offsetParam = 64.8f;
	m_farParam = 100.f;

}

Shader::~Shader()
{
	//�n���h���̓��\�[�X�}�l�[�W���[�Ŏ����f���[�g�����̂Ń��X�g�̏���������������B
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
			//���_�V�F�[�_�[�̓ǂݍ���
			if (it.second.vertex < 0)
			{
				if (!p->CheckHandle(it.second.vertFile))	//���̃t�@�C���̃��[�h���I����Ă��邩�m�F
					return;
				//�I����Ă�����n���h��������
				it.second.vertex = p->GetHandle(it.second.vertFile);
			}
			//�s�N�Z���V�F�[�_�[�̓ǂݍ���
			if (it.second.pixcel < 0)
			{
				if (!p->CheckHandle(it.second.pixlFile))	//���̃t�@�C���̃��[�h���I����Ă��邩�m�F
					return;
				//�I����Ă�����n���h��������
				it.second.pixcel = p->GetHandle(it.second.pixlFile);
			}
		}
		if (m_toonTexture.handle < 0)
		{
			if (!p->CheckHandle(m_toonTexture.fileName))	//���̃t�@�C���̃��[�h���I����Ă��邩�m�F
				return;
			//�I����Ă�����n���h��������
			m_toonTexture.handle = p->GetHandle(m_toonTexture.fileName);
		}
		//���[�h���S�ďI����Ă���̂��m�F�ł����玟����`�F�b�N���Ȃ�
		m_loadEnd = true;
	}

	Debug::DebugPrintf(200, 500, "SystemShader", "Far : %f", m_farParam);
	Debug::DebugPrintf(200, 520, "SystemShader", "Off : %f", m_offsetParam);
	Debug::DebugPrintf(200, 540, "SystemShader", "Oth : %f", m_othroParam);
	Debug::DebugPrintf(200, 560, "SystemShader", "Test : %f", m_shadowCorrection);

}

void Shader::CBufferUpdate()
{
	//���_�V�F�[�_�[�ɒl�̏�������
	//�V�F�[�_�[����float4x4��ݒ肵�Ă���̂ŁA�������MATRIX�������LIGHT_MATRIX�ɕϊ�����
	LIGHT_MATRIX * p = reinterpret_cast<LIGHT_MATRIX*>(GetBufferShaderConstantBuffer(m_cbufferVS));
	p->projection = m_lightMat.projection;
	p->view = m_lightMat.view;
	UpdateShaderConstantBuffer(m_cbufferVS);
	SetShaderConstantBuffer(m_cbufferVS, DX_SHADERTYPE_VERTEX, 4);
	//�s�N�Z���V�F�[�_�[�ɒl�̏�������
	if (CheckHitKey(KEY_INPUT_Z))
		m_shadowCorrection += 0.01f;
	if (CheckHitKey(KEY_INPUT_X))
		m_shadowCorrection -= 0.01f;
	//DrawFormatString(600, 60, 0xffffff, "test    : %f", test);	//�f�o�b�N���l�\��
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

	// ���̖ʂ̖@�����Z�o
	MirrorNormal = VNorm(VCross(VSub(MirrorWorldPosP[1], MirrorWorldPosP[0]), VSub(MirrorWorldPosP[2], MirrorWorldPosP[0])));

	// ���̖ʂ���J�����̍��W�܂ł̍ŒZ�����A���̖ʂ���J�����̒����_�܂ł̍ŒZ�������Z�o
	EyeLength = Plane_Point_MinLength(MirrorWorldPosP[0], MirrorNormal, _cPosition);
	TargetLength = Plane_Point_MinLength(MirrorWorldPosP[0], MirrorNormal, _cTarget);

	// ���ɉf��f����`�悷��ۂɎg�p����J�����̍��W�ƃJ�����̒����_���Z�o
	MirrorCameraEyePos = VAdd(_cPosition, VScale(MirrorNormal, -EyeLength * 2.0f));
	MirrorCameraTargetPos = VAdd(_cTarget, VScale(MirrorNormal, -TargetLength * 2.0f));

	// �v�Z�œ���ꂽ�J�����̍��W�ƃJ�����̒����_�̍��W���J�����̐ݒ肷��
	SetCameraPositionAndTarget_UpVecY(MirrorCameraEyePos, MirrorCameraTargetPos);
	SetCameraNearFar(0.01f, 3000.f);
	// ���ɉf��f���̒��ł̋��̎l���̍��W���Z�o( �������W )
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

	// ���̖ʂ̖@�����Z�o
	MirrorNormal = VNorm(VCross(VSub(m_mirror[_mirrorNum].Position[1], m_mirror[_mirrorNum].Position[0]), VSub(m_mirror[_mirrorNum].Position[2], m_mirror[_mirrorNum].Position[0])));

	// ���̕`��Ɏg�p���钸�_�̃Z�b�g�A�b�v
	for (int i = 0; i < 4; i++)
	{
		// ���W���Z�b�g
		Vert[i].pos = m_mirror[_mirrorNum].Position[i];

		// �@����Z�b�g
		Vert[i].norm = MirrorNormal;

		// Diffuse Color ���Z�b�g
		Vert[i].dif = m_mirror[_mirrorNum].diffuse;

		// �⏕���W�ɋ��ɉf�鎋�_�ł̎ˉe���W��������
		Vert[i].spos.x = m_mirror[_mirrorNum].ScreenPosition[i].x / 1024.f;
		Vert[i].spos.y = m_mirror[_mirrorNum].ScreenPosition[i].y / 512.f;
		Vert[i].spos.z = m_mirror[_mirrorNum].ScreenPosition[i].z;
		Vert[i].spos.w = m_mirror[_mirrorNum].ScreenPosition[i].w;
	}
	Vert[4] = Vert[2];
	Vert[5] = Vert[1];

	// �`�惂�[�h���o�C���j�A�t�B���^�����O�ɐݒ�
	SetDrawMode(DX_DRAWMODE_BILINEAR);

	// �`��u�����h���[�h���Z�b�g
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	//// �`��ɂy�o�b�t�@���g�p����
	SetUseZBuffer3D(TRUE);

	//// �y�o�b�t�@�ɏ������݂��s��
	SetWriteZBuffer3D(TRUE);

	// �g�p���钸�_�V�F�[�_�[���Z�b�g
	SetUseVertexShader(m_shader[MESH_TYPE::WATER].vertex);

	// �g�p����s�N�Z���V�F�[�_�[���Z�b�g
	SetUsePixelShader(m_shader[MESH_TYPE::WATER].pixcel);

	// �g�p����e�N�X�`�����Z�b�g
	SetUseTextureToShader(0, m_mirror[_mirrorNum].handle);

	// �t���l�����˂̋���`��
	DrawPolygon3DToShader(Vert, 2);

	//�g�p�����e�N�X�`���̃p�X������
	SetUseTextureToShader(0, -1);

	//// �y�o�b�t�@�ɏ������݂��s���ݒ�����ɖ߂�
	SetWriteZBuffer3D(FALSE);

	//// �y�o�b�t�@���g�p����ݒ�����ɖ߂�
	SetUseZBuffer3D(FALSE);

	// �`��u�����h���[�h�����ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	// �`�惂�[�h�����ɖ߂�
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
		SetUseTextureToShader(3, -1);	//�g�D�[�����ݒ肳��Ă������̉���
		SetUseTextureToShader(4, -1);	//�e�e�N�X�`�����ݒ肳��Ă������̉���
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
		//�[�x�摜���s�N�Z���V�F�[�_�[�ɃZ�b�g
		SetUseTextureToShader(4, m_deptHandle);
		SetUseVertexShader(m_shader[_type].vertex);

		break;
	default:	//���̑����ɐݒ肷��K�v�̂Ȃ��V�F�[�_�[
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
		//�J�����̐ݒ���L�[�{�[�h�Őݒ�
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
		// �J���������C�g�̌����Ɏw�肵�A�ꏊ�͎蓮�Őݒ肵���l�ɂ���(��X�Œ�l�ɂ���)
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