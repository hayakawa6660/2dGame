#include "Render2D.h"
#include <algorithm>

Render2D::Render2D() :
	m_sort(false)
{
	m_spriteList.clear();
	m_spriteName.clear();
	m_drawList.clear();
}

Render2D::~Render2D()
{
	m_spriteList.clear();
	m_spriteName.clear();
	m_drawList.clear();
}

void Render2D::Update()
{
	if (m_sort)
	{
		m_drawList.clear();
		m_drawList = m_spriteList; // Listを全コピー
		std::sort(m_drawList.begin(), m_drawList.end(), Comp);
		m_sort = false;
	}
}

void Render2D::Draw()
{
	for (auto & it : m_drawList)
		it.second.function();
	for (auto & it : m_textList)
		it.second();
}

bool Render2D::AddTexture(const std::string & _name, Sprite_Info & _sprite, const std::function<void()>& _func)
{
	//要素が存在するならreturn
	if (VectorFind(m_spriteName, std::hash<std::string>()(_name)) != m_spriteName.end())
		return false;
	//存在しなかったら要素を追加する。
	std::pair<size_t, Texture_Info> info;
	info.first = std::hash<std::string>()(_name);
	info.second.sprite = _sprite;
	info.second.function = _func;
	m_spriteList.emplace_back(info);
	m_spriteName.emplace_back(info.first);		//検索用vector
	m_sort = true;
	return false;
}

bool Render2D::RemoveTexture(const std::string & _name)
{
	size_t hash = std::hash<std::string>()(_name);
	auto find = VectorFind(m_spriteName, hash);
	//キーが存在しなかったらreturn
	if (find == m_spriteName.end())
		return false;
	//要素を消去
	m_spriteName.erase(find);
	for (auto & it = m_spriteList.begin(); it != m_spriteList.end();)
	{
		//一つのキーは一つしか存在しないので、一致したらerase後即座に抜ける。
		if (it->first == hash)
		{
			m_spriteList.erase(it);
			m_sort = true;
			return true;
		}
		else {
			it++;
		}
	}
	return false;
}

bool Render2D::AddText(const std::string & _name, const std::function<void()>& _func)
{
	std::pair<size_t, std::function<void()>> info;
	info.first = std::hash<std::string>()(_name);
	info.second = _func;
	m_textList.emplace_back(info);
	m_textName.emplace_back(info.first);
	return false;
}

bool Render2D::RemoveText(const std::string & _name)
{
	size_t hash = std::hash<std::string>()(_name);
	auto find = VectorFind(m_textName, hash);
	if (find == m_textName.end())
		return false;
	m_textName.erase(find);
	for (auto & it = m_textList.begin(); it != m_textList.end();)
	{
		//textはキーが複数ある場合があるので、全て消すため全部回す。
		if (it->first == hash)
		{
			it = m_textList.erase(it);
			m_sort = true;
		}
		else
		{
			it++;
		}
	}
	return false;
}

bool Render2D::Comp(const std::pair<size_t, Texture_Info>& _o1, const std::pair<size_t, Texture_Info>& _o2)
{
	return _o1.second.sprite.position.z < _o2.second.sprite.position.z;
}

const std::vector<size_t>::iterator Render2D::VectorFind(std::vector<size_t> &_vec, const size_t & _size)
{
	return std::find(_vec.begin(), _vec.end(), _size);
}