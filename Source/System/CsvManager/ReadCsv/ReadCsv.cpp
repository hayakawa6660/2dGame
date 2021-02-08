#include "ReadCsv.h"
#include "../../../../Library/Common/commonObjects.h"
#include "../CsvManager.h"
#include "../CsvData/CsvData.h"

void ReadCsv::ReadFile(std::string _file)
{
	std::string str = _file;
	std::ifstream ifs(str);
	if (ifs.fail())
	{
		MessageBox(NULL, ("CSV�t�@�C�����ǂݍ��߂܂���ł���\n" + _file).c_str(), "ReadFile", MB_ICONERROR | MB_OK);
	}
	std::string record;
	std::vector<std::vector<std::string>> rec;
	int size = 0;
	int line = 0;
	while (getline(ifs, record))
	{
		if (record[0] == '/')
			continue;
		size++;
		std::vector<std::string> tmp = Split(record, line);
		rec.emplace_back(tmp);
	}
	CsvData * p = CommonObjects::GetInstance()->FindGameObject<CsvData>("CsvData");
	if (p == nullptr)
		MessageBox(NULL, "CsvData�̃C���X�^���X������܂���", "ReadFile", MB_ICONERROR | MB_OK);

	p->PushCsv(rec, size, line);
	ifs.close();
}

std::vector<std::string> ReadCsv::Split(std::string _line, int &_lineNum)
{
	std::vector<std::string> str;
	str.clear();
	//�����̋�؂肪,�Ȃ̂ŁA�I����,�Ɏw�肷��
	size_t pos = _line.find(',');

	while (pos != std::string::npos)
	{
		//�����̊J�n�ʒu����,�܂ł�return����l�Ɋi�[����
		std::string a = _line.substr(0, pos);
		str.push_back(a);
		//�J�n�ʒu��,�̎��̏ꏊ�ɍX�V����
		_line = _line.substr(pos + 1);
		//���̏I���n�_��,
		pos = _line.find(',');
		_lineNum++;
	}
	str.push_back(_line);
	return str;
}