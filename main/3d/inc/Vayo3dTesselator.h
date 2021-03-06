/*************************************************************************\
* ��������1.0
* Copyright (c) 2018-2019 authored by ��Ӻ�
* ����ϸ����
\*************************************************************************/
#ifndef __VAYO3D_TESSELATOR_H__
#define __VAYO3D_TESSELATOR_H__

#include "Vayo3dSupport.h"
NS_VAYO3D_BEGIN

enum ETessWinding
{
	ETW_WINDING_ODD,
	ETW_WINDING_NONZERO,
	ETW_WINDING_POSITIVE,
	ETW_WINDING_NEGATIVE,
	ETW_WINDING_ABS_GEQ_TWO
};

class Tesselator
{
public:
	typedef void(*TessBeginDataProc)   (unsigned int, void*);
	typedef void(*TessVertexDataProc)  (void*, void*);
	typedef void(*TessEndDataProc)     (void*);
	typedef void(*TessErrorDataProc)   (unsigned int, void*);
	typedef void(*TessCombineDataProc) (double[3], void*[4], float[4], void**, void*);
public:
	virtual ~Tesselator() {}
	virtual void beginPolygon(void* data) = 0;
	virtual void beginContour() = 0;
	virtual void vertex(VertIdxPair* vert) = 0;
	virtual void endContour() = 0;
	virtual void endPolygon() = 0;
	virtual void setBeginCallback(TessBeginDataProc pBegin) = 0;
	virtual void setVertexCallback(TessVertexDataProc pVertex) = 0;
	virtual void setEndCallback(TessEndDataProc pEnd) = 0;
	virtual void setErrorCallback(TessErrorDataProc pError) = 0;
	virtual void setCombineCallback(TessCombineDataProc pCombine) = 0;
	virtual void setWindingProperty(ETessWinding value) = 0;
};

NS_VAYO3D_END

#endif // __VAYO3D_TESSELATOR_H__
