#include "CsvData.h"

CsvData::CsvData(SceneBase * _scene) :
	GameObject(_scene),
	m_lineHeight(0),
	m_lineWidht(0)
{
	m_csvList.clear();
}

CsvData::~CsvData()
{
}

void CsvData::PushCsv(std::vector<std::vector<std::string>> _value, int _size, int _line)
{
	m_csvList = _value;
	m_lineHeight = _size;
	m_lineWidht = _line;
}
