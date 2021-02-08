#include "MyEffekseer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////
//MyEffekseer
//////////////////////////////////////////////////////////////////////////////////////////////////
MyEffekseer::MyEffekseer(SceneBase * _scene) :
	GameObject(nullptr)
{
	//SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
	//Effekseer_SetGraphicsDeviceLostCallbackFunctions();
	//Effekseer::Manager* manager = GetEffekseer3DManager();
	//manager->SetEffectLoader(new EffeksserLoader);

	Effekseer_InitDistortion();
	m_playingEffectHandle.clear();
	m_effectData.clear();
}

MyEffekseer::~MyEffekseer()
{

}

void MyEffekseer::Update()
{
	if (m_firstDrawImage <= 0) {
		m_firstDrawImage = LoadGraph("data\\Texture\\Fade.png");
		assert(m_firstDrawImage >= 0);
	}

	AutoEffectDelete();
	UpdateEffekseer3D();
}

void MyEffekseer::Draw()
{
	Effekseer_Sync3DSetting();
	DrawGraph(0, 0, m_firstDrawImage,true);
	
	DrawEffekseer3D_Begin();
	DrawEffekseer3D();
	DrawEffekseer3D_End();
}

void MyEffekseer::Release()
{	
	for (auto it = m_playingEffectHandle.begin(); it != m_playingEffectHandle.end();) {
		StopEffekseer3DEffect(*it);
		it = m_playingEffectHandle.erase(it);
	}

	for (auto it = m_effectData.begin(); it != m_effectData.end();) {
		DeleteEffekseerEffect(it->second);
		it = m_effectData.erase(it);
	}
}

bool MyEffekseer::IsEffectPlaying(int _handle)
{
	return IsEffekseer3DEffectPlaying(_handle) == 0;
}

void MyEffekseer::Load(const char * _fileName)
{
	if (_fileName == "")
		return;
	if (m_effectData.count(_fileName) != 0)
		return;

	std::string path("data/Effekseer/");
	path += _fileName;
	path += ".efk";
	
	int handle = LoadEffekseerEffect(path.c_str());	

	assert(handle != -1);
	m_effectData.emplace(_fileName, handle);
}

int MyEffekseer::PlayEffect(const std::string & _key, const VECTOR& _pos, const float& _scale)
{
	int handle = -1;
	if (m_effectData.count(_key) == 0)
		return -1;

	handle = PlayEffekseer3DEffect(m_effectData[_key]);
	if (_pos.x != 0.f && _pos.y != 0.f && _pos.z != 0.f)
		SetPosPlayingEffekseer3DEffect(handle, _pos.x, _pos.y, _pos.z);
	if (_scale != 0.f)
		SetScalePlayingEffekseer3DEffect(handle, _scale, _scale, _scale);
	m_playingEffectHandle.emplace_back(handle);

	return handle;
}

void MyEffekseer::AutoEffectDelete()
{
	for (auto it = m_playingEffectHandle.begin(); it != m_playingEffectHandle.end();) {
		if (!IsEffectPlaying(*it)) {//çƒê∂Ç≥ÇÍÇƒÇ¢Ç»Ç¢
			StopEffect(*it);
			it = m_playingEffectHandle.erase(it);
		}
		else {
			it++;
		}
	}
}

void MyEffekseer::SetPosition(const int & _handle, const VECTOR & _pos)
{
	SetPosPlayingEffekseer3DEffect(_handle, _pos.x, _pos.y, _pos.z);
}

void MyEffekseer::SetRotation(const int & _handle, const VECTOR & _rot)
{
	SetRotationPlayingEffekseer3DEffect(_handle, _rot.x, _rot.y, _rot.z);
}

void MyEffekseer::SetScale(const int & _handle, const VECTOR & _scale)
{
	SetScalePlayingEffekseer3DEffect(_handle, _scale.x, _scale.y, _scale.z);
}

float MyEffekseer::GetSpeed(int _handle)
{
	return GetSpeedPlayingEffekseer3DEffect(_handle);
}

void MyEffekseer::SetSpeed(int _handle, const float & _speed)
{
	SetSpeedPlayingEffekseer3DEffect(_handle, _speed);
}

int MyEffekseer::DestroyEffect(const int _handle)
{
	return DeleteEffekseerEffect(_handle);
}

int MyEffekseer::StopEffect(const int _handle)
{
	return StopEffekseer3DEffect(_handle);
}

Effekseer::Matrix43 MyEffekseer::DxLib_MATRIXToEffekseer_Matrix43Conversion(const MATRIX & _m)
{
	Effekseer::Matrix43 returnEfkMatrix43;
	returnEfkMatrix43.Indentity();
	//çsóÒÇ4x4Ç©ÇÁ4x3Ç…ïœä∑
	for (int j = 0; j < 4; ++j) {
		for (int i = 0; i < 3; ++i) {
			returnEfkMatrix43.Value[j][i] = _m.m[j][i];
		}
	}
	return returnEfkMatrix43;
}
//Ç±ÇÃä÷êîÇåƒÇ‘Ç∆Ç´ÇÕëºÇÃSetånä÷êîÇégÇ¶Ç»Ç¢
void MyEffekseer::SetMatrix(int _handle,const MATRIX& _m)
{
	Effekseer::Manager* manager = GetEffekseer3DManager();
	Effekseer::Matrix43 m = DxLib_MATRIXToEffekseer_Matrix43Conversion(_m);
	manager->SetMatrix(_handle, m);
}

int MyEffekseer::SecureInstance()
{
	Effekseer::Manager* manager = GetEffekseer3DManager();
	return 8000 - manager->GetRestInstancesCount();
}

