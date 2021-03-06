/*************************************************************************\
* 望友引擎1.0
* Copyright (c) 2018-2019 authored by 朱加浩
* Direct2D支持
\*************************************************************************/
#ifndef __D2D_SUPPORT_H__
#define __D2D_SUPPORT_H__

#include "Vayo2dSupport.h"
#include "VayoLog.h"

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <dwmapi.h>
#include <wrl.h>

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dwrite.lib")
#ifdef _DEBUG
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")
#endif
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "windowscodecs.lib")
#pragma comment(lib, "Winmm.lib")

template<typename T>
using ComPtr = Microsoft::WRL::ComPtr<T>;

using namespace Vayo;
using namespace Vayo::_2d;
class D2DBitmap;
class D2DRenderer;
class D2DPaintbrush;
class D2DPicProcessor;

extern void printComError(HRESULT hr);

#endif // __D2D_SUPPORT_H__
