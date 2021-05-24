// ���_�V�F�[�_�[�̓���
struct VS_INPUT
{
	float3 pos			: POSITION0;	// ���W( ���[�J����� )
	float4 spos			: POSITION1;	// �\�����W
	float3 norm			: NORMAL0;		// �@��( ���[�J����� )
	float3 tan			: TANGENT0;		// �ڐ�( ���[�J����� )
	float3 binorm		: BINORMAL0;	// �]�@��( ���[�J����� )
	float4 dif			: COLOR0;		// �f�B�t���[�Y�J���[
	float4 spc			: COLOR1;		// �X�y�L�����J���[
	float2 texCoords0	: TEXCOORD0;	// �e�N�X�`�����W
	float2 texCoords1	: TEXCOORD1;	// �T�u�e�N�X�`�����W
};

// ���_�V�F�[�_�[�̏o��
struct VS_OUTPUT
{
	float4 spos			:	TEXCOORD0;		// �\�����W
	float3 vPosition	:	TEXCOORD1;		// ���W(�r���[���)
	float3 norm			:	TEXCOORD2;		// �@��(�r���[���)
	float4 dif			:	COLOR0;			// �f�B�t���[�Y�J���[
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

// ���̑��̍s��
struct DX_D3D11_VS_CONST_BUFFER_OTHERMATRIX
{
	float4		shadowMapLightViewProjectionMatrix[3][4];			// �V���h�E�}�b�v�p�̃��C�g�r���[�s��ƃ��C�g�ˉe�s�����Z��������
	float4		textureMatrix[3][2];								// �e�N�X�`�����W����p�s��
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
	
	// ���W�v�Z( ���[�J�����r���[���v���W�F�N�V���� )
	float4 worldPosition;
	worldPosition.x = dot(VSInput.pos, g_base.localWorldMatrix[0]);
	worldPosition.y = dot(VSInput.pos, g_base.localWorldMatrix[1]);
	worldPosition.z = dot(VSInput.pos, g_base.localWorldMatrix[2]);
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

	// �@�����r���[��Ԃ̊p�x�ɕϊ� =====================================================( �J�n )

	// ���[�J���x�N�g�������[���h�x�N�g���ɕϊ�
	float3 worldNrm;
	worldNrm.x = dot(VSInput.norm, g_base.localWorldMatrix[0].xyz);
	worldNrm.y = dot(VSInput.norm, g_base.localWorldMatrix[1].xyz);
	worldNrm.z = dot(VSInput.norm, g_base.localWorldMatrix[2].xyz);
	// ���[���h�x�N�g�����r���[�x�N�g���ɕϊ�
	VSOutput.norm.x = dot(worldNrm, g_base.viewMatrix[0].xyz);
	VSOutput.norm.y = dot(worldNrm, g_base.viewMatrix[1].xyz);
	VSOutput.norm.z = dot(worldNrm, g_base.viewMatrix[2].xyz);

	// �@�����r���[��Ԃ̊p�x�ɕϊ� =====================================================( �I�� )

	// �o�̓p�����[�^�Z�b�g ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++( �J�n )

	// ���_���W��ۑ�
	VSOutput.vPosition = viewPosition.xyz;
	// �f�B�t���[�Y�J���[�͂��̂܂ܓn��
	VSOutput.dif = VSInput.dif;
	// ���ɉf��f���̎��_�ł̎ˉe���W
	VSOutput.spos = VSInput.spos;

	// �o�̓p�����[�^�Z�b�g ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++( �I�� )

	// �o�̓p�����[�^��Ԃ�
	return VSOutput;
}
