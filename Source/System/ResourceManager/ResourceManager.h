#pragma once

#include "Library/GameObject/GameObject.h"
#include <map>
#include <functional>

class ResourceManager : public GameObject {
public:
	ResourceManager(SceneBase* _scene);
	~ResourceManager();
private:
	void Start()override;
	void Update()override;
public:
	void AllDelete();
	/// <summary>
	/// �w�肵���t�@�C���̏ꏊ����f�[�^�����폜����
	/// </summary>
	/// <param name="_file">�t�@�C���̃p�X</param>
	void ModelDelete(std::string _file);
	void SoundDelete(std::string _file);
	void TextureDelete(std::string _file);
	void ShaderDelete(std::string _file);
	/// <summary>
	/// �w�肵���t�@�C���̏ꏊ���烂�f�������[�h����
	/// </summary>
	/// <param name="_file">�t�@�C���̃p�X</param>
	void ModelLoad(std::string _file, std::function<void()> _func = nullptr);

	/// <summary>
	/// �w�肵���t�@�C���̏ꏊ����T�E���h�����[�h����
	/// </summary>
	/// <param name="_file">�t�@�C���̃p�X</param>
	void SoundLoad(std::string _file, std::function<void()> _func = nullptr);

	/// <summary>
	/// �w�肵���t�@�C���̏ꏊ����e�N�X�`���[�����[�h����
	/// </summary>
	/// <param name="_file">�t�@�C���̃p�X</param>
	void TextureLoad(std::string _file, std::function<void()> _func = nullptr);
	/// <summary>
	/// �w�肵���t�@�C���̏ꏊ����e�N�X�`���[�����[�h����
	/// </summary>
	/// <param name="_file">�t�@�C���̃p�X</param>
	void ShaderLoad(std::string _file, bool _isVertex, std::function<void()> _func = nullptr);

	/// <summary>
	/// �w�肵�����f�������[�h�I����Ă��邩�m�F����
	/// </summary>
	/// <param name="_file">�t�@�C���̃p�X</param>
	/// <returns>�������Ă�����TRUE</returns>
	bool CheckHandle(std::string _file);


	/// <summary>
	/// ���ׂẴ��f�������[�h�������Ă��邩�m�F����
	/// </summary>
	/// <returns>�S�Ċ������Ă�����TRUE</returns>
	void AllLoadEndCheck();


	/// <summary>
	/// �w�肵�����f���A�e�N�X�`���[�A�T�E���h�̂����ꂩ���擾����
	/// </summary>
	/// <param name="_file">�t�@�C���̃p�X</param>
	/// <returns>�w�肵�����f���̃n���h��</returns>
	int GetHandle(std::string _file);


	/// <summary>
	/// ���\�[�X�̃T�C�Y�����Z�b�g����
	/// </summary>
	void ResetLoadSize();


private:
	/// <summary>
	/// ���[�h�����t�@�C���̃T�C�Y�𑪂�Amax�ɉ��Z����
	/// </summary>
	/// <param name="obj">�t�@�C���̃p�X</param>
	void AddFileSize(std::string _file);
private:
	enum class TYPE
	{
		MODEL = 0,
		SOUND,
		TEXTURE,
		SHADER,
	};
private:
	unsigned int m_maxSize;
	unsigned int m_currentSize;

	struct Resource_Info {
		int handle;
		int size;
		bool initialize;
		TYPE type;
		std::function<void()> onCompleted;
	};
	std::map<std::string, Resource_Info> m_resource;
	bool m_isLoadEnd;
public:
	unsigned int GetMaxSize()const { return m_maxSize; }
	unsigned int GetCurrentSize()const { return m_currentSize; }
	bool IsLoadEnd()const { return m_isLoadEnd; }
};