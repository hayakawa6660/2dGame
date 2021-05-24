// �s�N�Z���V�F�[�_�[�̓���
struct PS_INPUT
{
	float2 texCoords0	:	TEXCOORD0;		// �e�N�X�`�����W
	float3 vPosition	:	TEXCOORD1;		// ���W( �r���[��� )
	float3 tan			:	TEXCOORD2;		// �ڐ�(�r���[���)
	float3 binorm		:	TEXCOORD3;		// �]�@��(�r���[���)
	float3 norm			:	TEXCOORD4;		// �@��(�r���[���)
	float4 spos			:	TEXCOORD5;		// �\�����W
	float  fog : TEXCOORD6;
	float4 diffuse		:	COLOR0;			// �f�B�t���[�Y�J���[
	float4 specular		:	COLOR1;			// �X�؃L�����J���[
};

// �s�N�Z���V�F�[�_�[�̏o��
struct PS_OUTPUT
{
	float4 color0           : SV_TARGET0;	// �F
};

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

cbuffer DEPTH_CONST				: register(b4)
{
	float4 test;
};
//Texture
SamplerState g_diffuseMapSampler	: register(s0);		// �f�B�t���[�Y�}�b�v�e�N�X�`��
Texture2D    g_diffuseMapTexture	: register(t0);		// �f�B�t���[�Y�}�b�v�e�N�X�`��
SamplerState g_normalMapSampler		: register(s1);		// �@���}�b�v�e�N�X�`��
Texture2D    g_normalMapTexture		: register(t1);		// �@���}�b�v�e�N�X�`��
SamplerState g_specularMapSampler	: register(s2);		// �X�؃L�����}�b�v�e�N�X�`��
Texture2D    g_specularMapTexture	: register(t2);		// �X�؃L�����}�b�v�e�N�X�`��
//SamplerState g_toonMapSampler		: register(s3);		// �g�D�[���}�b�v�e�N�X�`��
//Texture2D    g_toonMapTexture		: register(t3);		// �g�D�[���}�b�v�e�N�X�`��
SamplerState g_shadowMapSampler		: register(s4);		// �g�D�[���}�b�v�e�N�X�`��
Texture2D    g_shadowMapTexture		: register(t4);		// �g�D�[���}�b�v�e�N�X�`��


// main�֐�
PS_OUTPUT main(PS_INPUT PSInput)
{
	PS_OUTPUT PSOutput;
	// �ڐ��E�]�@���E�@���𐳋K��
	float3 VNrm = normalize(PSInput.norm);
	float3 VTan = normalize(PSInput.tan);
	float3 VBin = normalize(PSInput.binorm);
	// ���_���W���王�_�ւ̃x�N�g����ڒ��Ԃɓ��e�����㐳�K�����ĕۑ�
	float3 TempF3;
	TempF3.x = dot(VTan, -PSInput.vPosition.xyz);
	TempF3.y = dot(VBin, -PSInput.vPosition.xyz);
	TempF3.z = dot(VNrm, -PSInput.vPosition.xyz);
	float3 V_to_Eye = normalize(TempF3);
	// �@���� 0�`1 �̒l�� -1.0�`1.0 �ɕϊ�����
	float3 Normal = (g_normalMapTexture.Sample(g_normalMapSampler, PSInput.texCoords0.xy) - float3(0.5f, 0.5f, 0.5f)) * 2.0f;
	// �f�B�t���[�Y�J���[�ƃX�y�L�����J���[�̒~�ϒl��������
	float3 TotalDiffuse = float3(0.0f, 0.0f, 0.0f);
	float3 TotalSpecular = float3(0.0f, 0.0f, 0.0f);

	// �f�B���N�V���i�����C�g�̏��� +++++++++++++++++++++++++++++++++++++++++++++++++++++( �J�n )
	// ���C�g�����x�N�g���̌v�Z
	TempF3 = g_common.light[0].direction;
	// ���C�g�̃x�N�g����ڒn��Ԃɕϊ�
	float3 lLightDir;
	lLightDir.x = dot(VTan, TempF3);
	lLightDir.y = dot(VBin, TempF3);
	lLightDir.z = dot(VNrm, TempF3);
	// DiffuseAngleGen = �f�B�t���[�Y�p�x�������v�Z(��������)
	float DiffuseAngleGen = saturate(dot(Normal, -lLightDir));
	// �f�B�t���[�Y�J���[�~�ϒl += ���C�g�̃f�B�t���[�Y�J���[ * �}�e���A���̃f�B�t���[�Y�J���[ * �f�B�t���[�Y�J���[�p�x������ + ���C�g�̃A���r�G���g�J���[�ƃ}�e���A���̃A���r�G���g�J���[����Z�������� 
	TotalDiffuse += g_common.light[0].diffuse * g_common.material.diffuse.xyz * DiffuseAngleGen + g_common.light[0].ambient;
	// �X�y�L�����J���[�v�Z
	// �n�[�t�x�N�g���̌v�Z
	TempF3 = normalize(V_to_Eye - lLightDir);
	// Temp = pow( max( 0.0f, N * H ), g_Common.Material.Power )
	float4 Temp = pow(max(0.0f, dot(Normal, TempF3)), g_common.material.power);
	float3 TextureSpecular = g_specularMapTexture.Sample(g_specularMapSampler, PSInput.texCoords0);
	// �X�y�L�����J���[�~�ϒl += Temp * ���C�g�̃X�y�L�����J���[
	TotalSpecular += Temp * g_common.light[0].specular * TextureSpecular;
	// �f�B���N�V���i�����C�g�̏��� +++++++++++++++++++++++++++++++++++++++++++++++++++++( �I�� )

	// �o�̓J���[�v�Z +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++( �J�n )
	// TotalDiffuse = ���C�g�f�B�t���[�Y�J���[�~�ϒl + ( �}�e���A���̃A���r�G���g�J���[�ƃO���[�o���A���r�G���g�J���[����Z�������̂ƃ}�e���A���G�~�b�V�u�J���[�����Z�������� )
	TotalDiffuse += g_common.material.ambient_Emissive.xyz;
	// SpecularColor = ���C�g�̃X�y�L�����J���[�~�ϒl * �}�e���A���̃X�y�L�����J���[
	float3 SpecularColor = TotalSpecular * g_common.material.specular.xyz;
	// �o�̓J���[ = TotalDiffuse * �e�N�X�`���J���[ + SpecularColor
	float4 TextureDiffuseColor = g_diffuseMapTexture.Sample(g_diffuseMapSampler, PSInput.texCoords0);

	float4 outColor;
	outColor.rgb = TextureDiffuseColor.rgb * TotalDiffuse + SpecularColor;
	// �t�H�O����
	outColor.rgb = lerp(g_common.fog.color.rgb, outColor.rgb, saturate(PSInput.fog));
	// �A���t�@�l = �e�N�X�`���A���t�@ * �}�e���A���̃f�B�t���[�Y�A���t�@ * �s�����x
	outColor.a = TextureDiffuseColor.a * g_common.material.diffuse.a * g_base.factorColor.a;

	float2 DepthTexCoord;
	DepthTexCoord.x = (PSInput.spos.x + 1.0f) / 2.0f;
	DepthTexCoord.y = 1.0f - (PSInput.spos.y + 1.0f) / 2.0f;

	float DepthTexture = g_shadowMapTexture.Sample(g_shadowMapSampler, DepthTexCoord);
	if (PSInput.spos.z > DepthTexture + test.r)
	{
		outColor.rgb *= 0.8f;
	}

	PSOutput.color0 = outColor;

	//PSOutput.color0 = PSInput.spos;
	// �o�̓J���[�v�Z +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++( �I�� )
	return PSOutput;
}