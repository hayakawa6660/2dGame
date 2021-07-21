#pragma once

#include <map>
#include "Shader3D/Shader3D.h"
#include "Camera/Camera.h"

class GameObject;
class RenderCamera;
//登録したmv1モデルを描画するだけのクラス。
//特にモデルの移動などの関数などは無いため、動かす方のクラスでhandlerを保持して移動させてください。
class Render3D
{
public:
	Render3D();
	~Render3D();
	void Update();
	void Draw();
	void ShadowSetUp();
	void DrawSetUp();
	void DrawMain();
private:
	struct MV1Render_Info
	{
		Shader3D::MESH_TYPE shadowMesh;
		Shader3D::MESH_TYPE mesh;
		int handler;
		bool isWaterDraw;
		bool isTriangleDraw;
	};
	std::map<std::string, MV1Render_Info> m_mv1RenderList;
	Shader3D *m_shader;
	VECTOR m_target;
	Camera* m_camera;
public:
	bool CreateCamera();
	bool DeleteCamera();
	const Camera *GetCamera()const { return m_camera; }
	//描画するモデルを追加する。
	bool AddMV1Model(std::string _name, int _handler, Shader3D::MESH_TYPE _mesh, Shader3D::MESH_TYPE _shadowMesh, bool _isWaterDraw = false, bool _isTriangleDraw = false);
};