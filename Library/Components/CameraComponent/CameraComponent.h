#pragma once

#include "../ComponentBase.h"
class CameraComponent : public ComponentBase
{
public:		//Constructor
	CameraComponent();
	~CameraComponent();
private:	//Private Functions

public:		//Public Functions
	/// <summary>
	/// ���݂�Offset�Ɏw��l�����Z����
	/// </summary>
	/// <param name="_add">���Z����l</param>
	void AddOffset(const VECTOR &_add) { m_offset += _add; }

	/// <summary>
	/// �J�����̃^�C�v�����ߖ@�ɕύX����
	/// </summary>
	/// <param name="_fov">����p</param>
	void SetPerspective(float _fov);
	/// <summary>
	/// �J�����̃^�C�v�𐳎ˉe�ɕύX����
	/// </summary>
	/// <param name="_size">��ʏ㉺�̋�Ԃ͈̔�</param>
	void SetOrtho(float _size);

	/// <summary>
	/// �J�����̈ʒu�ƌ������X�V����
	/// �����́A���O�ɃZ�b�g����Target�̒l�ƁARotation�̒l����Z�o�����
	/// �ʒu�́ATarget�̈ʒu����Offset��Rotation���|�����l�ɂȂ�
	/// </summary>
	/// <param name="_rotation">�Z�b�g�����]�l(Radian)</param>
	void PositionAndTargetUpdate(const VECTOR &_rotation);
	
	/// <summary>
	/// �J�����̈ʒu�ƒ����_�𒼐ڎw�肷��
	/// </summary>
	/// <param name="_position">�ʒu</param>
	/// <param name="_target">�����_</param>
	void SetPositionAndTarget(const VECTOR &_position, const VECTOR &_target);

	/// <summary>
	/// ��̍��W�����_�ɓ����Ă��邩���m�F����
	/// �����`�̏ꍇ�͗����������W������
	/// </summary>
	/// <param name="_p1">���W1</param>
	/// <param name="_p2">���W2</param>
	/// <return>true : ���E�ɓ����Ă��� false : ���E�ɓ����Ă��Ȃ�</return>
	bool CheckCameraViewClip(const VECTOR &_p1, const VECTOR &_p2);

	void SetNearFar(float _near, float _far);
private:	//Variables
	VECTOR m_offset;	//�����_����̋���
	VECTOR m_target;	//�����_
public:		// Function to get and set variables
	/// <summary>
	/// ���݂�Offset�l���󂯎��
	/// </summary>
	/// <return>���݂�Offset�l</return>
	const VECTOR & GetOffset() { return m_offset; }
	/// <summary>
	/// Offset���w��l�ɕς���
	/// </summary>
	/// <param name="_offset">�ύX����Offset�̒l</param>
	void SetOffset(const VECTOR & _offset) { m_offset = _offset; }
	
	/// <summary>
	/// Target��Position���󂯎��
	/// </summary>
	/// <return>Target��Position</return>
	const VECTOR & GetTarget() { return m_target; }
	/// <summary>
	/// Target���w��l�ɕς���
	/// </summary>
	/// <param name="_offset">�ύX����Offset�̒l</param>
	void SetTarget(const VECTOR & _target) { m_target = _target; }
};