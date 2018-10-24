/*************************************************************************\
* ��������1.0
* Copyright (c) 2018-2018 author by ��Ӻ�
* �����
\*************************************************************************/
#ifndef __VAYO_CAMERA_H__
#define __VAYO_CAMERA_H__

#include "VayoInput.h"
#include "VayoBitState.h"
#include "VayoMatrix4x4.h"
#include "VayoArcball.h"
#include "VayoFrustum.h"
#include "VayoMovableObject.h"

NS_VAYO_BEGIN

// �����
class _VayoExport Camera : public TouchDelegate, public KeypadDelegate
{
public:
	enum EType
	{
		ET_PERSPECTIVE,
		ET_ORTHOGONAL
	};

	Camera();
	virtual ~Camera();
	virtual void  refresh();
	virtual void  setNeedUpdate(bool isUpdate);
	virtual EType getType() { return ET_PERSPECTIVE; }
	virtual bool  getWorldPos(Vector3df& outWorldPos) const;
	virtual bool  getWorldLook(Vector3df& outWorldLook) const;

	virtual const Vector3df& getRight() const;
	virtual const Vector3df& getUp() const;
	virtual const Vector3df& getLook() const;

	virtual void setLens(float fovY, float aspect, float zn, float zf);
	virtual void lookAt(const Vector3df& pos, const Vector3df& target = Vector3df::Origin, const Vector3df& worldUp = Vector3df::YAxis);

	virtual const Matrix4x4& getView() const;
	virtual const Matrix4x4& getProj() const;

	virtual void             setViewAffector(const Matrix4x4& affector);
	virtual const Matrix4x4& getViewAffector() const;

	virtual void strafe(float d);
	virtual void fly(float d);
	virtual void walk(float d);

	virtual void pitch(float angle);
	virtual void yaw(float angle);
	virtual void roll(float angle);

	virtual void rotateX(float angle);
	virtual void rotateY(float angle);
	virtual void rotateZ(float angle);

	virtual void transform(const Matrix4x4& mat, bool bRotationOnly=false);

	virtual float getNearZ() const;
	virtual float getFarZ() const;
	virtual float getFovY() const;
	virtual float getFovX() const;
	virtual float getAspect() const;

	virtual float getNearWindowWidth() const;
	virtual float getNearWindowHeight() const;
	virtual float getFarWindowWidth() const;
	virtual float getFarWindowHeight() const;

	virtual const Frustum& getViewFrustum() const;

	virtual void createViewMemento(const wstring& name) = 0;
	virtual void restoreViewMemento(const wstring& name) = 0;

	class ViewMemento
	{
	public:
		Vector3df _position;
		Vector3df _right;
		Vector3df _up;
		Vector3df _look;
		virtual ~ViewMemento() {}
	};

protected:
	virtual void updateViewTransform();
	virtual void rebuildViewArea();
	virtual void recalculateViewArea();
	map<wstring, ViewMemento*> _viewMementoPool;
protected:
	bool      _needUpdate;
	Vector3df _position;
	Vector3df _right;
	Vector3df _up;
	Vector3df _look;
	Matrix4x4 _view;
	Matrix4x4 _affector;
	float     _nearZ;
	float     _farZ;
	float     _fovY;
	float     _aspect;
	float     _nearWindowHeight;
	float     _farWindowHeight;
	Frustum   _viewArea;
};

// ��һ�˳������
/**
 * Serialized template:
 * <FPSCamera name="��һ�˳������" position="0,0,100" target="0,0,0" worldUp="0,1,0" fovY="45"  zn="1" zf="1000" moveSpeed="100"/>
**/
class _VayoExport FPSCamera : public MovableObject, public Camera
{
public:
	FPSCamera(const wstring& name);
	~FPSCamera();
	void update(float dt);
	void setMoveSpeed(float speed);
	void touchMoved(const Touch& touch, EMouseKeys key);
	bool keyClicked(const tagKeyInput& keyInput);
	void createViewMemento(const wstring& name);
	void restoreViewMemento(const wstring& name);
	void serialize(XMLElement* outXml);
	bool deserialize(XMLElement* inXml);

protected:
	void rebuildViewArea();
protected:
	float    _moveSpeed[2];
	BitState _direction;
};

// ��������
/**
 * Serialized template:
 * <OrbitCamera name="��������" position="0,0,100" target="0,0,0" worldUp="0,1,0" fovY="45" zn="1" zf="1000" moveSpeed="10" zoomSpeed="2"/>
**/
class _VayoExport OrbitCamera : public MovableObject, public Camera
{
public:
	OrbitCamera(const wstring& name);
	~OrbitCamera();
	void update(float dt);
	void setMoveSpeed(float speed);
	void setZoomSpeed(float speed);
	void setLens(float fovY, float aspect, float zn, float zf);
	void lookAt(const Vector3df& pos, const Vector3df& target = Vector3df::Origin, const Vector3df& worldUp = Vector3df::YAxis);
	bool touchBegan(const Touch& touch, EMouseKeys key);
	void touchMoved(const Touch& touch, EMouseKeys key);
	void touchEnded(const Touch& touch, EMouseKeys key);
	bool touchWheel(const Touch& touch, float wheel);
	bool keyClicked(const tagKeyInput& keyInput);
	void createViewMemento(const wstring& name);
	void restoreViewMemento(const wstring& name);
	void serialize(XMLElement* outXml);
	bool deserialize(XMLElement* inXml);

protected:
	void rebuildViewArea();
protected:
	float   _moveSpeed[2];
	float   _zoomSpeed[2];
	Arcball _arcball;
};

// ӥ�������
/**
 * Serialized template:
 * TODO
**/
class _VayoExport EagleEyeCamera : public OrbitCamera
{
public:
	EagleEyeCamera(const wstring& name);
	~EagleEyeCamera();
	void  update(float dt);
	EType getType() { return ET_ORTHOGONAL; }
	void  setZoomFactor(float zoom);
	void  setLens(float widthOfViewVolume, float heightOfViewVolume, float zn, float zf);
	float getFovY() const;
	float getFovX() const;
	float getNearWindowWidth() const;
	float getNearWindowHeight() const;
	float getFarWindowWidth() const;
	float getFarWindowHeight() const;
	bool  touchBegan(const Touch& touch, EMouseKeys key);
	void  touchMoved(const Touch& touch, EMouseKeys key);
	void  touchEnded(const Touch& touch, EMouseKeys key);
	bool  touchWheel(const Touch& touch, float wheel);
	bool  keyClicked(const tagKeyInput& keyInput);
	void  createViewMemento(const wstring& name);
	void  restoreViewMemento(const wstring& name);
	void  serialize(XMLElement* outXml);
	bool  deserialize(XMLElement* inXml);

protected:
	float    _zoomFactor;
	BitState _direction;
};

NS_VAYO_END

#endif // __VAYO_CAMERA_H__
