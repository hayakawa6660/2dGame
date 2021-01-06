#include "Player.h"

#include "Library/SceneManager/SceneManager.h"
#include "Source/System/ResourceManager/ResourceManager.h"
#include "Library/Common/commonObjects.h"

#include "State/Move/PlayerMoveState.h"
#include "State/Wait/WaitState.h"
#include "State/PlayerStateBase.h"

Player::Player(SceneBase* _scene) :
	GameObject(_scene)
{
	m_texture.fileName = "data\\texture\\Player\\Slime.jpg";
	m_texture.sizeX = 223;
	m_texture.sizeY = 226;
	ResourceManager* resource = CommonObjects::GetInstance()->FindGameObject<ResourceManager>("SceneResource");
	resource->TextureLoad(m_texture.fileName);
	m_movement.SetParent(this);

}

Player::~Player()
{
}

void Player::Start()
{
	//初期ステイト
	SetNextState<WaitState>();
	ResourceManager* resource = CommonObjects::GetInstance()->FindGameObject<ResourceManager>("SceneResource");
	m_texture.handle = resource->GetHandle(m_texture.fileName);
}

void Player::Update()
{
	if (m_currentState)
		m_currentState->Update();

	m_movement.Update();
}

void Player::Draw()
{
	VECTOR position = GameObject::GetPosition();
	DrawRectGraph((int)position.x - (m_texture.sizeX / 2), (int)position.y - (m_texture.sizeY / 2),
		0, 0, m_texture.sizeX, m_texture.sizeY, m_texture.handle, true);
}
