// ���_�V�F�[�_�[�̓���
struct VS_INPUT
{
	float3 pos				: POSITION;		// ���W( ���[�J����� )
	float3 norm				: NORMAL;		// �@��( ���[�J����� )
	float4 diffuse			: COLOR0;		// �f�B�t���[�Y�J���[
	float4 specular			: COLOR1;		// �X�y�L�����J���[
	float4 texCoords0		: TEXCOORD0;	// �e�N�X�`�����W
	float4 texCoords1		: TEXCOORD1;	// �T�u�e�N�X�`�����W
};

// ���_�V�F�[�_�[�̏o��
struct VS_OUTPUT
{
	float2 texCoords0	:	TEXCOORD0;		// �e�N�X�`�����W
	float3 vPosition	:	TEXCOORD1;		// ���W(�r���[���)
	float3 norm			:	TEXCOORD2;		// �@��(�r���[���)
	float4 pos			:	SV_POSITION;	// ���W(�v���W�F�N�V�������)
	//float4 spos			:	TEXCOORD3;		// �\�����W
};

// ��{�p�����[�^
struct DX_D3D11_VS_CONST_BUFFER_BASE
{
	float4		antiViewportMatrix[4];		// �A���`�r���[�|�[�g�s��
	float4		projectionMatrix[4];		// �r���[�@���@�v���W�F�N�V�����s��
	float4		viewMatrix[3];				// ���[���h�@���@�r���[�s��
	float4		localWorldMatrix[3];		// ���[�J���@���@���[���h�s��

	float4		toonOutLineSize;			// �g�D�[���̗֊s���̑傫��
	float		DdiffuseSource;				// �f�B�t���[�Y�J���[( 0.0f:�}�e���A��  1.0f:���_ )
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

	// �@�����r���[�x�N�g���ɕϊ�
	float3 worldNrm;
	worldNrm.x = dot(VSInput.norm, g_base.localWorldMatrix[0].xyz);
	worldNrm.y = dot(VSInput.norm, g_base.localWorldMatrix[1].xyz);
	worldNrm.z = dot(VSInput.norm, g_base.localWorldMatrix[2].xyz);
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
	// �@����ۑ�
	VSOutput.norm = viewNrm;

	// �o�̓p�����[�^�Z�b�g ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++( �I�� )


	// �o�̓p�����[�^��Ԃ�
	return VSOutput ;
}