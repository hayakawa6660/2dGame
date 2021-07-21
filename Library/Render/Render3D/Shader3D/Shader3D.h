#pragma once

#include "Library/GameObject/GameObject.h"
#include "Source/Common.h"

#include <map>
#include <vector>

class PolygonSetComponent;

class Shader3D : public GameObject
{
public:
	//�������̂��߁A�������̓R�����g�A�E�g��
	enum class MESH_TYPE
	{
		NO_SHADER = -1,						// �V�F�[�_�[���g��Ȃ�(�O��)
		NMESH_NO_LIGHTING_DIFFONLY_FOG,		// ���� : ���C�g�̌��ʂ��󂯂��A�f�B�t���[�Y�̐F�݂̂Ŕ��f����V�F�[�_�[(�t�H�O���ʂ���)
		NMESH_DIFFUSE_ONLY,					// ���� : �f�B�t���[�Y�e�N�X�`���̐F�̂�(���ːF�̓}�e���A���̐F���Q��)
		SKIN4_DIFFUSE_ONLY,					// �X�L��1_4 :		//
		SKIN8_DIFFUSE_ONLY,					// �X�L��5_8 :		//
		NMESH_DIFF_SPEC_NORM,				// ���� : �f�B�t���[�Y�A�X�؃L�����ƃm�[�}���}�b�v�V�F�[�_�[(�t�H�O���ʂ���)
		NMESH_DIFF_SPEC_NORM_SHADOW,		// ���� : �f�B�t���[�Y�A�X�؃L�����ƃm�[�}���}�b�v�V�F�[�_�[(�t�H�O���ʂ���)�A�e�t��

		SKIN4_DIFF_SPEC_NORM,				// �X�L��1_4 : �f�B�t���[�Y�A�X�؃L�����ƃm�[�}���}�b�v�V�F�[�_�[
		SKIN8_DIFF_SPEC_NORM,				// �X�L��5_8 : �f�B�t���[�Y�A�X�؃L�����ƃm�[�}���}�b�v�V�F�[�_�[
		NMESH_DIFF_SPEC_TOON,				// ���� : �f�B�t���[�Y�A�X�؃L�����t���g�D�[���V�F�[�_�[
		
		NMESH_SHADOW_SETUP_NOT_NORMAL,		// ���� : �e�V�F�[�_�[�Z�b�g�A�b�v�p�̃m�[�}���}�b�v�����V�F�[�_�[
		NMESH_SHADOW_SETUP_NORMALMAP,		// ���� : �e�V�F�[�_�[�Z�b�g�A�b�v�p�̃m�[�}���}�b�v�t���V�F�[�_�[
		
		SKIN4_SHADOW_SETUP_NOT_NORMAL,		// �X�L��1_4 : �e�V�F�[�_�[�Z�b�g�A�b�v�p�̃m�[�}���}�b�v�����V�F�[�_�[
		SKIN4_SHADOW_SETUP_NORMALMAP,		// �X�L��1_4 : �e�V�F�[�_�[�Z�b�g�A�b�v�p�̃m�[�}���}�b�v�t���V�F�[�_�[

		SKIN8_SHADOW_SETUP_NOT_NORMAL,		// �X�L��5_8 : �e�V�F�[�_�[�Z�b�g�A�b�v�p�̃m�[�}���}�b�v�����V�F�[�_�[
		SKIN8_SHADOW_SETUP_NORMALMAP,		// �X�L��5_8 : �e�V�F�[�_�[�Z�b�g�A�b�v�p�̃m�[�}���}�b�v�t���V�F�[�_�[

		WATER,								// �t���l������(��)�V�F�[�_�[
	};
public:
	Shader3D();
	~Shader3D();
	void Update()override;
private:
	void CBufferUpdate();
public:
	void SetUpMirror(int _mirrorNum, VECTOR &_cPosition, VECTOR &_cTarget);
	void MirrorRender(int _mirrorNum);
	void MirrorSet(VECTOR &_position, float _radiusX, float _radiusY);


	/// <summary>
	///  ���f���̎����b�V���̃^�C�v���w�肷��B�@(���b�V���̃^�C�v��ł����)MV1DrawModel�A����ȊO��MV1DrawTriangleList)
	/// �E��{�I��MV1GetTriangleListVertexType�ő����ė����l�����̂܂ܑ���ΑΉ�����
	/// �����}�e���A�����ƂɃ^�C�v���Ⴄ�Ȃ�AMV1DrawTriangleList�ŕ`�悷��O�ɑ��� 
	/// �E�`����I������(�V�F�[�_�[��؂�)�Ƃ���MESH_TYPE::NO_RENDER��ݒ肷��B
	/// ���������ꍇ�ADxLib�̃f�t�H���g�V�F�[�_�[���K�������
	/// �E����{�I�ɑ��Ŏg��Ȃ���������Ȃ��̂ŁA���g�̕`�悪�I�������NO_RENDER����񋲂ނƈ��S
	/// </summary>
	/// <param name="_type">MESH_TYPE�@�̎w�肷�郁�b�V���̃^�C�v</param>
	void SetMeshTypeShader(MESH_TYPE _type);

	void SetShadowSetUpShader(bool _start);

private:
	bool m_loadEnd;
	//�V�F�[�_�[�ϐ�
	struct Vert_Pxcl_Shader
	{
		std::string vertFile;
		int vertex;
		std::string pixlFile;
		int pixcel;

		Vert_Pxcl_Shader() :
			vertex(-1),pixcel(-1)
		{
			vertFile.clear();
			pixlFile.clear();
		}
	};
	std::map<MESH_TYPE, Vert_Pxcl_Shader> m_shader;

	//���p�ϐ�(��X�N���X���\��)
	PolygonSetComponent * m_polygon;
	struct Mirror
	{
		int handle;
		COLOR_U8 diffuse;
		FLOAT4 ScreenPosition[4];
		VECTOR Position[4];
	};
	std::vector<Mirror> m_mirror;
	int m_mirrorNum;

	Sprite_Info m_toonTexture;	//�g�D�[���p�̃e�N�X�`��

	//�V���h�E�}�b�v�p�ϐ�
	struct LIGHT_MATRIX
	{
		MATRIX view;
		MATRIX projection;
	};
	LIGHT_MATRIX m_lightMat;
	int m_deptHandle;
	//�[�x�摜�擾���̃J�����ݒ�ϐ�
	float m_othroParam;// = 15200.f;
	float m_offsetParam;// = 10000.f;
	float m_farParam;// = 16680.f;
	//�o�b�t�@�n���h��
	int m_cbufferVS;
	int m_cbufferPS;
	// cbufferPS����m�F�p + �V�F�[�_�[�̐[�x�摜�̕␳�l���蓮�ŕύX�ł���悤�ɕϐ����m��
	float m_shadowCorrection;// = 60.f;
	VECTOR m_lightTarget;
public:
	int GetMirrorNum()const { return m_mirrorNum; }

	void SetTargetPosition(VECTOR &_position) { m_lightTarget = _position; }
};
/*
class PolygonSetComponent;

class Shader : public GameObject
{
public:
	enum class MESH_TYPE
	{
		NO_SHADER = -1,	//�`�斳��
		DIFFUSE_ONLY,
		DIFFUSE_ONLY_TOON,
		SKIN_4_DIFFUSE,	//1���_�ɗ^����e��1�`4���b�V��
		NO_LIGHT_NORMAL,
		NORMAL,			//���̃��b�V��
		//SKIN_4,			//1���_�ɗ^����e��1�`4���b�V��
		//SKIN_8,			//1���_�ɗ^����e��4�`8���b�V��
		NMAP_NORMAL,	//�m�[�}���}�b�v�t�����̃��b�V��
		NMAP_SKIN_4,	//�m�[�}���}�b�v�t��1���_�ɗ^����e��1�`4���b�V��
		NMAP_SKIN_8,	//1���_�ɗ^����e��4�`8���b�V��

		MIRRRO,
	};
public:
	Shader(SceneBase * _scene);
	~Shader();
	void Update()override;

	void SetUpMirror(int _mirrorNum, VECTOR &_cPosition, VECTOR &_cTarget);
	void MirrorRender(int _mirrorNum);
	void ShadowSetUp()override;
private://�ϐ�
	struct Vert_Pxcl_Shader
	{
		int vertex;
		int pixcel;
	};
	std::map<MESH_TYPE, Vert_Pxcl_Shader> m_shader;

	PolygonSetComponent * m_polygon;

	//���p�ϐ�(��X�N���X���\��)
	struct Mirror
	{
		int handle;
		COLOR_U8 diffuse;
		FLOAT4 ScreenPosition[4];
		VECTOR Position[4];
	};
	std::vector<Mirror> m_mirror;

	int m_mirrorNum;

	Sprite_Info m_toonTexture;	//�g�D�[���p�̃e�N�X�`��
public://Set�AGet
	/// <summary>
	///  ���f���̎����b�V���̃^�C�v���w�肷��B�@(���b�V���̃^�C�v��ł����)MV1DrawModel�A����ȊO��MV1DrawTriangleList)
	/// �E��{�I��MV1GetTriangleListVertexType�ő����ė����l�����̂܂ܑ���ΑΉ�����
	/// �����}�e���A�����ƂɃ^�C�v���Ⴄ�Ȃ�AMV1DrawTriangleList�ŕ`�悷��O�ɑ��� 
	/// �E�`����I������(�V�F�[�_�[��؂�)�Ƃ���MESH_TYPE::NO_RENDER��ݒ肷��B
	/// ���������ꍇ�ADxLib�̃f�t�H���g�V�F�[�_�[���K�������
	/// �E����{�I�ɑ��Ŏg��Ȃ���������Ȃ��̂ŁA���g�̕`�悪�I�������NO_RENDER����񋲂ނƈ��S
	/// </summary>
	/// <param name="_type">MESH_TYPE�@�̎w�肷�郁�b�V���̃^�C�v</param>
	void SetMeshTypeShader(MESH_TYPE _type);

	void MirrorSet(VECTOR &_position, float _radiusX, float _radiusY);
	int GetMirrorNum()const { return m_mirrorNum; }
};
*/