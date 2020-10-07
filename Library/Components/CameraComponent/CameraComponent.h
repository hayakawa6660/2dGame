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
	/// 現在のOffsetに指定値を加算する
	/// </summary>
	/// <param name="_add">加算する値</param>
	void AddOffset(const VECTOR &_add) { m_offset += _add; }

	/// <summary>
	/// カメラのタイプを遠近法に変更する
	/// </summary>
	/// <param name="_fov">視野角</param>
	void SetPerspective(float _fov);
	/// <summary>
	/// カメラのタイプを正射影に変更する
	/// </summary>
	/// <param name="_size">画面上下の空間の範囲</param>
	void SetOrtho(float _size);

	/// <summary>
	/// カメラの位置と向きを更新する
	/// 向きは、事前にセットしたTargetの値と、Rotationの値から算出される
	/// 位置は、Targetの位置からOffsetとRotationを掛けた値になる
	/// </summary>
	/// <param name="_rotation">セットする回転値(Radian)</param>
	void PositionAndTargetUpdate(const VECTOR &_rotation);
	
	/// <summary>
	/// カメラの位置と注視点を直接指定する
	/// </summary>
	/// <param name="_position">位置</param>
	/// <param name="_target">注視点</param>
	void SetPositionAndTarget(const VECTOR &_position, const VECTOR &_target);

	/// <summary>
	/// 二つの座標が視点に入っているかを確認する
	/// 正方形の場合は両方同じ座標を入れる
	/// </summary>
	/// <param name="_p1">座標1</param>
	/// <param name="_p2">座標2</param>
	/// <return>true : 視界に入っている false : 視界に入っていない</return>
	bool CheckCameraViewClip(const VECTOR &_p1, const VECTOR &_p2);

	void SetNearFar(float _near, float _far);
private:	//Variables
	VECTOR m_offset;	//注視点からの距離
	VECTOR m_target;	//注視点
public:		// Function to get and set variables
	/// <summary>
	/// 現在のOffset値を受け取る
	/// </summary>
	/// <return>現在のOffset値</return>
	const VECTOR & GetOffset() { return m_offset; }
	/// <summary>
	/// Offsetを指定値に変える
	/// </summary>
	/// <param name="_offset">変更するOffsetの値</param>
	void SetOffset(const VECTOR & _offset) { m_offset = _offset; }
	
	/// <summary>
	/// TargetのPositionを受け取る
	/// </summary>
	/// <return>TargetのPosition</return>
	const VECTOR & GetTarget() { return m_target; }
	/// <summary>
	/// Targetを指定値に変える
	/// </summary>
	/// <param name="_offset">変更するOffsetの値</param>
	void SetTarget(const VECTOR & _target) { m_target = _target; }
};