#pragma once

namespace CameraDefine
{
	//感度(下げると早くなる)
	static constexpr float SENSITIVITY = 7000.0f;
	//カメラとプレイヤーの距離
	static constexpr float OFFSET_Y = 125.f;
	static constexpr float OFFSET_Z = -180.f;

	//注視点の補正値
	static constexpr float TARGET_OFFSET_Y = 113.f;
};