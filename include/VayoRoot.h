/*************************************************************************\
* ��������1.0
* Copyright (c) 2018-2018 author by ��Ӻ�
* �������
\*************************************************************************/
#ifndef __VAYO_ROOT_H__
#define __VAYO_ROOT_H__

#include "VayoSupport.h"
#include "VayoTimer.h"
#include "VayoColour.h"
#include "VayoSingleton.h"
#include "VayoDimension2d.h"
NS_VAYO_BEGIN

class _VayoExport Root : public Singleton<Root>
{
public:
	typedef struct tagInitConfig
	{
		bool         PostQuit;
		bool         OwnerDraw;
		bool         FullScreen;
		Colour       BgClearColor;
		Dimension2di WindowSize;
		wstring      WindowName;
		wstring      RendererName;
		wstring      RootDirectory;
		void*        WindowId;
		tagInitConfig()
			: PostQuit(true)
			, OwnerDraw(false)
			, FullScreen(false)
			, BgClearColor(0)
			, WindowSize(1280, 720)
			, WindowName(L"VayoEngine1.0")
			, RendererName(L"RenderSystem_GL")
			, WindowId(NULL) {}
	} InitConfig;

public:
	Root(const InitConfig& initConfig);
	~Root();
	bool          launch();
	bool          renderOneFrame();
	bool          isOwnerDraw() const;
	bool          isFullscreen() const;
	bool          isQuitWhenCloseWnd() const;
	Timer&        getTimer() { return _timer; }
	int           getFrameCnt() { return _frameCnt; }
	float         getMsOneFrame() { return _msOneFrame; }
	void          addRenderSystem(RenderSystem* newRenderer);

	bool          loadScene(const wstring& xmlFileName);
	SceneManager* findSceneMgr(const wstring& sceneName);
	SceneManager* createSceneMgr(const wstring& sceneName = L"");
	void          destroySceneMgr(const wstring& sceneName);
	void          destroySceneMgr(SceneManager* pSceneMgr);
	void          destroyAllSceneMgrs();

	// ������
	void loadPlugins();
	void initialisePlugins();
	void shutdownPlugins();
	void unloadPlugins();
	void loadPlugin(const wstring& pluginName);
	void unloadPlugin(const wstring& pluginName);
	void installPlugin(Plugin* plugin);
	void uninstallPlugin(Plugin* plugin);
	const vector<Plugin*>& getInstalledPlugins() const { return _plugins; }

private:
	Timer                       _timer;
	int                         _frameCnt;
	float                       _msOneFrame;
	InitConfig                  _initConfig;
	map<wstring, SceneManager*> _sceneMgrPool;
	map<wstring, RenderSystem*> _renderers;
	vector<Plugin*>             _plugins;
	vector<DynLib*>             _pluginLibs;

private:
	void updateFrameStats();

protected:
	PROPERTY_R(bool,              _isInit,           IsInit)
	PROPERTY_RW(SceneManager*,    _curSceneMgr,      CurSceneMgr)
	PROPERTY_RW(ScriptSystem*,    _scriptSystem,     ScriptSystem)
	PROPERTY_R(RenderSystem*,     _activeRenderer,   ActiveRenderer)
	PROPERTY_R(DynLibManager*,    _dynLibManager,    DynLibManager)
	PROPERTY_R(KeypadDispatcher*, _keypadDispatcher, KeypadDispatcher)
	PROPERTY_R(TouchDispatcher*,  _touchDispatcher,  TouchDispatcher)
	PROPERTY_R(Device*,           _device,           Device)
	PROPERTY_R(ConfigManager*,    _configManager,    ConfigManager)
	PROPERTY_R(DatabaseCSV*,      _csvDatabase,      DatabaseCSV)
	PROPERTY_R(Language*,         _language,         Language)
	PROPERTY_R(UIManager*,        _uiManager,        UIManager)
	PROPERTY_R(TextureManager*,   _textureManager,   TextureManager)
	PROPERTY_R(MaterialManager*,  _materialManager,  MaterialManager)
	PROPERTY_R(MeshManager*,      _meshManager,      MeshManager)
};

NS_VAYO_END

#endif // __VAYO_ROOT_H__