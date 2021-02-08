#include "PlayerUi.h"
#include "../../../Macro.h"

#include "../../../Scene/Play/Player/Player.h"
#include "../../../Scene/Play/PlayScene.h"

#include "../../../../Library/Common/commonObjects.h"
#include "../../ResourceManager/ResourceManager.h"

PlayerUi::PlayerUi(SceneBase * _scene) :
	UiBase(nullptr),
	m_isLoadEnd(false),
	m_active(false)
{
	m_hpBar.pos = VGet(90, 618, 0);
	m_staminaBar.pos = VGet(90, 638, 0);
	m_damage.maxVal = 0;
	m_damage.pos = VGet(90, 618, 0);
	m_addCount = 0;

	Create(HP_BAR, UI_TEXTURE("hp.png"));
	Create(DAMAGE_BAR, UI_TEXTURE("HPbar_red.png"));
	Create(STAMINA_BAR, UI_TEXTURE("stamina.png"));
	Create(BAR_BACK, UI_TEXTURE("hp_back.png"));

}

PlayerUi::~PlayerUi()
{
	m_ui.clear();
}

void PlayerUi::Update()
{
	if (!m_isLoadEnd)
		LoadEndCheck();

	if (!m_active)
		return;
	m_hpBar.size = (m_hpBar.val / m_hpBar.maxVal) * 283.f;
	m_staminaBar.size = (m_staminaBar.val / m_staminaBar.maxVal) * 221;

	if (--m_decreaseCount <= 0) {
		if (m_damage.val > m_hpBar.val) {
			m_damage.val -= 0.5f;
		}
	}
	m_damage.size = ((float)m_damage.val / (float)m_damage.maxVal) * 283.f;

}

void PlayerUi::Draw()
{
	if (!m_active)
		return;
	DrawGraph(60, 614, m_ui[BAR_BACK].handle, true);

	VECTOR damPos = m_damage.pos;
	DrawRectGraph((int)damPos.x, (int)damPos.y, 0, 0, (int)m_damage.size, 17, m_ui[DAMAGE_BAR].handle, true, false);

	VECTOR hpPos = m_hpBar.pos;
	//DrawGraph(hpPos.x, hpPos.y, m_ui[BAR_BACK], true);
	DrawRectGraph((int)hpPos.x, (int)hpPos.y, 0, 0, (int)m_hpBar.size, 17, m_ui[HP_BAR].handle, true, false);

	VECTOR staPos = m_staminaBar.pos;
	if (++m_addCount % 3 == 0 && m_staminaBar.val <= 250)
	{
		SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
		for (int i = 0; i < 5; i++)
		{
			DrawRectGraph((int)staPos.x, (int)staPos.y, 0, 0, (int)m_staminaBar.size, 14, m_ui[STAMINA_BAR].handle, true, false);
		}
	}
	DrawRectGraph((int)staPos.x, (int)staPos.y, 0, 0, (int)m_staminaBar.size, 14, m_ui[STAMINA_BAR].handle, true, false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//DrawFormatString(100, 100, 0x00ff00, "%d", m_ui[HP_BACK]);
}

void PlayerUi::Create(const TYPE & _type, const char* _p)
{
	if (m_ui.count(_type) != 0)
		return;

	ResourceManager * p = CommonObjects::GetInstance()->FindGameObject<ResourceManager>("SystemResource");
	p->TextureLoad(_p);
	Sprite_Info info;
	info.fileName = _p;
	info.handle = -1;
	info.sizeX = 0;
	info.sizeY = 0;

	m_ui.emplace(_type, info);
}

void PlayerUi::SetHitPiintInfo(const int & _currentHp, const int & _maxHp)
{
	m_hpBar.val = (float)_currentHp;
	m_decreaseCount = 60;
	if (m_damage.maxVal == 0)
	{
		m_hpBar.maxVal = (float)_maxHp;
		m_damage.maxVal = (float)_maxHp;
		m_damage.val = (float)_maxHp;
	}

}

void PlayerUi::SetStaminaInfo(const int & _currentStamina, const int & _maxStamina)
{
	m_staminaBar.val = (float)_currentStamina;
	m_staminaBar.maxVal = (float)_maxStamina;
}

void PlayerUi::LoadEndCheck()
{
	for (auto &it : m_ui)
	{
		if (it.second.handle >= 0)
			continue;
		ResourceManager * p = CommonObjects::GetInstance()->FindGameObject<ResourceManager>("SystemResource");
		if (!p->CheckHandle(it.second.fileName))	//このファイルのロードが終わっているか確認
			return;
		it.second.handle = p->GetHandle(it.second.fileName);
	}
	m_isLoadEnd = true;
}
