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
//時間があるときでいいので、Playerの下記関数の最後にそれぞれ付け足してください
/************* ShadowSetUp()
	//頂点シェーダーのみを入れ替えて、他キャラも同じピクセルシェーダーでやるので解除はしない
	m_shader->SetMeshTypeShader(Shader::MESH_TYPE::NMESH_SHADOW_SETUP_NOT_NORMALMAP);
	MV1DrawModel(m_model.handle);

************** DrawSetUp()
	m_shader->SetMeshTypeShader(Shader::MESH_TYPE::NMESH_DIFF_SPEC_TOON);
	MV1DrawModel(m_model.handle);
	m_shader->SetMeshTypeShader(Shader::MESH_TYPE::NO_SHADER);

*/