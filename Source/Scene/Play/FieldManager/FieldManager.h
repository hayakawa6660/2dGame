#pragma once

#include "Library/GameObject/GameObject.h"
#include "Source/Common.h"

class Shader;
class FieldManager : public GameObject
{
public:
	FieldManager(SceneBase * _scene);
	~FieldManager();
private:
	void Load()override;
	void Start()override;
	void Update()override;
	void ShadowSetUp()override;
	void DrawSetUp()override;
	void Draw()override;
private:
	Model_Info m_ground;
	Model_Info m_sky;
	Shader * m_shader;
};

/*
//���Ԃ�����Ƃ��ł����̂ŁAPlayer�̉��L�֐��̍Ō�ɂ��ꂼ��t�������Ă�������
/************* ShadowSetUp()
	//���_�V�F�[�_�[�݂̂����ւ��āA���L�����������s�N�Z���V�F�[�_�[�ł��̂ŉ����͂��Ȃ�
	m_shader->SetMeshTypeShader(Shader::MESH_TYPE::NMESH_SHADOW_SETUP_NOT_NORMALMAP);
	MV1DrawModel(m_model.handle);

************** DrawSetUp()
	m_shader->SetMeshTypeShader(Shader::MESH_TYPE::NMESH_DIFF_SPEC_TOON);
	MV1DrawModel(m_model.handle);
	m_shader->SetMeshTypeShader(Shader::MESH_TYPE::NO_SHADER);

*/