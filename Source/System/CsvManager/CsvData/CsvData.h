#pragma once

#include "../../../../Library/GameObject/GameObject.h"
#include <unordered_map>
#include <fstream>

class CsvData : public GameObject {
public:
	CsvData(SceneBase* _scene);
	~CsvData();
private:
	std::vector<std::vector<std::string>> m_csvList;
	int m_lineHeight;
	int m_lineWidht;
public:

	/// <summary>
	/// Csv�̏���ۑ�����
	/// </summary>
	/// <param name="_value">�S�Ă̗v�f�̃��X�g</param>
	/// <param name="_height">�s��</param>
	/// <param name="_widht">�v�f��</param>
	void PushCsv(std::vector<std::vector<std::string>> _value, int _height, int _widht);

	void SetSize(int _height) { m_lineHeight = _height; }

	//Csv�̏c�̗v�f�����擾����
	int GetHeight()const { return m_lineHeight; }
	//Csv�̉��̗v�f�����擾����
	int GetWidht()const { return m_lineWidht; }
	
	const std::vector<std::vector<std::string>> &GetAllData()	{ return m_csvList; }
	const std::vector<std::string>	&GetLineData(int _height)	{ return m_csvList[_height - 1]; }
	const std::string &GetData(int _height, int _widht)			{ return m_csvList[_height - 1][_widht - 1]; }
};