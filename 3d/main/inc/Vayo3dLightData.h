/*************************************************************************\
* ��������1.0
* Copyright (c) 2018-2019 authored by ��Ӻ�
* �ƹ�����
\*************************************************************************/
#ifndef __VAYO3D_LIGHT_DATA_H__
#define __VAYO3D_LIGHT_DATA_H__

#include "Vayo3dColour.h"
#include "math/VayoVector3d.h"
NS_VAYO3D_BEGIN

enum ELightType
{
	ELT_DIRECTIONAL_LIGHT = 0, // �����
	ELT_POINT_LIGHT,           // ���Դ
	ELT_SPOT_LIGHT             // �۹��
};

class _Vayo3dExport LightData
{
public:
	LightData() : _lightType((ELightType)-1) {}
	ELightType  _lightType;
	Colour      _ambientColor;
	Colour      _diffuseColor;
	Colour      _specularColor;
	Vector3df   _position;
	float       _range;
	Vector3df   _att;
	Vector3df   _direction;
	float       _exponent;
	float       _cutoff;
};

NS_VAYO3D_END

#endif // __VAYO3D_LIGHT_DATA_H__