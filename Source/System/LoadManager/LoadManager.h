#pragma once

#include "../../../Library/GameObject/GameObject.h"
#include "../../Common.h"
#include <unordered_map>
/*
���[�h��ʂ��Ǘ�����N���X�B
%�\����A
����Ȃ�%�Q�[�W�ATIPS�̏����A�\�����Ǘ�����B
*/

//#if�ƁA#else�͂ǂ����ɂ��悤���Y��ł���Ƃ���Ȃ̂ŁA
//�o����΂ǂ��炩�A�������͕ʂ̕��@�����������肢�v���܂��B
class LoadManager : public GameObject
{
public:
	enum class SPRITE_TYPE
	{
		BACK_GROUND = 0,
		LOAD_CHARA,
	};
public:
	LoadManager(SceneBase * _scene);
	~LoadManager();

private:
	void Start()override;
	void Update()override;
	void Draw()override;

private:
	/// <summary>
	/// ���ׂĂ�Handle�̃��[�h���I����Ă��邩�`�F�b�N����
	/// </summary>
	/// <return> �I����Ă�����rue</return>
	bool LoadCheck();
private:
	bool m_isLoadEnd;
	Sprite_Info sprite;
	std::unordered_map<SPRITE_TYPE, Sprite_Info> m_imageList;
public:
	void SetActive(bool _flag);
};