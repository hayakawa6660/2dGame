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
	//カメラを生成する。成功したらtrue
	bool CreateCamera();
	//カメラを削除する。成功したらtrue
	bool DeleteCamera();
	//モデルを追加する。西欧したらtrue
	bool AddMV1Model(std::string _name, int _handler, Shader3D::MESH_TYPE _mesh, Shader3D::MESH_TYPE _shadowMesh, bool _isWaterDraw = false, bool _isTriangleDraw = false);
	const Render3D* GetRender3D()const;
	const Camera *GetCamera()const;
};