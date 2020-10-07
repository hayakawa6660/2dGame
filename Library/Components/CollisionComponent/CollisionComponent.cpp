#include "CollisionComponent.h"

CollisionComponent::CollisionComponent() :
	m_model(-1)
{
	m_capsuleList.clear();
	m_lineList.clear();
	m_sphereList.clear();
}

CollisionComponent::~CollisionComponent()
{
	m_capsuleList.clear();
	m_lineList.clear();
	m_sphereList.clear();
}

void CollisionComponent::Start()
{
}

void CollisionComponent::Update()
{
	m_lineList.clear();
	m_capsuleList.clear();
	m_sphereList.clear();
	SetUpColModel();
}

void CollisionComponent::Draw()
{
}

bool CollisionComponent::IsModelToLine(const std::list<Line_Info>& _info)
{
	for (auto & it : _info)
	{
		MV1_COLL_RESULT_POLY hit = MV1CollCheck_Line(m_model, -1, it.topPos, it.bottomPos);
		if (hit.HitFlag > 0)
			return true;
	}
	return false;
}

Hit_Info CollisionComponent::GetLineHitInfo(const std::list<Line_Info>& _info)
{
	Hit_Info info;
	info.hit = false;
	for (auto & it : _info)
	{
		MV1_COLL_RESULT_POLY hit = MV1CollCheck_Line(m_model, -1, it.topPos, it.bottomPos);
		if (hit.HitFlag > 0)
		{
			info.hit = true;
			info.hitPos = hit.HitPosition;
			info.normal = hit.Normal;
			return info;
		}
	}
	return info;
}

bool CollisionComponent::IsModelToCapsule(const std::list<Capsule_Info>& _info)
{
	for (auto &it : _info)
	{
		MV1_COLL_RESULT_POLY_DIM  info = MV1CollCheck_Capsule(m_model, -1, it.topPos, it.bottomPos, it.radius);
		if (info.HitNum > 0) {
			return true;
		}
	}
	return false;
}

bool CollisionComponent::IsCapsuleToModel(int _model)
{
	for (auto &it : m_capsuleList)
	{
		MV1_COLL_RESULT_POLY_DIM  info = MV1CollCheck_Capsule(_model, -1, it.topPos, it.bottomPos, it.radius);
		if (info.HitNum > 0) {
			return true;
		}
	}
	return false;
}

bool CollisionComponent::IsModelToSphere(const std::list<Sphere_Info>& _info)
{
	for (auto &it : _info)
	{
		MV1_COLL_RESULT_POLY_DIM info = MV1CollCheck_Sphere(m_model, -1, it.centerPos, it.radius);
		if (info.HitNum > 0) {
			return true;
		}
	}
	return false;
}

bool CollisionComponent::IsSphereToModel(int _model)
{
	for (auto &it : m_sphereList)
	{
		MV1_COLL_RESULT_POLY_DIM info = MV1CollCheck_Sphere(_model, -1, it.centerPos, it.radius);
		if (info.HitNum > 0) {
			return true;
		}
	}
	return false;
}

void CollisionComponent::SetCapsule(const VECTOR & _top, const VECTOR & _bottom, float _radius)
{
	Capsule_Info info;
	info.topPos = _top;
	info.bottomPos = _bottom;
	info.radius = _radius;
	m_capsuleList.emplace_back(info);
}

void CollisionComponent::SetSpere(const VECTOR & _centerPos, float _radius)
{
	Sphere_Info info;
	info.centerPos = _centerPos;
	info.radius = _radius;
	m_sphereList.emplace_back(info);
}

void CollisionComponent::SetLine(const VECTOR & _top, const VECTOR & _bottom)
{
	Line_Info info;
	info.topPos = _top;
	info.bottomPos = _bottom;
	m_lineList.emplace_back(info);
}

void CollisionComponent::SetModel(int _model)
{
	m_model = _model;
	MV1SetupCollInfo(m_model, -1, 32, 32, 32);
}

void CollisionComponent::SetUpColModel()
{
	if (m_model < 0)
		return;
	MV1RefreshCollInfo(m_model, -1);
}
