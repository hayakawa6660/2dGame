// �s�N�Z���V�F�[�_�[�̓���
struct PS_INPUT
{
	float2 texCoords0	:	TEXCOORD0;		// �e�N�X�`�����W
	float3 vPosition	:	TEXCOORD1;		// ���W(�r���[���)
	float3 norm			:	TEXCOORD2;		// �@��(�r���[���)
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

//Texture
SamplerState g_diffuseMapSampler	: register(s0);		// �f�B�t���[�Y�}�b�v�e�N�X�`��
Texture2D    g_diffuseMapTexture	: register(t0);		// �f�B�t���[�Y�}�b�v�e�N�X�`��

SamplerState g_specularMapSampler		: register(s2);				// �X�؃L�����e�N�X�`��
Texture2D    g_specularMapTexture		: register(t2);				// �X�؃L�����e�N�X�`��

SamplerState g_toonSampler			: register(s3);				// �g�D�[���e�N�X�`��
Texture2D    g_toonTexture			: register(t3);				// �g�D�[���e�N�X�`��

// main�֐�
PS_OUTPUT main(PS_INPUT PSInput)
{
	PS_OUTPUT PSOutput;

	float3 nrm = normalize(PSInput.norm);
	float3 v_to_eye = normalize(-PSInput.vPosition);
	//�l�̏�����
	float3 totalDiff = float3(0.f, 0.f, 0.f);
	float3 totalSpec = float3(0.f, 0.f, 0.f);
	float3 totalAmb = float3(0.0f, 0.0f, 0.0f);
	float totalLightGen = 0.f;

	/*
	�f�B���N�V���i�����C�g�̏���
	*/
	float3 lightDir = g_common.light[0].direction;
	float diffAngleGen = saturate(dot(nrm, -lightDir));
	float3 temp = normalize(v_to_eye - lightDir);
	float temp2 = pow(max(0.0f, dot(nrm, temp)), g_common.material.power);
	totalSpec += temp2 * g_common.light[0].specular;
	totalDiff += g_common.light[0].diffuse;
	totalAmb += g_common.light[0].ambient;
	totalLightGen += diffAngleGen;
	/*
	�I��
	*/
	/*
	�X�|�b�g���C�g�̏���
	*/
	/*
	lightDir = normalize(PSInput.vPosition.xyz - g_common.light[1].position.xyz);
	float3 temp3 = PSInput.vPosition.xyz - g_common.light[1].position.xyz;
	float lightDistancePow = dot(temp3, temp3);
	float lightGen = 1.0f / (g_common.light[1].attenuation0 + g_common.light[1].attenuation1 * sqrt(lightDistancePow) + g_common.light[1].attenuation2 * lightDistancePow);
	// �L�������O�������猸�������ő�ɂ��鏈��
	float lightDirCos = dot(lightDir, g_common.light[1].direction);
	lightGen *= saturate(pow(abs(max(lightDirCos - g_common.light[1].spotParam0, 0.0f) * g_common.light[1].spotParam1), g_common.light[1].fallOff));

	lightGen *= step(lightDistancePow, g_common.light[1].rangePow2);
	diffAngleGen = saturate(dot(nrm, -lightDir));

	totalLightGen += diffAngleGen * lightGen;

	temp = normalize(v_to_eye - lightDir);
	temp2 = pow(max(0.0f, dot(nrm, temp)), g_common.material.power);

	totalSpec += temp2 * lightGen * g_common.light[1].specular;
	totalDiff += g_common.light[1].diffuse;
	totalAmb += g_common.light[1].ambient;
	*/
	/*
	�I��
	*/

	/*
	�|�C���g���C�g�̏���
	*/
	/*
	lightDir = normalize(PSInput.vPosition.xyz - g_common.light[1].position.xyz);
	float3 temp3 = PSInput.vPosition.xyz - g_common.light[1].position.xyz;
	float lightDistancePow = dot(temp3, temp3);
	float lightGen = 1.0f / (g_common.light[1].attenuation0 + g_common.light[1].attenuation1 * sqrt(lightDistancePow) + g_common.light[1].attenuation2 * lightDistancePow);
	// �L�������O�������猸�������ő�ɂ��鏈��
	lightGen *= step(lightDistancePow, g_common.light[1].rangePow2);
	diffAngleGen = saturate(dot(nrm, -lightDir));
	temp = normalize(v_to_eye - lightDir);
	temp2 = pow(max(0.0f, dot(nrm, temp)), g_common.material.power);
	totalSpec += temp2 * lightGen * g_common.light[1].specular;
	totalDiff += g_common.light[1].diffuse;
	totalAmb += g_common.light[1].ambient;
	totalLightGen += diffAngleGen;
	*/
	/*
	�I��
	*/
	// �A���r�G���g�J���[�̒~�ϒl += �}�e���A���̃A���r�G���g�J���[�ƃO���[�o���A���r�G���g�J���[����Z�������̂ƃ}�e���A���G�~�b�V�u�J���[�����Z��������
	totalAmb += g_common.material.ambient_Emissive.xyz;
	totalDiff *= g_common.material.diffuse.xyz;//g_common.light[0].diffuse * g_common.material.diffuse.xyz * diffAngleGen + g_common.light[0].ambient.xyz;

	// TotalDiffuse = ���C�g�f�B�t���[�Y�J���[�~�ϒl + ( �}�e���A���̃A���r�G���g�J���[�ƃO���[�o���A���r�G���g�J���[����Z�������̂ƃ}�e���A���G�~�b�V�u�J���[�����Z�������� )
	//totalDiff += g_common.material.ambient_Emissive.xyz;
	// SpecularColor = ���C�g�̃X�y�L�����J���[�~�ϒl * �}�e���A���̃X�y�L�����J���[
	float3 texSpec = g_specularMapTexture.Sample(g_specularMapSampler, PSInput.texCoords0);
	float3 specColor = totalSpec * g_common.material.specular.xyz * texSpec;
	// �o�̓J���[ = TotalDiffuse * �e�N�X�`���J���[ + SpecularColor
	float4 texDiff = g_diffuseMapTexture.Sample(g_diffuseMapSampler, PSInput.texCoords0);
	float4 ToonColor = g_toonTexture.Sample(g_toonSampler, totalLightGen);
	//PSOutput.color0.rgb = texDiff.rgb * ToonColor * totalDiff + specColor;
	PSOutput.color0.rgb = saturate(saturate(totalDiff.rgb + totalAmb) * ToonColor.rgb + specColor.rgb) * texDiff.rgb;
	// �A���t�@�l = �e�N�X�`���A���t�@ * �}�e���A���̃f�B�t���[�Y�A���t�@ * �s�����x
	PSOutput.color0.a = texDiff.a * g_common.material.diffuse.a * g_base.factorColor.a;

	return PSOutput;
}