#pragma once

#include <DxLib.h>

namespace DxLib {
	inline float ToRadian(float deg)	{ return deg * DX_PI_F / 180.f; }
	inline float ToDegree(float rad)	{ return rad * 180.f / DX_PI_F; }

	inline VECTOR	operator +	(const VECTOR &in1, const VECTOR &in2)	{	return VAdd(in1, in2);			}
	inline VECTOR&	operator +=	(VECTOR &in1, const VECTOR &in2)		{	return (in1 = VAdd(in1, in2));	}
	inline VECTOR	operator -	(const VECTOR &in1, const VECTOR &in2)	{	return VSub(in1, in2);			}
	inline VECTOR&	operator -=	(VECTOR &in1, const VECTOR &in2)		{	return (in1 = VSub(in1, in2));	}

	inline MATRIX	operator *	(const MATRIX& m1, const MATRIX& m2)	{	return MMult(m1, m2);			}
	inline MATRIX&	operator *=	(MATRIX& m1, const MATRIX& m2)			{	return m1 = MMult(m1, m2);		}
	inline VECTOR	operator *	(const VECTOR& v1, const MATRIX& v2)	{	return VTransform(v1, v2);		}
	inline VECTOR&	operator *=	(VECTOR& v1, const MATRIX& v2)			{	return v1 = VTransform(v1, v2);	}

	inline VECTOR&	operator *	(VECTOR& in, float scale)				{	return VScale(in, scale);		}
	inline VECTOR&	operator *= (VECTOR& in ,float scale)				{	return VScale(in, scale);		}
	inline VECTOR&	operator *	(VECTOR& in1 , VECTOR& in2)				{	return VGet(in1.x * in2.x, in1.y * in2.y, in1.z * in2.z);		}
};