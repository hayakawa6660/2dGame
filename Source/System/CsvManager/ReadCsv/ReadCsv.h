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
	/// �w�肵���t�@�C����CSV��ǂ�
	/// �v�f���͓ǂݍ��񂾂��̂ňႤ���߁A���g�ő��݊m�F���邱��
	/// </summary>
	/// <param name="_file">�t�@�C���̃p�X</param>
	void ReadFile(std::string _file);
private:
	/// <summary>
	/// �w�肵����s��ǂ�ŕԂ�
	/// </summary>
	/// <param name="_file">�����̏ꏊ��{��0</param>
	/// <param name="_lineNum">�s��</param>
	std::vector<std::string> Split(std::string _line, int &_lineNum);
};