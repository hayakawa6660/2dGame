#include "ResourceManager.h"
#include <fstream>
#include <assert.h>

ResourceManager::ResourceManager(SceneBase * _scene) :
	GameObject(nullptr),
	m_currentSize(0),
	m_maxSize(0)
{
	m_resource.clear();
}

ResourceManager::~ResourceManager()
{
	AllDelete();
	m_resource.clear();
}

void ResourceManager::Start()
{
	m_maxSize = 0;
	m_currentSize = 0;
}

void ResourceManager::Update()
{
	AllLoadEndCheck();
}

void ResourceManager::Draw()
{
}

void ResourceManager::AllDelete()
{
	try {
		for (auto &it = m_resource.begin(); it != m_resource.end();)
		{
			switch (it->second.type)
			{
			case TYPE::MODEL:		it->second.handle = MV1DeleteModel(it->second.handle);	break;
			case TYPE::SOUND:		it->second.handle = DeleteSoundMem(it->second.handle);	break;
			case TYPE::TEXTURE:		it->second.handle = DeleteGraph(it->second.handle);		break;
			case TYPE::SHADER:		it->second.handle = DeleteShader(it->second.handle);	break;
			default:	break;
			}
			it = m_resource.erase(it);
		}
	}
	catch (const std::string & e)
	{
		MessageBox(NULL, ("delete�Ɏ��s���܂���\n" + e).c_str(), "ResourceManager", MB_ICONERROR | MB_OK);
	}

	//�S�������Ă��Ȃ�������G���[���o��
	if (m_resource.size() != 0)
	{
		MessageBox(NULL, ("delete���������Ă��܂���"), "ResourceManager", MB_ICONERROR | MB_OK);
	}
}

void ResourceManager::ModelDelete(std::string _file)
{
	if (m_resource.count(_file) == false)	//�����L�[�����݂��Ȃ��Ȃ�Delete���Ȃ�
		return;

	//handle���폜���A�G���[���`�F�b�N����
	int error = MV1DeleteModel(m_resource[_file].handle);
	if (error == -1)	//delete���s���Ă�����
		throw std::string(_file);
	auto itr = m_resource.find(_file);
	itr = m_resource.erase(itr);
}

void ResourceManager::SoundDelete(std::string _file)
{
	if (m_resource.count(_file) == false)	//�����L�[�����݂��Ȃ��Ȃ�Delete���Ȃ�
		return;

	//handle���폜���A�G���[���`�F�b�N����
	int error = DeleteSoundMem(m_resource[_file].handle);
	if (error == -1)	//delete���s���Ă�����
		throw std::string(_file);
	auto itr = m_resource.find(_file);
	itr = m_resource.erase(itr);
}

void ResourceManager::TextureDelete(std::string _file)
{
	if (m_resource.count(_file) == false)	//�����L�[�����݂��Ȃ��Ȃ�Delete���Ȃ�
		return;

	//handle���폜���A�G���[���`�F�b�N����
	int error = DeleteGraph(m_resource[_file].handle);
	if (error == -1)	//delete���s���Ă�����
		throw std::string(_file);

	auto itr = m_resource.find(_file);
	itr = m_resource.erase(itr);
}

void ResourceManager::ShaderDelete(std::string _file)
{
	if (m_resource.count(_file) == false)	//�����L�[�����݂��Ȃ��Ȃ�Delete���Ȃ�
		return;

	//handle���폜���A�G���[���`�F�b�N����
	int error = DeleteShader(m_resource[_file].handle);
	if (error == -1)	//delete���s���Ă�����
		throw std::string(_file);

	auto itr = m_resource.find(_file);
	itr = m_resource.erase(itr);
}

void ResourceManager::ModelLoad(std::string _file)
{
	if (m_resource.count(_file) == TRUE)	//�������ɃL�[�����݂���Ȃ烍�[�h���Ȃ�
		return;

	m_resource[_file].initialize = false;
	m_resource[_file].type = TYPE::MODEL;
	AddFileSize(_file);		//���[�h����O�Ƀt�@�C����%�ő�ʂ𑫂��Ă���
	SetUseASyncLoadFlag(TRUE);
	m_resource[_file].handle = MV1LoadModel(_file.c_str());
	SetUseASyncLoadFlag(FALSE);
}

void ResourceManager::SoundLoad(std::string _file)
{
	if (m_resource.count(_file) == TRUE)	//�������ɃL�[�����݂���Ȃ烍�[�h���Ȃ�
		return;

	m_resource[_file].initialize = false;
	m_resource[_file].type = TYPE::SOUND;
	AddFileSize(_file);		//���[�h����O�Ƀt�@�C����%�ő�ʂ𑫂��Ă���
	SetUseASyncLoadFlag(TRUE);
	m_resource[_file].handle = LoadSoundMem(_file.c_str());
	SetUseASyncLoadFlag(FALSE);
}

void ResourceManager::TextureLoad(std::string _file)
{
	if (m_resource.count(_file) == TRUE)	//�������ɃL�[�����݂���Ȃ烍�[�h���Ȃ�
		return;

	m_resource[_file].initialize = false;
	m_resource[_file].type = TYPE::TEXTURE;
	AddFileSize(_file);		//���[�h����O�Ƀt�@�C����%�ő�ʂ𑫂��Ă���
	SetUseASyncLoadFlag(TRUE);
	m_resource[_file].handle = LoadGraph(_file.c_str());
	SetUseASyncLoadFlag(FALSE);
}

void ResourceManager::ShaderLoad(std::string _file, bool _isVertex)
{
	if (m_resource.count(_file) == TRUE)	//�������ɃL�[�����݂���Ȃ烍�[�h���Ȃ�
		return;

	m_resource[_file].initialize = false;
	m_resource[_file].type = TYPE::SHADER;
	AddFileSize(_file);		//���[�h����O�Ƀt�@�C����%�ő�ʂ𑫂��Ă���
	SetUseASyncLoadFlag(TRUE);
	if (_isVertex)
		m_resource[_file].handle = LoadVertexShader(_file.c_str());
	else
		m_resource[_file].handle = LoadPixelShader(_file.c_str());

	SetUseASyncLoadFlag(FALSE);
}

bool ResourceManager::CheckHandle(std::string _file)
{
	if (m_resource[_file].initialize)	//���[�h�̃`�F�b�N����x�ł��N���A���Ă����炻�̂܂ܕԂ�
		return true;
	try
	{
		//������p�X���Q�l�Ƀ��[�h���������Ă��邩�m���߂�
		int check = CheckHandleASyncLoad(m_resource[_file].handle);
		if (check == 0)
		{
			m_currentSize += m_resource[_file].size;
			m_resource[_file].initialize = true;
			return true;
		}
		else if (check == -1)
		{		//���[�h�����s���Ă�����
			throw std::string(_file); // ��O���o
		}
	}
	catch (const std::string & e)
	{
		MessageBox(NULL, ("�ȉ���handle�̃��[�h�Ɏ��s���܂���\n" + e).c_str(), "ResourceManager", MB_ICONERROR | MB_OK);
	}

	return false;
}

int ResourceManager::GetHandle(std::string _file)
{
	try {
		if (m_resource.count(_file) == TRUE)	//�}�b�v�ɃL�[�����邩�m�F����
		{
			if (CheckHandle(_file))		//�n���h�������[�h�ł��Ă��邩���m�F����
			{
				return m_resource[_file].handle;
			}
		}
		else
		{
			throw std::string(_file); // ��O���o
		}
	}
	catch (const std::string & e)
	{
		MessageBox(NULL, ("�ȉ���Handle���쐬����Ă��܂���\n" + e).c_str(), "ResourceManager", MB_ICONERROR | MB_OK);
	}
	return -1;
}

void ResourceManager::ResetLoadSize()
{
	m_maxSize = 0;
	m_currentSize = 0;
}

bool ResourceManager::AllLoadEndCheck()
{
	for (auto & it : m_resource)
	{
		try
		{
			if (it.second.initialize)
				continue;
			int check = CheckHandleASyncLoad(it.second.handle);
			if (check == TRUE)
			{
				return false;
			}
			else if (check == FALSE)
			{
				it.second.initialize = true;
				m_currentSize += it.second.size;
			}
			else if (check == -1)
			{
				throw std::string(it.first); // ��O���o
			}
		}
		catch (const std::string & e)
		{
			MessageBox(NULL, ("�ȉ��̃��f���͂���܂���\n" + e).c_str(), "ResourceManager", MB_ICONERROR | MB_OK);
		}
	}
	return true;
}


void ResourceManager::AddFileSize(std::string _file)
{
	std::ifstream ifs(_file, std::ios::binary);
	ifs.seekg(0, std::ios::end);
	int eofpos = (int)ifs.tellg();
	ifs.clear();
	ifs.seekg(0, std::ios::beg);
	int begpos = (int)ifs.tellg();
	m_resource[_file].size = eofpos - begpos;
	m_maxSize += m_resource[_file].size;
	ifs.close();
}