#pragma once

#include <MyDxLib.h>
#include <map>
#include "Library/GameObject/GameObject.h"
#include "Render3D/Shader3D/Shader3D.h"

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
	Render3D* m_render3D;
public:
	//�J�����𐶐�����B����������true
	bool CreateCamera();
	//�J�������폜����B����������true
	bool DeleteCamera();
	//���f����ǉ�����B����������true
	bool AddMV1Model(std::string _name, int _handler, Shader3D::MESH_TYPE _mesh, Shader3D::MESH_TYPE _shadowMesh, bool _isWaterDraw = false, bool _isTriangleDraw = false);
	const Render3D* GetRender3D()const;
	const Camera *GetCamera()const;
};