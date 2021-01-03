// ���_�V�F�[�_�[�̓���
struct VS_INPUT
{
	//���̏��ԂłȂ��ƃo�O��
	float3 pos			: POSITION;			// ���W(���[�J�����)
	float3 norm			: NORMAL;			// �@��(���[�J�����)
	float4 diffuse		: COLOR0;			// �f�B�t���[�Y�J���[
	float4 specular		: COLOR1;			// �X�y�L�����J���[
	float4 texCoords0	: TEXCOORD0;		// �e�N�X�`�����W
	float4 texCoords1	: TEXCOORD1;		// �T�u�e�N�X�`�����W
	float3 tan			: TANGENT0;			// �ڐ�(���[�J�����)
	float3 binorm		: BINORMAL0;		// �]�@��(���[�J�����)
};

// ���_�V�F�[�_�[�̏o��
struct VS_OUTPUT
{
	float2 texCoords0	:	TEXCOORD0;		// �e�N�X�`�����W
	float3 vPosition	:	TEXCOORD1;		// ���W(�r���[���)
	float3 tan			:	TEXCOORD2;		// �ڐ�(�r���[���)
	float3 binorm		:	TEXCOORD3;		// �]�@��(�r���[���)
	float3 norm			:	TEXCOORD4;		// �@��(�r���[���)
	float  fog			:	TEXCOORD5;		//�t�H�O�p�����[�^�[
	float4 pos			:	SV_POSITION;	// ���W(�v���W�F�N�V�������)
	//�g���ĂȂ��̂�SV_POSITION��艺�ɒu���Ă���
	//float4 spos			:	TEXCOORD6;		// �\�����W
};

// ��{�p�����[�^
struct DX_D3D11_VS_CONST_BUFFER_BASE
{
	float4		antiViewportMatrix[4];		// �A���`�r���[�|�[�g�s��
	float4		projectionMatrix[4];		// �r���[�@���@�v���W�F�N�V�����s��
	float4		viewMatrix[3];				// ���[���h�@���@�r���[�s��
	float4		localWorldMatrix[3];		// ���[�J���@���@���[���h�s��

	float4		toonOutLineSize;			// �g�D�[���̗֊s���̑傫��
	float		diffuseSource;				// �f�B�t���[�Y�J���[( 0.0f:�}�e���A��  1.0f:���_ )
	float		specularSource;				// �X�y�L�����J���[(   0.0f:�}�e���A��  1.0f:���_ )
	float		mulSpecularColor;			// �X�y�L�����J���[�l�ɏ�Z����l( �X�y�L�������������Ŏg�p )
	float		padding;
};

// ���̑��̍s��
struct DX_D3D11_VS_CONST_BUFFER_OTHERMATRIX
{
	float4		shadowMapLightViewProjectionMatrix[3][4];			// �V���h�E�}�b�v�p�̃��C�g�r���[�s��ƃ��C�g�ˉe�s�����Z��������
	float4		textureMatrix[3][2];								// �e�N�X�`�����W����p�s��
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

// ���_�V�F�[�_�[�E�s�N�Z���V�F�[�_�[���ʃp�����[�^
cbuffer cbD3D11_CONST_BUFFER_COMMON					: register(b0)
{
	DX_D3D11_CONST_BUFFER_COMMON				g_common;
};

// ��{�p�����[�^
cbuffer cbD3D11_CONST_BUFFER_VS_BASE			: register(b1)
{
	DX_D3D11_VS_CONST_BUFFER_BASE				g_base;
};

// ���̑��̍s��
cbuffer cbD3D11_CONST_BUFFER_VS_OTHERMATRIX		: register(b2)
{
	DX_D3D11_VS_CONST_BUFFER_OTHERMATRIX		g_otherMatrix;
};

// main�֐�
VS_OUTPUT main(VS_INPUT VSInput)
{
	VS_OUTPUT VSOutput;
	// ���_���W�ϊ� ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++( �J�n )

	// ���[�J�����W�̃Z�b�g
	float4 localPosition;
	localPosition.xyz = VSInput.pos ;
	localPosition.w = 1.0f ;

	// ���W�v�Z( ���[�J�����r���[���v���W�F�N�V���� )
	float4 worldPosition;
	worldPosition.x = dot(localPosition, g_base.localWorldMatrix[0]);
	worldPosition.y = dot(localPosition, g_base.localWorldMatrix[1]);
	worldPosition.z = dot(localPosition, g_base.localWorldMatrix[2]);
	worldPosition.w = 1.0f;

	float4 viewPosition;
	viewPosition.x = dot(worldPosition, g_base.viewMatrix[0]);
	viewPosition.y = dot(worldPosition, g_base.viewMatrix[1]);
	viewPosition.z = dot(worldPosition, g_base.viewMatrix[2]);
	viewPosition.w = 1.0f;

	VSOutput.pos.x = dot(viewPosition, g_base.projectionMatrix[0]) ;
	VSOutput.pos.y = dot(viewPosition, g_base.projectionMatrix[1]) ;
	VSOutput.pos.z = dot(viewPosition, g_base.projectionMatrix[2]) ;
	VSOutput.pos.w = dot(viewPosition, g_base.projectionMatrix[3]) ;

	// ���_���W�ϊ� ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++( �I�� )

	// �@�����r���[��Ԃ̊p�x�ɕϊ� =====================================================( �J�n )

	// �]�@���A�ڐ��A�@�����r���[�x�N�g���ɕϊ�
	float3 worldTan;
	worldTan.x = dot(VSInput.tan, g_base.localWorldMatrix[0].xyz);
	worldTan.y = dot(VSInput.tan, g_base.localWorldMatrix[1].xyz);
	worldTan.z = dot(VSInput.tan, g_base.localWorldMatrix[2].xyz);

	float3 worldBin;
	worldBin.x = dot(VSInput.binorm, g_base.localWorldMatrix[0].xyz);
	worldBin.y = dot(VSInput.binorm, g_base.localWorldMatrix[1].xyz);
	worldBin.z = dot(VSInput.binorm, g_base.localWorldMatrix[2].xyz);

	float3 worldNrm;
	worldNrm.x = dot(VSInput.norm, g_base.localWorldMatrix[0].xyz);
	worldNrm.y = dot(VSInput.norm, g_base.localWorldMatrix[1].xyz);
	worldNrm.z = dot(VSInput.norm, g_base.localWorldMatrix[2].xyz);

	float3 viewTan;
	viewTan.x = dot(worldTan, g_base.viewMatrix[0].xyz);
	viewTan.y = dot(worldTan, g_base.viewMatrix[1].xyz);
	viewTan.z = dot(worldTan, g_base.viewMatrix[2].xyz);

	float3 viewBin;
	viewBin.x = dot(worldBin, g_base.viewMatrix[0].xyz);
	viewBin.y = dot(worldBin, g_base.viewMatrix[1].xyz);
	viewBin.z = dot(worldBin, g_base.viewMatrix[2].xyz);

	float3 viewNrm;
	viewNrm.x = dot(worldNrm, g_base.viewMatrix[0].xyz);
	viewNrm.y = dot(worldNrm, g_base.viewMatrix[1].xyz);
	viewNrm.z = dot(worldNrm, g_base.viewMatrix[2].xyz);

	// �@�����r���[��Ԃ̊p�x�ɕϊ� =====================================================( �I�� )


	// �o�̓p�����[�^�Z�b�g ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++( �J�n )

		// �e�N�X�`�����W�ϊ��s��ɂ��ϊ����s�������ʂ̃e�N�X�`�����W���Z�b�g
	VSOutput.texCoords0.x = dot(VSInput.texCoords0, g_otherMatrix.textureMatrix[0][0]);
	VSOutput.texCoords0.y = dot(VSInput.texCoords0, g_otherMatrix.textureMatrix[0][1]);

	// ���_���W��ۑ�
	VSOutput.vPosition = viewPosition.xyz;
	// �ڐ���ۑ�
	VSOutput.tan = viewTan;
	// �]�@����ۑ�
	VSOutput.binorm = viewBin;
	// �@����ۑ�
	VSOutput.norm = viewNrm;

	// ���`�t�H�O�v�Z
	VSOutput.fog = viewPosition.z * g_common.fog.linearDiv + g_common.fog.linearAdd;

	// �o�̓p�����[�^�Z�b�g ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++( �I�� )


	// �o�̓p�����[�^��Ԃ�
	return VSOutput ;
}