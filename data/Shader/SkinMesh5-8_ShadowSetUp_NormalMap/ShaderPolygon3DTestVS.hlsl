// ���_�V�F�[�_�[�̓���
struct VS_INPUT
{
	float4 pos				: POSITION;			// ���W(���[�J�����)
	float3 norm				: NORMAL;			// �@��(���[�J�����)
	float4 diffuse			: COLOR0;			// �f�B�t���[�Y�J���[
	float4 specular			: COLOR1;			// �X�y�L�����J���[
	float4 texCoords0		: TEXCOORD0;		// �e�N�X�`�����W
	float4 texCoords1		: TEXCOORD1;		// �T�u�e�N�X�`�����W
	float3 tan				: TANGENT0;			// �ڐ�(���[�J�����)
	float3 binorm			: BINORMAL0;		// �]�@��(���[�J�����)
	int4   blendIndices0	: BLENDINDICES0;	// �X�L�j���O�����p Float�^�萔�z��C���f�b�N�X
	float4 blendWeight0		: BLENDWEIGHT0;		// �X�L�j���O�����p�E�G�C�g�l
	int4   blendIndices1	: BLENDINDICES1;	// �X�L�j���O�����p Float�^�萔�z��C���f�b�N�X
	float4 blendWeight1		: BLENDWEIGHT1;		// �X�L�j���O�����p�E�G�C�g�l
};

// ���_�V�F�[�_�[�̏o��
struct VS_OUTPUT
{
	float4 spos			:	TEXCOORD0;
	float4 pos			:	SV_POSITION;	// ���W(�v���W�F�N�V�������)
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

// �X�L�j���O���b�V���p�́@���[�J���@���@���[���h�s��
struct DX_D3D11_VS_CONST_BUFFER_LOCALWORLDMATRIX
{
	// ���[�J���@���@���[���h�s��
	float4		Matrix[54 * 3];
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

// �X�L�j���O���b�V���p�́@���[�J���@���@���[���h�s��
cbuffer cbD3D11_CONST_BUFFER_VS_LOCALWORLDMATRIX	: register(b3)
{
	DX_D3D11_VS_CONST_BUFFER_LOCALWORLDMATRIX	g_localWorldMatrix;
};

// main�֐�
VS_OUTPUT main(VS_INPUT VSInput)
{
	VS_OUTPUT VSOutput;

	// �����̃t���[���̃u�����h�s��̍쐬
	float4 localWorldMatrix[3];
	localWorldMatrix[0] = g_localWorldMatrix.Matrix[VSInput.blendIndices0.x + 0] * VSInput.blendWeight0.x;
	localWorldMatrix[1] = g_localWorldMatrix.Matrix[VSInput.blendIndices0.x + 1] * VSInput.blendWeight0.x;
	localWorldMatrix[2] = g_localWorldMatrix.Matrix[VSInput.blendIndices0.x + 2] * VSInput.blendWeight0.x;

	localWorldMatrix[0] += g_localWorldMatrix.Matrix[VSInput.blendIndices0.y + 0] * VSInput.blendWeight0.y;
	localWorldMatrix[1] += g_localWorldMatrix.Matrix[VSInput.blendIndices0.y + 1] * VSInput.blendWeight0.y;
	localWorldMatrix[2] += g_localWorldMatrix.Matrix[VSInput.blendIndices0.y + 2] * VSInput.blendWeight0.y;

	localWorldMatrix[0] += g_localWorldMatrix.Matrix[VSInput.blendIndices0.z + 0] * VSInput.blendWeight0.z;
	localWorldMatrix[1] += g_localWorldMatrix.Matrix[VSInput.blendIndices0.z + 1] * VSInput.blendWeight0.z;
	localWorldMatrix[2] += g_localWorldMatrix.Matrix[VSInput.blendIndices0.z + 2] * VSInput.blendWeight0.z;

	localWorldMatrix[0] += g_localWorldMatrix.Matrix[VSInput.blendIndices0.w + 0] * VSInput.blendWeight0.w;
	localWorldMatrix[1] += g_localWorldMatrix.Matrix[VSInput.blendIndices0.w + 1] * VSInput.blendWeight0.w;
	localWorldMatrix[2] += g_localWorldMatrix.Matrix[VSInput.blendIndices0.w + 2] * VSInput.blendWeight0.w;
	//5~8
	localWorldMatrix[0] += g_localWorldMatrix.Matrix[VSInput.blendIndices1.x + 0] * VSInput.blendWeight1.x;
	localWorldMatrix[1] += g_localWorldMatrix.Matrix[VSInput.blendIndices1.x + 1] * VSInput.blendWeight1.x;
	localWorldMatrix[2] += g_localWorldMatrix.Matrix[VSInput.blendIndices1.x + 2] * VSInput.blendWeight1.x;

	localWorldMatrix[0] += g_localWorldMatrix.Matrix[VSInput.blendIndices1.y + 0] * VSInput.blendWeight1.y;
	localWorldMatrix[1] += g_localWorldMatrix.Matrix[VSInput.blendIndices1.y + 1] * VSInput.blendWeight1.y;
	localWorldMatrix[2] += g_localWorldMatrix.Matrix[VSInput.blendIndices1.y + 2] * VSInput.blendWeight1.y;

	localWorldMatrix[0] += g_localWorldMatrix.Matrix[VSInput.blendIndices1.z + 0] * VSInput.blendWeight1.z;
	localWorldMatrix[1] += g_localWorldMatrix.Matrix[VSInput.blendIndices1.z + 1] * VSInput.blendWeight1.z;
	localWorldMatrix[2] += g_localWorldMatrix.Matrix[VSInput.blendIndices1.z + 2] * VSInput.blendWeight1.z;

	localWorldMatrix[0] += g_localWorldMatrix.Matrix[VSInput.blendIndices1.w + 0] * VSInput.blendWeight1.w;
	localWorldMatrix[1] += g_localWorldMatrix.Matrix[VSInput.blendIndices1.w + 1] * VSInput.blendWeight1.w;
	localWorldMatrix[2] += g_localWorldMatrix.Matrix[VSInput.blendIndices1.w + 2] * VSInput.blendWeight1.w;


	// ���_���W�ϊ� ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++( �J�n )

	// ���[�J�����W�̃Z�b�g

	// ���W�v�Z( ���[�J�����r���[���v���W�F�N�V���� )
	float4 worldPosition;
	worldPosition.x = dot(VSInput.pos, localWorldMatrix[0]);
	worldPosition.y = dot(VSInput.pos, localWorldMatrix[1]);
	worldPosition.z = dot(VSInput.pos, localWorldMatrix[2]);
	worldPosition.w = 1.0f;

	float4 viewPosition;
	viewPosition.x = dot(worldPosition, g_base.viewMatrix[0]);
	viewPosition.y = dot(worldPosition, g_base.viewMatrix[1]);
	viewPosition.z = dot(worldPosition, g_base.viewMatrix[2]);
	viewPosition.w = 1.0f;

	VSOutput.pos.x = dot(viewPosition, g_base.projectionMatrix[0]);
	VSOutput.pos.y = dot(viewPosition, g_base.projectionMatrix[1]);
	VSOutput.pos.z = dot(viewPosition, g_base.projectionMatrix[2]);
	VSOutput.pos.w = dot(viewPosition, g_base.projectionMatrix[3]);

	// ���_���W�ϊ� ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++( �I�� )
	// �o�̓p�����[�^�Z�b�g ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++( �J�n )

	VSOutput.spos = viewPosition;

	// �o�̓p�����[�^�Z�b�g ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++( �I�� )


	// �o�̓p�����[�^��Ԃ�
	return VSOutput ;
}