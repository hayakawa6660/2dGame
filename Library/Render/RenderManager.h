#pragma once

#include <MyDxLib.h>
#include <map>
#include "Library/GameObject/GameObject.h"
#include "Render3D/Shader3D/Shader3D.h"
#include <functional>

class Render2D;
class Render3D;
class Camera;
class RenderManager
{
public:
	static RenderManager* GetInstance();
	RenderManager();
	~RenderManager();

	void Update();
	void Draw();
	void Release();

private:
	Render2D* m_render2D;
	Render3D* m_render3D;
public:
	//�J�����𐶐�����B����������true
	bool CreateCamera();
	//�J�������폜����B����������true
	bool DeleteCamera();
	//�e�N�X�`����ǉ�����B����������true
	bool AddTexture(std::string _name, Sprite_Info& _sprite, std::function<void()> _func);
	bool RemoveTexture(std::string _name);
	//�e�L�X�g��ǉ�����
	bool AddText(std::string _name, std::function<void()> _func);
	bool RemoveText(std::string _name);
	//���f����ǉ�����B����������true
	bool AddMV1Model(std::string _name, int _handler, Shader3D::MESH_TYPE _mesh, Shader3D::MESH_TYPE _shadowMesh, bool _isWaterDraw = false, bool _isTriangleDraw = false);
	//���f����`�悵�Ȃ�����B�폜����킯�ł͐m��Œ���
	bool RemoveMV1Model(std::string _name);
	const Render3D* GetRender3D()const;
	const Camera *GetCamera()const;
};