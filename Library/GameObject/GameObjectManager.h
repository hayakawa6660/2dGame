#pragma once

#include "GameObject.h"

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();

	void Start();
	void Update();
	void ShadowDraw();
	void MirrorDraw();
	void Draw();


	/// <summary>
	/// �I�u�W�F�N�g�̊Ǘ����J�n����
	/// </summary>
	/// <param name="obj">�o�^����GameObject</param>
	void PushGameObject(GameObject* obj);

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	std::list<GameObject*> GetAllObjects() const;

	/// 	/// <summary>
	/// �^�O����v����GameObject���擾����
	/// </summary>
	/// <param name="tag">�^�O</param>
	/// <returns>GameObject�̃C���X�^���X</returns>
	GameObject* FindGameObject(std::string tag) const;

	/// <summary>
	/// tag����v���邷�ׂĂ�GameObject�𒊏o����
	/// </summary>
	/// <param name="tag">�]������^�O</param>
	/// <returns>�^�O����v����GameObject�̃C���X�^���X</returns>
	std::list<GameObject*> FindGameObjects(std::string tag) const;

	/// <summary>
	/// GameObject���폜����
	/// </summary>
	/// <param name="obj">GameObject�̃C���X�^���X</param>
	void DeleteGameObject(GameObject* obj);

	/// <summary>
	/// �S�Ă�GameObject���폜����
	/// </summary>
	void DeleteAllGameObject();

	/// <summary>
	/// �`��̃v���C�I���e�B��ݒ肷��
	/// ���l�����Ȃ����ɕ`�悳���̂ŁA�Q�c�ł͉��ɕ\�������
	/// �Q�c�Ŏ�O�ɕ\�����������A�R�c�Ō�ɕ`�悵�������́A�l����������
	/// �v���C�I���e�B���������̂̏��Ԃ͕ۏ؂���Ȃ�
	/// �v���C�I���e�B�̃f�t�H���g��100�ł�
	/// </summary>
	/// <param name="obj">�v���C�I���e�B��ݒ肷��I�u�W�F�N�g</param>
	/// <param name="order">�`��v���C�I���e�B</param>
	void SetDrawOrder(GameObject* _obj, int _order);
	void SetUpdateOrder(GameObject* _obj, int _order);
private:
	struct NODE {
		int drawOrder;
		int upOrder;
		bool initialized;
		GameObject* object;
		NODE() : drawOrder(100), upOrder(100), object(nullptr), initialized(false) {}
	};
	std::list<NODE> m_objects;			// �����ŊǗ����Ă���GameObject���X�g
	std::list<NODE> m_drawObjects;		// �`��p��GameObject���X�g
	bool m_drawSort;
	bool m_upSort;

	void DeleteFromDrawObjects(GameObject* obj);
	static bool DrawComp(const NODE& o1, const NODE& o2);
	static bool UpComp(const NODE& o1, const NODE& o2);
};