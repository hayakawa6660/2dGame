#include "EnemyUi.h"
#include "../../../Macro.h"

#include "../../../Scene/Play/Player/Player.h"
#include "../../../Scene/Play/PlayScene.h"

#include "../../../../Library/Common/commonObjects.h"
#include "../../ResourceManager/ResourceManager.h"

EnemyUi::EnemyUi(SceneBase * _scene) :
	UiBase(nullptr),
	m_isLoadEnd(false),
	m_decreaseCount(0),
	m_nextHp(0)
{
	ResourceManager * p = CommonObjects::GetInstance()->FindGameObject<ResourceManager>("SystemResource");
	m_bar[(int)TYPE::HP_BAR].fileName = "data\\texture\\Ui\\boss_hp.png";
	p->TextureLoad(m_bar[(int)TYPE::HP_BAR].fileName);
	m_bar[(int)TYPE::HP_BAR].texture = -1;
	m_bar[(int)TYPE::HP_BAR].texSize = VGet(549, 19, 0);
	m_bar[(int)TYPE::HP_BAR].pos = VGet(791, 26, 0);

	m_bar[(int)TYPE::BACK].fileName = "data\\texture\\Ui\\boss_hp_back.png";
	p->TextureLoad(m_bar[(int)TYPE::BACK].fileName);
	m_bar[(int)TYPE::BACK].texture = -1;
	m_bar[(int)TYPE::BACK].texSize = VGet(557, 60, 0);
	m_bar[(int)TYPE::BACK].pos = VGet(787, 4, 0);

	m_bar[(int)TYPE::DAMAGE].fileName = "data\\texture\\Ui\\boss_hp_red.png";
	p->TextureLoad(m_bar[(int)TYPE::DAMAGE].fileName);
	m_bar[(int)TYPE::DAMAGE].texture = -1;
	m_bar[(int)TYPE::DAMAGE].texSize = VGet(549, 19, 0);
	m_bar[(int)TYPE::DAMAGE].pos = VGet(791, 26, 0);
}

EnemyUi::~EnemyUi()
{
}

void EnemyUi::Update()
{
	if (!m_isLoadEnd)
		LoadUpdate();

	m_bar[(int)TYPE::HP_BAR].whidhtHarf = ((float)m_bar[(int)TYPE::HP_BAR].currentHp
		/ (float)m_bar[(int)TYPE::HP_BAR].maxHp) * (float)m_bar[(int)TYPE::HP_BAR].texSize.x;

	if (--m_decreaseCount <= 0) {
		if (m_bar[(int)TYPE::DAMAGE].currentHp > m_bar[(int)TYPE::HP_BAR].currentHp) {
			m_bar[(int)TYPE::DAMAGE].currentHp -= 3;
		}
	}
	m_bar[(int)TYPE::DAMAGE].whidhtHarf = ((float)m_bar[(int)TYPE::DAMAGE].currentHp
		/ (float)m_bar[(int)TYPE::DAMAGE].maxHp) * (float)m_bar[(int)TYPE::DAMAGE].texSize.x;
}

void EnemyUi::Draw()
{
	VECTOR backPos = m_bar[(int)TYPE::BACK].pos;
	DrawRectGraph((int)backPos.x, (int)backPos.y, 0, 0, (int)m_bar[(int)TYPE::BACK].texSize.x, (int)m_bar[(int)TYPE::BACK].texSize.y, m_bar[(int)TYPE::BACK].texture, true, false);

	VECTOR damagePos = m_bar[(int)TYPE::DAMAGE].pos;
	if (m_decreaseCount % 3 == 0 && m_decreaseCount >= 0) {
		SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
		for (int i = 0; i < 5; i++)
		{
			DrawRectGraph((int)damagePos.x, (int)damagePos.y, 0, 0, (int)m_bar[(int)TYPE::DAMAGE].whidhtHarf, 34, m_bar[(int)TYPE::DAMAGE].texture, true, false);
		}
	}
	DrawRectGraph((int)damagePos.x, (int)damagePos.y, 0, 0, (int)m_bar[(int)TYPE::DAMAGE].whidhtHarf, 34, m_bar[(int)TYPE::DAMAGE].texture, true, false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	VECTOR hpPos = m_bar[(int)TYPE::HP_BAR].pos;
	DrawRectGraph((int)hpPos.x, (int)hpPos.y, 0, 0, (int)m_bar[(int)TYPE::HP_BAR].whidhtHarf, (int)m_bar[(int)TYPE::HP_BAR].texSize.y, m_bar[(int)TYPE::HP_BAR].texture, true, false);
}

void EnemyUi::LoadUpdate()
{
	ResourceManager * p = CommonObjects::GetInstance()->FindGameObject<ResourceManager>("SystemResource");
	for (auto &it : m_bar)
	{
		if (it.texture >= 0)
			continue;
		if (!p->CheckHandle(it.fileName))
			return;
		it.texture = p->GetHandle(it.fileName);
	}
	m_isLoadEnd = true;
}

void EnemyUi::Reset(int _hp)
{
	m_bar[(int)TYPE::HP_BAR].maxHp = _hp;
	m_bar[(int)TYPE::HP_BAR].currentHp = _hp;

	m_bar[(int)TYPE::DAMAGE].maxHp = _hp;
	m_bar[(int)TYPE::DAMAGE].currentHp = _hp;
}

void EnemyUi::SetHitPointInfo(const int & _currentHp)
{
	m_bar[(int)TYPE::HP_BAR].currentHp = _currentHp;
	m_decreaseCount = 60;
}