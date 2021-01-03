#include "CsvManager.h"
#include "ReadCsv/ReadCsv.h"
#include "CsvData/CsvData.h"

#include "Library/Common/commonObjects.h"

CsvManager::CsvManager(SceneBase * _scene) :
	GameObject(nullptr)
{
	m_read = CommonObjects::GetInstance()->CreateGameObject<ReadCsv>("ReadCsv");
	m_data = CommonObjects::GetInstance()->CreateGameObject<CsvData>("CsvData");

}

CsvManager::~CsvManager()
{
}

void CsvManager::Read(std::string _file)
{
	m_read->ReadFile(_file);
}

const std::vector<std::vector<std::string>> &CsvManager::GetAllData()
{
	return m_data->GetAllData();
}

const std::vector<std::string> &CsvManager::GetLineData(int _height)
{
	return m_data->GetLineData(_height);
}

const std::string &CsvManager::GetData(int _height, int _widht)
{
	return m_data->GetData(_height, _widht);
}

int CsvManager::GetHeight()
{
	return m_data->GetHeight();
}

int CsvManager::GetWidht()
{
	return m_data->GetWidht();
}
