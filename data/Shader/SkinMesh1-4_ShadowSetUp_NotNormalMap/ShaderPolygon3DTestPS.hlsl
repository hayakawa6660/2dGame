// �s�N�Z���V�F�[�_�[�̓���
struct PS_INPUT
{
	float4 spos			:	TEXCOORD0;
};

// �s�N�Z���V�F�[�_�[�̏o��
struct PS_OUTPUT
{
	float4 color0           : SV_TARGET0;	// �F
};

// main�֐�
PS_OUTPUT main(PS_INPUT PSInput)
{
	PS_OUTPUT PSOutput;
	PSOutput.color0 = PSInput.spos.z;
	PSOutput.color0.a = 1.0f;
	return PSOutput;
}