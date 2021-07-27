#pragma once

#include "Source/Common.h"
#include <vector>
#include <functional>
#include <string>

class Render2D
{
public:
	Render2D();
	~Render2D();
	void Update();
	void Draw();
private:
	struct Texture_Info
	{
		Sprite_Info sprite;
		std::function<void()> function;
	};
	std::vector<std::pair<size_t, Texture_Info>> m_spriteList;				//�摜���
	std::vector<std::pair<size_t, Texture_Info>> m_drawList;
	std::vector<size_t> m_spriteName;
	std::vector<std::pair<size_t, std::function<void()>>> m_textList;		//�e�L�X�g���
	std::vector<size_t> m_textName;
	bool m_sort;
public:
	bool AddTexture(const std::string &_name, Sprite_Info &_sprite, const std::function<void()> &_func);
	bool RemoveTexture(const std::string&_name);
	bool AddText(const std::string &_name, const std::function<void()>& _func);
	bool RemoveText(const std::string &_name);
private:
	static bool Comp(const std::pair<size_t, Texture_Info>& _o1, const std::pair<size_t, Texture_Info>& _o2);
	//�v�f������΁Astd::vector<size_t>��end�ȊO�̗v�f�̒l���Ԃ�B
	//�v�f���������std::vector<size_t>��end���Ԃ�
	const std::vector<size_t>::iterator VectorFind(std::vector<size_t> &_vec, const size_t &_size);
};