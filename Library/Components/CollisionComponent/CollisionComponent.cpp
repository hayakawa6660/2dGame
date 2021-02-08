#include "CollisionComponent.h"
#include "Library/GameObject/GameObject.h"

CollisionComponent::CollisionComponent() :
	m_model(-1)
{
	m_line.clear();
	m_sphere.clear();
	m_capsule.clear();
	m_callback.clear();
}

CollisionComponent::~CollisionComponent()
{
	m_line.clear();
	m_sphere.clear();
	m_capsule.clear();
	m_callback.clear();
	m_model = -1;
}

void CollisionComponent::Start()
{
	std::string str = "OnCollision";
	//�����蔻������m����֐����Z�b�g
	m_callback[str] = [&](Hit_Info _info) { m_parent->OnCollision(_info); };
}

void CollisionComponent::Update()
{
	m_line.clear();
	m_capsule.clear();
	m_sphere.clear();

	if (m_model > 0)
		MV1RefreshCollInfo(m_model);
}

void CollisionComponent::SetCollisionModel(int _model)
{
	m_model = _model;
	MV1SetupCollInfo(m_model);
}

void CollisionComponent::SetSphere(const VECTOR & _centerPos, float _radius, std::string _name)
{
	Sphere_Info info(_centerPos, _radius, _name);
	m_sphere.emplace_back(info);
}

void CollisionComponent::SetLine(const VECTOR &_firstPos, const VECTOR & _endPos, std::string _name)
{
	Line_Info info(_firstPos, _endPos, _name);
	m_line.emplace_back(info);
}

void CollisionComponent::SetCapsule(const VECTOR & _firstPos, const VECTOR & _endPos, float _radius, std::string _name)
{
	Capsule_Info info(_firstPos, _endPos, _radius, _name);
	m_capsule.emplace_back(info);
}

void CollisionComponent::SetEvent(std::string _eventName, std::function<void(Hit_Info)> _func)
{
	m_callback.emplace(_eventName, _func);
}

void CollisionComponent::RemoveEvent(std::string _eventName)
{
	if (!m_callback.count(_eventName))
		return;
	m_callback.erase(_eventName);
}

void CollisionComponent::LineToModel(CollisionComponent * _p)
{
	std::list<Line_Info> info = _p->GetLineInfo();

	for (auto & it : info)
	{
		Hit_Info info;
		info.singlePoly = MV1CollCheck_Line(m_model, -1, it.firstPos, it.endPos);
		if (info.singlePoly.HitFlag)
		{
			if (m_isTrigger && _p->GetIsTrigger())
			{
				GameObject * p = _p->GetParent();
				VECTOR currentPos = p->GetPosition();
				VECTOR hitPos = info.singlePoly.HitPosition;
				VECTOR dir = it.firstPos - it.endPos;
				if (dir.x != 0.f || dir.z != 0.f)
				{	//XZ�␳
					float vel = VDot(dir, info.singlePoly.Normal);
					if (vel <= 0)
					{
						VECTOR w = dir - VScale(info.singlePoly.Normal, vel);
						currentPos = VGet(hitPos.x, currentPos.y, hitPos.z);
						currentPos = VGet(currentPos.x + w.x, currentPos.y, currentPos.z + w.z);
					}
				}
				if (dir.y != 0.f)
				{	//Y�␳
					currentPos.y = hitPos.y;
				}
				p->SetPosition(currentPos);
			}
			info.name = _p->GetTag();
			for (auto &call : m_callback)
				call.second(info);
			//���O�������̂ɂ��đ����OnCollision�ɓ����
			info.name = m_tag;
			for (auto & call : _p->GetCallBackFunction())
				call.second(info);
		}
	}
}

void CollisionComponent::CapsuleToModel(CollisionComponent * _p)
{
}

void CollisionComponent::SphereToSpere(CollisionComponent * _p)
{
	if (!_p)
		return;
	std::list<Sphere_Info> info = _p->GetSphereInfo();
	for (auto & it1 : m_sphere)
	{
		for (auto & it2 : info)
		{
			bool hit = HitCheck_Sphere_Sphere(it1.centerPos, it1.radius, it2.centerPos, it2.radius);
			if (hit)
			{
				Hit_Info info;
				//���ʕϐ����Z�b�g
				info.norm = VNorm(it1.centerPos - it2.centerPos);	//�@����ۑ�
				{	//���g�p��Hit_Info����
					info.hitObject = _p->GetParent();				//�����N���X��ۑ�
					info.name = _p->GetTag();						//Component�̃^�O��ۑ�
					//�����蔻�肪���������̂ŃZ�b�g����Ă���R�[���o�b�N�֐����Ă�
					for (auto &call : m_callback)
						call.second(info);
				}

				{	//����p��Hit_Info����
					info.hitObject = m_parent;							//�����N���X��ۑ�
					info.name = m_tag;									//Component�̃^�O��ۑ�
					//�����蔻�肪���������̂ŃZ�b�g����Ă���R�[���o�b�N�֐����Ă�
					for (auto &call : _p->GetCallBackFunction())
						call.second(info);
				}
			}
		}
	}
}