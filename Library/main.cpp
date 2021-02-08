#include <DxLib.h>
#include "App.h"
#include <EffekseerForDXLib.h>
#include "Source/Config.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetGraphMode(Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT, 32);
	SetOutApplicationLogValidFlag(FALSE); // ログを出さない
#if _DEBUG // デバッグビルドのときだけ
	SetMainWindowText(Config::WINDOW_NAME);
	SetWindowSizeExtendRate(Config::WINDOW_EXTEND);
#endif
	SetZBufferBitDepth(24);
	SetUseDirect3DVersion(DX_DIRECT3D_11);
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	ChangeWindowMode(Config::WINDOW_MODE); // Windowモードの場合
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}
	SetDrawScreen(DX_SCREEN_BACK);
	if (Effekseer_Init(8000) == -1) {
		Effkseer_End();
	}
	ClearDrawScreen();
	DrawFormatString(0, 0, 0xffffff, "起動中...");
	ScreenFlip();

	AppInit();
	while (ProcessMessage() >= 0 && (IsExitGame() == false))/* && (CheckHitKey(KEY_INPUT_ESCAPE) == 0))*/
	{
		ClearDrawScreen();
		AppUpdate();
		AppDraw();
		ScreenFlip();
	}
	AppRelease();

	Effkseer_End();
	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}