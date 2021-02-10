#include "CompressManager.h"
#include <string>
#include <stdio.h>
#include <stdarg.h>
#include <direct.h>

CompressManager::CompressManager(GameObject * _scene) :
	GameObject(nullptr)
{
	GetCurrentDirectory(256, m_currentDirectory);
}

CompressManager::~CompressManager()
{
	AllDeleteDirectory();
}

bool CompressManager::Unzip(IShellDispatch *_pShellDispatch, WCHAR* _lpszZipPath, WCHAR* _lpszOutPath)
{
	HRESULT     hr;
	VARIANT     varOutDir, varZip, varItem, varOptions;
	Folder      *pOutFolder, *pZipFile;
	FolderItems *pZipFileItems;

	VariantInit(&varOutDir);
	varOutDir.vt = VT_BSTR;
	varOutDir.bstrVal = SysAllocString(_lpszOutPath);
	hr = _pShellDispatch->NameSpace(varOutDir, &pOutFolder);
	VariantClear(&varOutDir);
	if (hr != S_OK)
		return FALSE;

	VariantInit(&varZip);
	varZip.vt = VT_BSTR;
	varZip.bstrVal = SysAllocString(_lpszZipPath);
	hr = _pShellDispatch->NameSpace(varZip, &pZipFile);
	VariantClear(&varZip);
	if (hr != S_OK) {
		pOutFolder->Release();
		return FALSE;
	}

	hr = pZipFile->Items(&pZipFileItems);
	if (hr != S_OK) {
		pZipFile->Release();
		pOutFolder->Release();
		return FALSE;
	}

	VariantInit(&varItem);
	varItem.vt = VT_DISPATCH;
	varItem.pdispVal = pZipFileItems;
	VariantInit(&varOptions);
	varOptions.vt = VT_I4;
	//varOptions.lVal = 4;
	varOptions.lVal = FOF_SILENT;
	hr = pOutFolder->CopyHere(varItem, varOptions);
	if (hr != S_OK) {
		pZipFileItems->Release();
		pZipFile->Release();
		pOutFolder->Release();
		return FALSE;
	}

	pZipFileItems->Release();
	pZipFile->Release();
	pOutFolder->Release();

	return TRUE;
}

//==============================================================
// [概要]
//   char* から wchar_t* への変換を行う
// [引数]
//   pSrc      const char*   変換するchar型の文字列。
//   pDest     wchar_t*      変換結果のwchar_t型文字列。
//   sDestSize const size_t  pDestのサイズ
// [戻り値]
//   int  0:正常,1:異常
//==============================================================
int CompressManager::CharToWchart(const char * _pSrc, wchar_t * _pDest, const size_t _sDestSize)
{
	size_t iReturnValue;
	errno_t ret = mbstowcs_s(&iReturnValue
		, _pDest
		, _sDestSize
		, _pSrc
		, _TRUNCATE
	);
	return 0;
}

void CompressManager::AllDeleteDirectory()
{
	for (auto it : m_outFilePath)
	{
		DeleteDirectory(it.first.c_str());
	}
	m_outFilePath.clear();
}

bool CompressManager::DeleteDirectory(LPCTSTR _lpPathName)
{
	// 入力値チェック
	if (NULL == _lpPathName)
	{
		return false;
	}

	// ディレクトリ名の保存(終端を、"\0\0"にする)
	TCHAR szDirectoryPathName[_MAX_PATH];
	_tcsncpy_s(szDirectoryPathName, _MAX_PATH, _lpPathName, _TRUNCATE);
	if ('\\' == szDirectoryPathName[_tcslen(szDirectoryPathName) - 1])
	{	// 一番最後に'\'があるなら取り去る。
		szDirectoryPathName[_tcslen(szDirectoryPathName) - 1] = '\0';
	}
	szDirectoryPathName[_tcslen(szDirectoryPathName) + 1] = '\0';

	SHFILEOPSTRUCT fos;
	ZeroMemory(&fos, sizeof(SHFILEOPSTRUCT));
	fos.hwnd = NULL;
	fos.wFunc = FO_DELETE;
	fos.pFrom = szDirectoryPathName;
	fos.fFlags = FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_SILENT; // | FOF_ALLOWUNDO;
	if (SHFileOperation(&fos))
	{	// 成功すると０が、失敗すると０以外が返る。
		return false;
	}
	return true;
}

bool CompressManager::IsUnZip(std::string _outPath)
{
	//std::lock_guard<std::mutex> lock(m_mutex);	//非同期読み込み用mutex
	if (!m_outFilePath.count(_outPath))
		return false;
	return m_outFilePath[_outPath];
}

bool CompressManager::IsAllUnZip()
{
	//std::lock_guard<std::mutex> lock(m_mutex);	//非同期読み込み用mutex
	for (auto &it : m_outFilePath)
	{
		if (!it.second)
			return false;
	}
	return true;
}

bool CompressManager::UnCompress(const char *_zipPath, const char *_outPath)
{
	//std::lock_guard<std::mutex> lock(m_mutex);	//非同期読み込み用mutex

	HRESULT        hr;

	CoInitialize(NULL);
	//構築し直さないとなぜかダイアログボックスが非表示にできないので、Zip解凍の時は構築し直す
	hr = CoCreateInstance(CLSID_Shell, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pShellDispatch));
	if (FAILED(hr))
	{
		CoUninitialize();
		return false;
	}

	std::string utterlyPath = m_currentDirectory;	//このプロジェクトの絶対パス
	utterlyPath += "\\";
	//ZipFileの場所をunicodeで求める
	std::string zipPath = utterlyPath + _zipPath;
	wchar_t zipUniPath[255];	//unicode変換後のZipFilePath
	CharToWchart(zipPath.c_str(), zipUniPath, 255);
	//ZipFileの展開場所をunicodeで求める
	std::string outPath = utterlyPath + _outPath;
	wchar_t outUniPath[255];
	m_outFilePath.emplace(outPath, false);	//削除用にFilePathを保存 : 数値はロードが完了したか
	CharToWchart(outPath.c_str(), outUniPath, 255);

	if (_mkdir(outPath.c_str()) != 0)
		MessageBox(NULL, TEXT("展開先のフォルダの作成に失敗しました。\n既にフォルダが存在するか、使用できない文字が存在する可能性があります。"),
			TEXT("OK"), MB_OK);

	if (Unzip(m_pShellDispatch, zipUniPath, outUniPath))
	{	//展開完了
		m_outFilePath[outPath] = true;
		//MessageBox(NULL, TEXT("ZIPファイルを展開しました。"), TEXT("OK"), MB_OK);
	}
	else
	{
		m_outFilePath.erase(outPath);
		MessageBox(NULL, TEXT("ZIPファイルの展開に失敗しました。"), NULL, MB_ICONWARNING);
	}
	CoUninitialize();
	m_pShellDispatch->Release();

	return 0;

}