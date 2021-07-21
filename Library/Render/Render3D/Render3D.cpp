#include "Render3D.h"
#include "Shader3D/Shader3D.h"

Render3D::Render3D() :
	m_shader(nullptr),
	m_camera(nullptr)
{
	m_shader = new Shader3D;
}

Render3D::~Render3D()
{
	if (m_shader)
	{
		delete m_shader;
		m_shader = nullptr;
	}
	if (m_camera)
	{
		delete m_camera;
		m_camera = nullptr;
	}
}

void Render3D::Update()
{
	if (m_shader) m_shader->Update();
	if (m_camera) m_camera->Update();
}

void Render3D::Draw()
{
	//�J��������������Ă��Ȃ������猋�Ǖ`�悳��Ȃ��̂Ńv���Z�X���΂��B
	if (!m_camera) return;
	ShadowSetUp();
	DrawSetUp();
	DrawMain();
}

void Render3D::ShadowSetUp()
{
	m_shader->SetShadowSetUpShader(true);
	//�`��
	for (auto it : m_mv1RenderList)
	{
		auto second = it.second;
		//�e�p�V�F�[�_�[�������Ȃ�Ήe�̃Z�b�g�A�b�v���΂��ĉe�`������Ȃ��悤�ɂ���B
		if (second.shadowMesh == Shader3D::MESH_TYPE::NO_SHADER)
			continue;
		if (!second.isTriangleDraw)
		{
			m_shader->SetMeshTypeShader(second.shadowMesh);
			MV1DrawModel(second.handler);
		}
		else
		{
			//4��8�����݂��Ă���̂ŁA�V�F�[�_�[��������K�v������B
			int triListNum = MV1GetTriangleListNum(second.handler);
			for (int i = 0; i < triListNum; i++)
			{
				//4�{�[���ȓ���5�{�[���ȏ�ŃV�F�[�_�[�𕪂���12�ȏ�͌����Ή�
				int type = MV1GetTriangleListVertexType(second.handler, i);
				switch (type)
				{
				case DX_MV1_VERTEX_TYPE_1FRAME:			m_shader->SetMeshTypeShader(Shader3D::MESH_TYPE::NMESH_SHADOW_SETUP_NOT_NORMAL);	break;
				case DX_MV1_VERTEX_TYPE_4FRAME:			m_shader->SetMeshTypeShader(Shader3D::MESH_TYPE::SKIN4_SHADOW_SETUP_NOT_NORMAL);	break;
				case DX_MV1_VERTEX_TYPE_8FRAME:			m_shader->SetMeshTypeShader(Shader3D::MESH_TYPE::SKIN8_SHADOW_SETUP_NOT_NORMAL);	break;
				case DX_MV1_VERTEX_TYPE_NMAP_1FRAME:	m_shader->SetMeshTypeShader(Shader3D::MESH_TYPE::NMESH_SHADOW_SETUP_NORMALMAP);		break;
				case DX_MV1_VERTEX_TYPE_NMAP_4FRAME:	m_shader->SetMeshTypeShader(Shader3D::MESH_TYPE::SKIN4_SHADOW_SETUP_NORMALMAP);		break;
				case DX_MV1_VERTEX_TYPE_NMAP_8FRAME:	m_shader->SetMeshTypeShader(Shader3D::MESH_TYPE::SKIN8_SHADOW_SETUP_NORMALMAP);		break;
				}
				MV1DrawTriangleList(second.handler, i);
			}
		}
		//m_shader->SetMeshTypeShader(Shader3D::MESH_TYPE::NO_SHADER);
	}
	m_shader->SetShadowSetUpShader(false);
}

void Render3D::DrawSetUp()
{
	int num = m_shader->GetMirrorNum();
	{	//��(����)���猩�����̔��˔̃Z�b�g�A�b�v
		VECTOR pos = m_shader->GetPosition();
		VECTOR target = m_camera->GetTarget();
		for (int i = 0; i < num; ++i)
		{
			m_shader->SetUpMirror(i, pos, target);
			//�`��
			for (auto it : m_mv1RenderList)
			{
				auto second = it.second;
				if (!second.isTriangleDraw)
				{
					m_shader->SetMeshTypeShader(second.mesh);
					MV1DrawModel(second.handler);
				}
				else
				{
					//4��8�����݂��Ă���̂ŁA�V�F�[�_�[��������K�v������B
					int triListNum = MV1GetTriangleListNum(second.handler);
					for (int i = 0; i < triListNum; i++)
					{
						//4�{�[���ȓ���5�{�[���ȏ�ŃV�F�[�_�[�𕪂���12�ȏ�͌����Ή�
						int type = MV1GetTriangleListVertexType(second.handler, i);
						switch (type)
						{
						case DX_MV1_VERTEX_TYPE_1FRAME:			m_shader->SetMeshTypeShader(Shader3D::MESH_TYPE::NMESH_DIFFUSE_ONLY);		break;
						case DX_MV1_VERTEX_TYPE_4FRAME:			m_shader->SetMeshTypeShader(Shader3D::MESH_TYPE::SKIN4_DIFFUSE_ONLY);		break;
						case DX_MV1_VERTEX_TYPE_8FRAME:			m_shader->SetMeshTypeShader(Shader3D::MESH_TYPE::SKIN8_DIFFUSE_ONLY);		break;
						case DX_MV1_VERTEX_TYPE_NMAP_1FRAME:	m_shader->SetMeshTypeShader(Shader3D::MESH_TYPE::NMESH_DIFF_SPEC_NORM);		break;
						case DX_MV1_VERTEX_TYPE_NMAP_4FRAME:	m_shader->SetMeshTypeShader(Shader3D::MESH_TYPE::SKIN4_DIFF_SPEC_NORM);		break;
						case DX_MV1_VERTEX_TYPE_NMAP_8FRAME:	m_shader->SetMeshTypeShader(Shader3D::MESH_TYPE::SKIN8_DIFF_SPEC_NORM);		break;
						}
						MV1DrawTriangleList(second.handler, i);
					}
				}
			}
		}
	}

}

void Render3D::DrawMain()
{
	{	//�{�\��

		m_camera->SetCameraPosAndDir();
		//�`��
		for (auto& it : m_mv1RenderList)
		{
			auto second = it.second;
			if (!second.isTriangleDraw)
			{
				m_shader->SetMeshTypeShader(second.mesh);
				MV1DrawModel(second.handler);
			}
			else
			{
				//4��8�����݂��Ă���̂ŁA�V�F�[�_�[��������K�v������B
				int triListNum = MV1GetTriangleListNum(second.handler);
				for (int i = 0; i < triListNum; i++)
				{
					//4�{�[���ȓ���5�{�[���ȏ�ŃV�F�[�_�[�𕪂���12�ȏ�͌����Ή�
					int type = MV1GetTriangleListVertexType(second.handler, i);
					switch (type)
					{
					case DX_MV1_VERTEX_TYPE_1FRAME:			m_shader->SetMeshTypeShader(Shader3D::MESH_TYPE::NMESH_DIFFUSE_ONLY);		break;
					case DX_MV1_VERTEX_TYPE_4FRAME:			m_shader->SetMeshTypeShader(Shader3D::MESH_TYPE::SKIN4_DIFFUSE_ONLY);		break;
					case DX_MV1_VERTEX_TYPE_8FRAME:			m_shader->SetMeshTypeShader(Shader3D::MESH_TYPE::SKIN8_DIFFUSE_ONLY);		break;
					case DX_MV1_VERTEX_TYPE_NMAP_1FRAME:	m_shader->SetMeshTypeShader(Shader3D::MESH_TYPE::NMESH_DIFF_SPEC_NORM);		break;
					case DX_MV1_VERTEX_TYPE_NMAP_4FRAME:	m_shader->SetMeshTypeShader(Shader3D::MESH_TYPE::SKIN4_DIFF_SPEC_NORM);		break;
					case DX_MV1_VERTEX_TYPE_NMAP_8FRAME:	m_shader->SetMeshTypeShader(Shader3D::MESH_TYPE::SKIN8_DIFF_SPEC_NORM);		break;
					}
					MV1DrawTriangleList(second.handler, i);
				}
			}
		}
	}
	/*
	{	//���ʕ\��
		int num = m_shader->GetMirrorNum();
		for (int i = 0; i < num; ++i)
			m_shader->MirrorRender(i);
	}
	*/
}

bool Render3D::CreateCamera()
{
	if (m_camera) return false;
	m_camera = new Camera();
	return true;
}

bool Render3D::DeleteCamera()
{
	if (m_camera)
	{
		delete m_camera;
		m_camera = nullptr;
		return true;
	}
	return false;
}

bool Render3D::AddMV1Model(std::string _name, int _handler, Shader3D::MESH_TYPE _mesh, Shader3D::MESH_TYPE _shadowMesh, bool _isWaterDraw, bool _isTriangleDraw)
{
	//�������݂�����ǉ����Ȃ�
	if (m_mv1RenderList.count(_name)) return false;
	MV1Render_Info info;
	info.handler = _handler;
	info.mesh = _mesh;
	info.shadowMesh = _shadowMesh;
	info.isWaterDraw = _isWaterDraw;
	info.isTriangleDraw = _isTriangleDraw;
	m_mv1RenderList.emplace(_name, info);
	return true;
}