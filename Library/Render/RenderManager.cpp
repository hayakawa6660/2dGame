#include "RenderManager.h"
#include "Render2D/Render2D.h"
#include "Render3D/Render3D.h"

RenderManager* RenderManager::GetInstance()
{
	static RenderManager * instance = nullptr;
	if (!instance)
	{
		instance = new RenderManager;
	}
	return instance;
}

RenderManager::RenderManager() :
	m_render2D(nullptr),
	m_render3D(nullptr)
{
	m_render2D = new Render2D;
	m_render3D = new Render3D;
}

RenderManager::~RenderManager()
{
	Release();
}

void RenderManager::Update()
{
	if (m_render2D) m_render2D->Update();
	if (m_render3D) m_render3D->Update();
}

void RenderManager::Draw()
{
	if (m_render3D) m_render3D->Draw();
	if (m_render2D) m_render2D->Draw();
}

void RenderManager::Release()
{
	if (m_render2D)
	{
		delete m_render2D;
		m_render2D = nullptr;
	}

	if (m_render3D)
	{
		delete m_render3D;
		m_render3D = nullptr;
	}
}

bool RenderManager::CreateCamera()
{
	return m_render3D->CreateCamera();
}

bool RenderManager::DeleteCamera()
{
	return m_render3D->DeleteCamera();
}

bool RenderManager::AddTexture(std::string _name, Sprite_Info & _sprite, std::function<void()> _func)
{
	return m_render2D->AddTexture(_name, _sprite, _func);
}

bool RenderManager::RemoveTexture(std::string _name)
{
	return m_render2D->RemoveTexture(_name);
}

bool RenderManager::AddText(std::string _name, std::function<void()> _func)
{
	return m_render2D->AddText(_name, _func);
}

bool RenderManager::RemoveText(std::string _name)
{
	return m_render2D->RemoveText(_name);
}

bool RenderManager::AddMV1Model(std::string _name, int _handler, Shader3D::MESH_TYPE _mesh, Shader3D::MESH_TYPE _shadowMesh, bool _isWaterDraw, bool _isTriangleDraw)
{
	return m_render3D->AddMV1Model(_name, _handler, _mesh, _shadowMesh, _isWaterDraw, _isTriangleDraw);
}

bool RenderManager::RemoveMV1Model(std::string _name)
{
	return m_render3D->RemoveMV1Model(_name);
}

const Render3D * RenderManager::GetRender3D() const
{
	return m_render3D;
}

const Camera * RenderManager::GetCamera() const
{
	return m_render3D->GetCamera();
}
