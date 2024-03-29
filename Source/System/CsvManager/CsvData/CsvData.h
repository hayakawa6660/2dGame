#pragma once

#include "Library/GameObject/GameObject.h"
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
	/// Csvの情報を保存する
	/// </summary>
	/// <param name="_value">全ての要素のリスト</param>
	/// <param name="_height">行数</param>
	/// <param name="_widht">要素数</param>
	void PushCsv(std::vector<std::vector<std::string>> _value, int _height, int _widht);

	void SetSize(int _height) { m_lineHeight = _height; }

	//Csvの縦の要素数を取得する
	int GetHeight()const { return m_lineHeight; }
	//Csvの横の要素数を取得する
	int GetWidht()const { return m_lineWidht; }
	
	const std::vector<std::vector<std::string>> &GetAllData()	{ return m_csvList; }
	const std::vector<std::string>	&GetLineData(int _height)	{ return m_csvList[_height - 1]; }
	const std::string &GetData(int _height, int _widht)			{ return m_csvList[_height - 1][_widht - 1]; }
};