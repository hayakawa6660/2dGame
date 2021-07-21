#include "RenderManager.h"
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
	m_render3D(nullptr)
{
	m_render3D = new Render3D;
}

RenderManager::~RenderManager()
{
	Release();
}

void RenderManager::Update()
{
	if (m_render3D) m_render3D->Update();
}

void RenderManager::Draw()
{
	if (m_render3D) m_render3D->Draw();
}

void RenderManager::Release()
{
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

bool RenderManager::AddMV1Model(std::string _name, int _handler, Shader3D::MESH_TYPE _mesh, Shader3D::MESH_TYPE _shadowMesh, bool _isWaterDraw, bool _isTriangleDraw)
{
	return m_render3D->AddMV1Model(_name, _handler, _mesh, _shadowMesh, _isWaterDraw, _isTriangleDraw);
}

const Render3D * RenderManager::GetRender3D() const
{
	return m_render3D;
}

const Camera * RenderManager::GetCamera() const
{
	return m_render3D->GetCamera();
}
