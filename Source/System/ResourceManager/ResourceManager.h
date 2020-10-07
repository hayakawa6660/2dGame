#pragma once

#include "../../../Library/GameObject/GameObject.h"
#include <map>

class ResourceManager : public GameObject {
public:
	ResourceManager(SceneBase* _scene);
	~ResourceManager();
private:
	void Start()override;
	void Update()override;
	void Draw()override;
public:
	void AllDelete();
	/// <summary>
	/// 指定したファイルの場所からデータをを削除する
	/// </summary>
	/// <param name="_file">ファイルのパス</param>
	void ModelDelete(std::string _file);
	void SoundDelete(std::string _file);
	void TextureDelete(std::string _file);

	/// <summary>
	/// 指定したファイルの場所からモデルをロードする
	/// </summary>
	/// <param name="_file">ファイルのパス</param>
	void ModelLoad(std::string _file);

	/// <summary>
	/// 指定したファイルの場所からサウンドをロードする
	/// </summary>
	/// <param name="_file">ファイルのパス</param>
	void SoundLoad(std::string _file);

	/// <summary>
	/// 指定したファイルの場所からテクスチャーをロードする
	/// </summary>
	/// <param name="_file">ファイルのパス</param>
	void TextureLoad(std::string _file);

	/// <summary>
	/// 指定したモデルがロード終わっているか確認する
	/// </summary>
	/// <param name="_file">ファイルのパス</param>
	/// <returns>完了していたらTRUE</returns>
	bool CheckHandle(std::string _file);


	/// <summary>
	/// すべてのモデルがロード完了しているか確認する
	/// </summary>
	/// <returns>全て完了していたらTRUE</returns>
	bool AllLoadEndCheck();


	/// <summary>
	/// 指定したモデル、テクスチャー、サウンドのいずれかを取得する
	/// </summary>
	/// <param name="_file">ファイルのパス</param>
	/// <returns>指定したモデルのハンドル</returns>
	int GetHandle(std::string _file);


	/// <summary>
	/// リソースのサイズをリセットする
	/// </summary>
	void ResetLoadSize();


private:
	/// <summary>
	/// ロードしたファイルのサイズを測り、maxに加算する
	/// </summary>
	/// <param name="obj">ファイルのパス</param>
	void AddFileSize(std::string _file);
private:
	enum class TYPE
	{
		MODEL = 0,
		SOUND,
		TEXTURE,
	};
private:
	unsigned int m_maxSize;
	unsigned int m_currentSize;

	struct Resource_Info {
		int handle;
		int size;
		bool initialize;
		TYPE type;
	};
	std::map<std::string, Resource_Info> m_resource;
public:
	unsigned int GetMaxSize()const { return m_maxSize; }
	unsigned int GetCurrentSize()const { return m_currentSize; }
};