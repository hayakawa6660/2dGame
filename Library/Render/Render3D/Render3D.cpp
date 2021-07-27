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
	//カメラが生成されていなかったら結局描画されないのでプロセスを飛ばす。
	if (!m_camera) return;
	ShadowSetUp();
	DrawSetUp();
	DrawMain();
}

void Render3D::ShadowSetUp()
{
	m_shader->SetShadowSetUpShader(true);
	//描画
	for (auto it : m_mv1RenderList)
	{
		auto second = it.second;
		//影用シェーダーが無しならば影のセットアップを飛ばして影描画をしないようにする。
		if (second.shadowMesh == Shader3D::MESH_TYPE::NO_SHADER)
			continue;
		if (!second.isTriangleDraw)
		{
			m_shader->SetMeshTypeShader(second.shadowMesh);
			MV1DrawModel(second.handler);
		}
		else
		{
			//4と8が混在しているので、シェーダーも分ける必要がある。
			int triListNum = MV1GetTriangleListNum(second.handler);
			for (int i = 0; i < triListNum; i++)
			{
				//4ボーン以内か5ボーン以上でシェーダーを分ける12以上は現状非対応
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
	{	//鏡(水面)から見た時の反射板のセットアップ
		VECTOR pos = m_shader->GetPosition();
		VECTOR target = m_camera->GetTarget();
		for (int i = 0; i < num; ++i)
		{
			m_shader->SetUpMirror(i, pos, target);
			//描画
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
					//4と8が混在しているので、シェーダーも分ける必要がある。
					int triListNum = MV1GetTriangleListNum(second.handler);
					for (int i = 0; i < triListNum; i++)
					{
						//4ボーン以内か5ボーン以上でシェーダーを分ける12以上は現状非対応
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
	{	//本表示

		m_camera->SetCameraPosAndDir();
		//描画
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
				//4と8が混在しているので、シェーダーも分ける必要がある。
				int triListNum = MV1GetTriangleListNum(second.handler);
				for (int i = 0; i < triListNum; i++)
				{
					//4ボーン以内か5ボーン以上でシェーダーを分ける12以上は現状非対応
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
	{	//水面表示
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

bool Render3D::AddMV1Model(const std::string &_name, int _handler, Shader3D::MESH_TYPE _mesh, Shader3D::MESH_TYPE _shadowMesh, bool _isWaterDraw, bool _isTriangleDraw)
{
	//もし存在したら追加しない
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

bool Render3D::RemoveMV1Model(const std::string &_name)
{
	//もし存在しなかったらdeleteしない
	if (!m_mv1RenderList.count(_name)) return false;

	m_mv1RenderList.erase(_name);	//該当する名前のモデルを削除
	return false;
}
