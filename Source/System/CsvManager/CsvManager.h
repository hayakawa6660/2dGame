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
	/// 直近で読み込んだCsvの要素、行数を取得する
	/// </summary>
	/// <returns>読み込んだ行と要素全て</returns>
	void Read(std::string _file);

	/// <summary>
	/// 直近で読み込んだCsvの要素、行数を取得する
	/// </summary>
	/// <returns>読み込んだ行と要素全て</returns>
	const std::vector<std::vector<std::string>> &GetAllData();
	
	/// <summary>
	/// 行数を指定して、その行数の要素を取得する
	/// </summary>
	/// <param name="_height">読み込んだCsvの行数</param>
	/// <returns>指定した行の要素全て</returns>
	const std::vector<std::string> &GetLineData(int _height);

	/// <summary>
	/// 行数と要素の場所指定して、その行数の要素を取得する
	/// </summary>
	/// <param name="_height">読み込んだCsvの行数</param>
	/// <param name="_widht">読み込んだCsvの要素番号</param>
	/// <returns>指定された要素</returns>
	const std::string &GetData(int _height, int _widht);

	/// <summary>
	/// 直近で読み込んだCsvの行数を取得する
	/// </summary>
	/// <returns>行数</returns>
	int GetHeight();

	/// <summary>
	/// 直近で読み込んだCsvの要素を取得する
	/// </summary>
	/// <returns>要素数</returns>
	int GetWidht();

	ReadCsv * GetRead()const { return m_read; }
	CsvData * GetData()const { return m_data; }
};