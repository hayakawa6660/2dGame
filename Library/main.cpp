#include <DxLib.h>
#include "App.h"
#include <EffekseerForDXLib.h>
#include "../Source/Config.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetGraphMode(Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT, 32);
	SetOutApplicationLogValidFlag(FALSE); // ���O���o���Ȃ�
#if _DEBUG // �f�o�b�O�r���h�̂Ƃ�����
	SetMainWindowText(Config::WINDOW_NAME);
	SetWindowSizeExtendRate(Config::WINDOW_EXTEND);
#endif
	SetUseDirect3DVersion(DX_DIRECT3D_9);
	ChangeWindowMode(Config::WINDOW_MODE); // Window���[�h�̏ꍇ
	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}
	SetDrawScreen(DX_SCREEN_BACK);
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	if (Effekseer_Init(8000) == -1) {
		Effkseer_End();
	}
	AppInit();
	while  (ProcessMessage() >= 0 && (CheckHitKey(KEY_INPUT_ESCAPE) == 0))
	{
		ClearDrawScreen();
		AppUpdate();
		AppDraw();
		ScreenFlip();
		if (IsExitGame())
			break;
	}
	AppRelease();

	Effkseer_End();
	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}