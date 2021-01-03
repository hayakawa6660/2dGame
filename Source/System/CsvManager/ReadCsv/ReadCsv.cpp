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
		MessageBox(NULL, ("CSVファイルが読み込めませんでした\n" + _file).c_str(), "ReadFile", MB_ICONERROR | MB_OK);
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
		MessageBox(NULL, "CsvDataのインスタンスがありません", "ReadFile", MB_ICONERROR | MB_OK);

	p->PushCsv(rec, size, line);
	ifs.close();
}

std::vector<std::string> ReadCsv::Split(std::string _line, int &_lineNum)
{
	std::vector<std::string> str;
	str.clear();
	//文字の区切りが,なので、終わりを,に指定する
	size_t pos = _line.find(',');

	while (pos != std::string::npos)
	{
		//文字の開始位置から,までをreturnする値に格納する
		std::string a = _line.substr(0, pos);
		str.push_back(a);
		//開始位置を,の次の場所に更新する
		_line = _line.substr(pos + 1);
		//次の終了地点も,
		pos = _line.find(',');
		_lineNum++;
	}
	str.push_back(_line);
	return str;
}