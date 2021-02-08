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
	for (auto it : m_outFilePath)
	{
		DeleteDirectory(it.first.c_str());
	}
	m_outFilePath.clear();
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
// [�T�v]
//   char* ���� wchar_t* �ւ̕ϊ����s��
// [����]
//   pSrc      const char*   �ϊ�����char�^�̕�����B
//   pDest     wchar_t*      �ϊ����ʂ�wchar_t�^������B
//   sDestSize const size_t  pDest�̃T�C�Y
// [�߂�l]
//   int  0:����,1:�ُ�
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

bool CompressManager::DeleteDirectory(LPCTSTR _lpPathName)
{
	// ���͒l�`�F�b�N
	if (NULL == _lpPathName)
	{
		return false;
	}

	// �f�B���N�g�����̕ۑ�(�I�[���A"\0\0"�ɂ���)
	TCHAR szDirectoryPathName[_MAX_PATH];
	_tcsncpy_s(szDirectoryPathName, _MAX_PATH, _lpPathName, _TRUNCATE);
	if ('\\' == szDirectoryPathName[_tcslen(szDirectoryPathName) - 1])
	{	// ��ԍŌ��'\'������Ȃ��苎��B
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
	{	// ��������ƂO���A���s����ƂO�ȊO���Ԃ�B
		return false;
	}
	return true;
}

bool CompressManager::IsUnZip(std::string _outPath)
{
	//std::lock_guard<std::mutex> lock(m_mutex);	//�񓯊��ǂݍ��ݗpmutex
	if (!m_outFilePath.count(_outPath))
		return false;
	return m_outFilePath[_outPath];
}

bool CompressManager::IsAllUnZip()
{
	//std::lock_guard<std::mutex> lock(m_mutex);	//�񓯊��ǂݍ��ݗpmutex
	for (auto &it : m_outFilePath)
	{
		if (!it.second)
			return false;
	}
	return true;
}

bool CompressManager::UnCompress(const char *_zipPath, const char *_outPath)
{
	//std::lock_guard<std::mutex> lock(m_mutex);	//�񓯊��ǂݍ��ݗpmutex

	HRESULT        hr;

	CoInitialize(NULL);
	//�\�z�������Ȃ��ƂȂ����_�C�A���O�{�b�N�X����\���ɂł��Ȃ��̂ŁAZip�𓀂̎��͍\�z������
	hr = CoCreateInstance(CLSID_Shell, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pShellDispatch));
	if (FAILED(hr))
	{
		CoUninitialize();
		return false;
	}

	std::string utterlyPath = m_currentDirectory;	//���̃v���W�F�N�g�̐�΃p�X
	utterlyPath += "\\";
	//ZipFile�̏ꏊ��unicode�ŋ��߂�
	std::string zipPath = utterlyPath + _zipPath;
	wchar_t zipUniPath[255];	//unicode�ϊ����ZipFilePath
	CharToWchart(zipPath.c_str(), zipUniPath, 255);
	//ZipFile�̓W�J�ꏊ��unicode�ŋ��߂�
	std::string outPath = utterlyPath + _outPath;
	wchar_t outUniPath[255];
	m_outFilePath.emplace(outPath, false);	//�폜�p��FilePath��ۑ� : ���l�̓��[�h������������
	CharToWchart(outPath.c_str(), outUniPath, 255);

	if (_mkdir(outPath.c_str()) != 0)
		MessageBox(NULL, TEXT("�W�J��̃t�H���_�̍쐬�Ɏ��s���܂����B\n���Ƀt�H���_�����݂��邩�A�g�p�ł��Ȃ����������݂���\��������܂��B"),
			TEXT("OK"), MB_OK);

	if (Unzip(m_pShellDispatch, zipUniPath, outUniPath))
	{	//�W�J����
		m_outFilePath[outPath] = true;
		//MessageBox(NULL, TEXT("ZIP�t�@�C����W�J���܂����B"), TEXT("OK"), MB_OK);
	}
	else
	{
		m_outFilePath.erase(outPath);
		MessageBox(NULL, TEXT("ZIP�t�@�C���̓W�J�Ɏ��s���܂����B"), NULL, MB_ICONWARNING);
	}
	CoUninitialize();
	m_pShellDispatch->Release();

	return 0;

}