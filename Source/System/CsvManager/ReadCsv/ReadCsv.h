#pragma once

#include "../../../../Library/GameObject/GameObject.h"
#include <vector>
#include <fstream>
#include <unordered_map>

class ReadCsv : public GameObject {
public:
	ReadCsv(SceneBase* _scene) : GameObject(_scene) {}
	~ReadCsv() {}
	void Start()override {}
	void Update()override {}
	void Draw()override {}
	/// <summary>
	/// 指定したファイルのCSVを読む
	/// 要素数は読み込んだもので違うため、自身で相互確認すること
	/// </summary>
	/// <param name="_file">ファイルのパス</param>
	void ReadFile(std::string _file);
private:
	/// <summary>
	/// 指定した一行を読んで返す
	/// </summary>
	/// <param name="_file">文字の場所基本は0</param>
	/// <param name="_lineNum">行数</param>
	std::vector<std::string> Split(std::string _line, int &_lineNum);
};