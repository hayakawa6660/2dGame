// ピクセルシェーダーの入力
struct PS_INPUT
{
	float4 spos			:	TEXCOORD0;
};

// ピクセルシェーダーの出力
struct PS_OUTPUT
{
	float4 color0           : SV_TARGET0;	// 色
};

// main関数
PS_OUTPUT main(PS_INPUT PSInput)
{
	PS_OUTPUT PSOutput;
	PSOutput.color0 = PSInput.spos.z;
	PSOutput.color0.a = 1.0f;
	return PSOutput;
}