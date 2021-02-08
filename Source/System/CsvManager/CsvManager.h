#pragma once

#include "Library/GameObject/GameObject.h"

#include <vector>

class ReadCsv;
class CsvData;

class CsvManager : public GameObject
{
public:
	CsvManager(SceneBase * _scene);
	~CsvManager();
private:
	ReadCsv * m_read;
	CsvData * m_data;
public:
	/// <summary>
	/// ���߂œǂݍ���Csv�̗v�f�A�s�����擾����
	/// </summary>
	/// <returns>�ǂݍ��񂾍s�Ɨv�f�S��</returns>
	void Read(std::string _file);

	/// <summary>
	/// ���߂œǂݍ���Csv�̗v�f�A�s�����擾����
	/// </summary>
	/// <returns>�ǂݍ��񂾍s�Ɨv�f�S��</returns>
	const std::vector<std::vector<std::string>> &GetAllData();
	
	/// <summary>
	/// �s�����w�肵�āA���̍s���̗v�f���擾����
	/// </summary>
	/// <param name="_height">�ǂݍ���Csv�̍s��</param>
	/// <returns>�w�肵���s�̗v�f�S��</returns>
	const std::vector<std::string> &GetLineData(int _height);

	/// <summary>
	/// �s���Ɨv�f�̏ꏊ�w�肵�āA���̍s���̗v�f���擾����
	/// </summary>
	/// <param name="_height">�ǂݍ���Csv�̍s��</param>
	/// <param name="_widht">�ǂݍ���Csv�̗v�f�ԍ�</param>
	/// <returns>�w�肳�ꂽ�v�f</returns>
	const std::string &GetData(int _height, int _widht);

	/// <summary>
	/// ���߂œǂݍ���Csv�̍s�����擾����
	/// </summary>
	/// <returns>�s��</returns>
	int GetHeight();

	/// <summary>
	/// ���߂œǂݍ���Csv�̗v�f���擾����
	/// </summary>
	/// <returns>�v�f��</returns>
	int GetWidht();

	ReadCsv * GetRead()const { return m_read; }
	CsvData * GetData()const { return m_data; }
};