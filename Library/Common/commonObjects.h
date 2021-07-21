#pragma once
#include "../GameObject/GameObjectManager.h"
/// <summary>
/// �V�[����؂�ւ��Ă������Ȃ�GameObject���Ǘ����܂��B
/// </summary>
class CommonObjects {
private:
	CommonObjects() {}
public:
	static CommonObjects* GetInstance();
	void Start();
	void Update();
	void Release();
private:
	GameObjectManager objectManager;
public:

	/// <summary>
	/// �`��̃v���C�I���e�B��ݒ肷��
	/// ���l�����Ȃ����ɕ`�悳���̂ŁA��O�ɕ\�����������͒l����������
	/// �v���C�I���e�B���������̂̏��Ԃ͕ۏ؂���Ȃ�
	/// �v���C�I���e�B�̃f�t�H���g��100�ł�
	/// </summary>
	/// <param name="obj">�v���C�I���e�B��ݒ肷��I�u�W�F�N�g</param>
	/// <param name="order">�`��v���C�I���e�B</param>
	inline void SetDrawOrder(GameObject * _obj, int _order)
	{
		objectManager.SetDrawOrder(_obj, _order);
	}

	/// <summary>
	/// GameObject�𐶐�����
	/// �����Ő�������ƁAUpdate,Draw���Ă΂��悤�ɂȂ�
	/// </summary>
	template <class C>
	C* CreateGameObject(std::string _tag) {
		C* obj = new C(nullptr);
		obj->SetTag(_tag);
		objectManager.PushGameObject(obj);
		return obj;
	};

	/// <summary>
	/// tag���w�肵�āAGameObject����������
	/// �S�I�u�W�F�N�g����Atag�������I�u�W�F�N�g��Ԃ��܂�
	/// �������A�ŏ��Ɍ����������̂�����Ԃ��܂�
	/// ������Ȃ���΁Anullptr��Ԃ��܂�
	/// </summary>
	template <class C>
	C* FindGameObject(std::string _tag) {
		GameObject* obj = objectManager.FindGameObject(_tag);
		return dynamic_cast<C*>(obj);
	};

	/// <summary>
	/// GameObject���폜����
	/// </summary>
	/// <param name="obj">GameObject�̃C���X�^���X</param>
	inline void DeleteGameObject(GameObject * obj)
	{
		objectManager.DeleteGameObject(obj);
	}
};