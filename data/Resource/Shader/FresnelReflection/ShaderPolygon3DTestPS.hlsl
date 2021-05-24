// �s�N�Z���V�F�[�_�[�̓���
struct PS_INPUT
{
	float4 spos			:	TEXCOORD0;		// �\�����W
	float3 vPosition	:	TEXCOORD1;		// ���W(�r���[���)
	float3 norm			:	TEXCOORD2;		// �@��(�r���[���)
	float4 dif			:	COLOR0;			// �f�B�t���[�Y�J���[
};

// �s�N�Z���V�F�[�_�[�̏o��
struct PS_OUTPUT
{
	float4 color0           : SV_TARGET0;	// �F
} ;

// �}�e���A���p�����[�^
struct DX_D3D11_CONST_MATERIAL
{
	float4		diffuse;				// �f�B�t���[�Y�J���[
	float4		specular;				// �X�y�L�����J���[
	float4		ambient_Emissive;		// �}�e���A���G�~�b�V�u�J���[ + �}�e���A���A���r�G���g�J���[ * �O���[�o���A���r�G���g�J���[

	float		power;					// �X�y�L�����̋���
	float		typeParam0;			// �}�e���A���^�C�v�p�����[�^0
	float		typeParam1;			// �}�e���A���^�C�v�p�����[�^1
	float		typeParam2;			// �}�e���A���^�C�v�p�����[�^2
};

// �t�H�O�p�����[�^
struct DX_D3D11_VS_CONST_FOG
{
	float		linearAdd;				// �t�H�O�p�p�����[�^ end / ( end - start )
	float		linearDiv;				// �t�H�O�p�p�����[�^ -1  / ( end - start )
	float		density;				// �t�H�O�p�p�����[�^ density
	float		e;						// �t�H�O�p�p�����[�^ ���R�ΐ��̒�

	float4		color;					// �J���[
};

// ���C�g�p�����[�^
struct DX_D3D11_CONST_LIGHT
{
	int			type;					// ���C�g�^�C�v( DX_LIGHTTYPE_POINT �Ȃ� )
	int3		padding1;				// �p�f�B���O�P

	float3		position;				// ���W( �r���[��� )
	float		rangePow2;				// �L�������̂Q��

	float3		direction;				// ����( �r���[��� )
	float		fallOff;				// �X�|�b�g���C�g�pFallOff

	float3		diffuse;				// �f�B�t���[�Y�J���[
	float		spotParam0;			// �X�|�b�g���C�g�p�p�����[�^�O( cos( Phi / 2.0f ) )

	float3		specular;				// �X�y�L�����J���[
	float		spotParam1;			// �X�|�b�g���C�g�p�p�����[�^�P( 1.0f / ( cos( Theta / 2.0f ) - cos( Phi / 2.0f ) ) )

	float4		ambient;				// �A���r�G���g�J���[�ƃ}�e���A���̃A���r�G���g�J���[����Z��������

	float		attenuation0;			// �����ɂ�錸�������p�p�����[�^�O
	float		attenuation1;			// �����ɂ�錸�������p�p�����[�^�P
	float		attenuation2;			// �����ɂ�錸�������p�p�����[�^�Q
	float		padding2;				// �p�f�B���O�Q
};

// �s�N�Z���V�F�[�_�[�E���_�V�F�[�_�[���ʃp�����[�^
struct DX_D3D11_CONST_BUFFER_COMMON
{
	DX_D3D11_CONST_LIGHT		light[6];			// ���C�g�p�����[�^
	DX_D3D11_CONST_MATERIAL		material;				// �}�e���A���p�����[�^
	DX_D3D11_VS_CONST_FOG		fog;					// �t�H�O�p�����[�^
};

// �萔�o�b�t�@�s�N�Z���V�F�[�_�[��{�p�����[�^
struct DX_D3D11_PS_CONST_BUFFER_BASE
{
	float4		factorColor;			// �A���t�@�l��

	float		mulAlphaColor;			// �J���[�ɃA���t�@�l����Z���邩�ǂ���( 0.0f:��Z���Ȃ�  1.0f:��Z���� )
	float		alphaTestRef;			// �A���t�@�e�X�g�Ŏg�p�����r�l
	float2		padding1;

	int			alphaTestCmpMode;		// �A���t�@�e�X�g��r���[�h( DX_CMP_NEVER �Ȃ� )
	int3		padding2;

	float4		ignoreTextureColor;	// �e�N�X�`���J���[���������p�J���[
};

// ���_�V�F�[�_�[�E�s�N�Z���V�F�[�_�[���ʃp�����[�^
cbuffer cbD3D11_CONST_BUFFER_COMMON					: register(b0)
{
	DX_D3D11_CONST_BUFFER_COMMON		g_common;
};

// ��{�p�����[�^
cbuffer cbD3D11_CONST_BUFFER_PS_BASE				: register(b1)
{
	DX_D3D11_PS_CONST_BUFFER_BASE		g_base;
};

//Texture
SamplerState	g_mirrorSampler	: register(s0);		// ���˃e�N�X�`���T���v���[
Texture2D		g_mirrorTexture	: register(t0);		// ���˃e�N�X�`��

// main�֐�
PS_OUTPUT main( PS_INPUT PSInput)
{
	PS_OUTPUT PSOutput;
	float2 texCoords;
	float4 texColor;
	float refractiveRatio;

	// �e�N�X�`�����W�̎Z�o
	texCoords.x = PSInput.spos.x / PSInput.spos.w;
	texCoords.y = PSInput.spos.y / PSInput.spos.w;

	// ���ɉf���e�N�X�`������F���擾
	texColor = g_mirrorTexture.Sample(g_mirrorSampler, texCoords);
	// �f�B�t���[�Y�J���[�Ə�Z���ďo�͂ɃZ�b�g
	PSOutput.color0 = texColor * PSInput.dif;

	// ���̋��ܗ� = 1.333    ��C�̋��ܗ� = 1.000293
	refractiveRatio = 1.001f / 1.000293f;

	// �t���l�����˗��v�Z( �}���y�P����[�ǂ��ƃR���l�̃t���l�����ˉ��������p )
	float A = refractiveRatio;
	float B = dot(-normalize(PSInput.vPosition), normalize(PSInput.norm));
	float C = sqrt(1.0f - A * A * (1 - B * B));
	//0�ȉ��ɂȂ�ꍇ��������ۂ��̂ňꉞ�`�F�b�N����0�ȉ��Ȃ�␳����
	float Rs = (A * B - C) * (A * B - C) / ((A * B + C) * (A * B + C));
	float Rp = (A * C - B) * (A * C - B) / ((A * C + B) * (A * C + B));
	float alpha = (Rs + Rp) / 2.0f;
	alpha = min(alpha + 0.40f, 1.0f);
	// �A���t�@�l���Z�b�g
	PSOutput.color0.a = alpha;

	return PSOutput;
}