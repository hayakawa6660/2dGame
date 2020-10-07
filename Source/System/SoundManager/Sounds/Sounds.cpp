#include "Sounds.h"
#include "../../../../Library/Common/commonObjects.h"
#include "../../ResourceManager/ResourceManager.h"
#include "../../CsvManager/CsvManager.h"

Sounds::Sounds(SceneBase * _scene) :
	GameObject(_scene),
	m_isScene(false)
{
	m_soundList.clear();
}

Sounds::~Sounds()
{
	if (m_isScene)
	{
		//シーン系のサウンドなら、全てdelete
		std::string resourceName = "SceneResource";

		ResourceManager * p = CommonObjects::GetInstance()->FindGameObject<ResourceManager>(resourceName);
		for (auto & it : m_soundList)
		{
			if (p == nullptr)
				break;
			StopSoundMem(it.second.handle);
			p->SoundDelete(it.second.fileName);
		}
	}
	else
	{
		//システム系のサウンドなら、deleteしない
		for (auto & it : m_soundList)
		{
			StopSoundMem(it.second.handle);
		}
	}
	m_soundList.clear();
}

void Sounds::Update()
{
	if (m_isLoadEnd)
		return;

	std::string resourceName;
	if (m_isScene)
		resourceName = "SceneResource";
	else
		resourceName = "SystemResource";
	ResourceManager * p = CommonObjects::GetInstance()->FindGameObject<ResourceManager>(resourceName);
	for (auto &it : m_soundList)
	{
		if (it.second.handle >= 0)
			continue;
		if (!p->CheckHandle(it.second.fileName))
			return;
		it.second.handle = p->GetHandle(it.second.fileName);
	}
	m_isLoadEnd = true;
}

void Sounds::Load(std::string _folder, std::string _csv)
{
	std::string resourceName;
	if (m_isScene)
		resourceName = "SceneResource";
	else
		resourceName = "SystemResource";
	CsvManager * csv = CommonObjects::GetInstance()->FindGameObject<CsvManager>("CsvManager");
	csv->Read(_folder + _csv);
	int height = csv->GetHeight();
	ResourceManager * rsc = CommonObjects::GetInstance()->FindGameObject<ResourceManager>(resourceName);
	for (int i = 1; i < height; i++)
	{
		std::vector<std::string> str = csv->GetLineData(i);
		if (m_soundList.count(str[0]) != 0)
			continue;
		Sound_Info info;
		info.handle = -1;
		info.fileName = _folder + str[0] + ".mp3";
		rsc->SoundLoad(info.fileName);
		info.isLoop = atoi(str[1].c_str());
		info.volume = atoi(str[2].c_str());
		m_soundList.emplace(str[0], info);
	}
	m_isLoadEnd = false;
}

void Sounds::SoundPlay(std::string _tag)
{
	if (m_soundList.count(_tag) == 0)
		return;

	ChangeVolumeSoundMem(m_soundList[_tag].volume, m_soundList[_tag].handle);
	//ループするかどうか
	int playType = m_soundList[_tag].isLoop ? DX_PLAYTYPE_LOOP : DX_PLAYTYPE_BACK;

	PlaySoundMem(m_soundList[_tag].handle, playType);

	CheckSoundMem(m_soundList[_tag].handle);
}

void Sounds::StopSound(std::string _tag)
{
	if (m_soundList.count(_tag) == 0)
		return;
	StopSoundMem(m_soundList[_tag].handle);
}

void Sounds::AllStop()
{
	for (auto & it : m_soundList)
	{
		StopSoundMem(it.second.handle);
	}
}

void Sounds::CheckScene()
{
	//systemだと消えると困るので、あらかじめ確認をしておく
	if (GameObject::GetTag() != "CommonSound")
		m_isScene = true;
}
