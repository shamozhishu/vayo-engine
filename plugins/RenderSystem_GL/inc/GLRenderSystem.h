/*************************************************************************\
* 望友引擎1.0
* Copyright (c) 2018-2019 authored by 朱加浩
* OpenGL渲染系统
\*************************************************************************/
#ifndef __GL_RENDER_SYSTEM_H__
#define __GL_RENDER_SYSTEM_H__

#include "GLSupport.h"
#include "Vayo3dRenderSystem.h"

class GLRenderSystem : public RenderSystem
{
	DISALLOW_COPY_AND_ASSIGN(GLRenderSystem)
public:
	GLRenderSystem(const wstring& name);
	~GLRenderSystem();

	TexturePtr   createTexture(const wstring& filename, Image* image, bool generateMipLevels);
	DisplayList* createDisplayList();
	Tesselator*  createTesselator();

	bool init(unsigned char antiAliasFactor = 0, bool handleSRGB = false);
	bool isActive() const;
	void restoreContext() const;
	bool beginScene(bool backBuffer, bool zBuffer, bool stencilBuffer, Device* renderWnd);
	bool endScene();
	const Matrix4x4& getTransform(ETransformState state) const;
	void setTransform(ETransformState state, const Matrix4x4& mat);
	const Dimension2di& getCurRenderTargetSize() const;
	void setViewpot(const Recti& area);
	void setAmbientLight(const Colour& color);
	void setMaterial(const Material& material);
	bool setWndPixelFormat(Device* renderWnd);
	void addDynamicLight(const LightData& light);
	void removeAllDynamicLights();

	void drawDisplayList(DisplayList* displayList);
	void drawPixel(int x, int y, const Colour& color);
	void draw2DLine(const Position2di& startPos, const Position2di& endPos, Colour color = Colour(255, 255, 255, 255));
	void draw3DLine(const Vector3df& start, const Vector3df& end, Colour color = Colour(255, 255, 255, 255));
	void draw2DRect(const Recti& rc, Colour colorLeftUp, Colour colorRightUp, Colour colorLeftDown, Colour colorRightDown, const Recti* clip = NULL);

	void draw2DImage(TexturePtr texture, const Position2di& destPos,
		const Recti& sourceRect, const Recti* clipRect = NULL,
		Colour color = Colour(255, 255, 255, 255), bool useAlphaChannelOfTexture = false);

	void draw2DImage(TexturePtr texture, const Recti& destRect,
		const Recti& sourceRect, const Recti* clipRect = NULL,
		const Colour* const colors = NULL, bool useAlphaChannelOfTexture = false);

	void draw2DImageBatch(TexturePtr texture,
		const vector<Position2di>& positions,
		const vector<Recti>& sourceRects,
		const Recti* clipRect = NULL,
		Colour color = Colour(255, 255, 255, 255),
		bool useAlphaChannelOfTexture = false);

	void draw2DImageBatch(TexturePtr texture,
		const vector<Recti>& destRects,
		const vector<Recti>& sourceRects,
		const Recti* clipRect = NULL,
		const vector<Colour>* colors = NULL,
		bool useAlphaChannelOfTexture = false);

	void              testGLErrorBegan();
	bool              testGLErrorEnded(const wstring& errLog = L"");
	EColorFormat      getColorBufferFormat() const { return _colorBufferFormat; }
	ERenderSystemType getRenderSystemType() const { return ERST_OPENGL; }
	unsigned int      getMaximalPrimitiveCount() const { return 0x7fffffff; }
	bool              setActiveTexture(int stage, Texture* texture);
	bool              disableTextures(int fromStage = 0);

	int addShaderMaterial(const char* vertexShaderProgram = "",
		const char* pixelShaderProgram = "",
		ShaderConstantSetCallback* callback = NULL,
		EMaterialType baseMaterial = EMT_SOLID);

	void setRenderMode3D();
	void setRenderMode2D(bool alpha, bool texture, bool alphaChannel);
	void setBasicRenderStates(const Material& material, const Material& lastMaterial, bool resetAllRenderStates);
	void fillingDisplayList(bool isFilling) { _isFillDisplayList = isFilling; }

protected:
	void drawVertexPrimitiveListBegan(const void* vertices, unsigned int vertexCount);
	void drawVertexPrimitiveList(const unsigned int* indexList, unsigned int primitiveCount, EPrimitiveType primType);
	void drawVertexPrimitiveListEnded();

	typedef struct tagHardwareBufferLink_OpenGL : public HardwareBufferLink
	{
		GLuint VBO_verticesID;
		GLuint EBO_indicesID;
		GLuint VBO_verticesSize;
		GLuint EBO_indicesSize;

		tagHardwareBufferLink_OpenGL(SubMesh* meshBuffer)
			: HardwareBufferLink(meshBuffer)
			, VBO_verticesID(0)
			, EBO_indicesID(0)
			, VBO_verticesSize(0)
			, EBO_indicesSize(0) {}
	} HardwareBufferLink_OpenGL;

	HardwareBufferLink* createHardwareBuffer(SubMesh* mb);
	bool updateHardwareBuffer(HardwareBufferLink* hwBuffer);
	void drawHardwareBuffer(HardwareBufferLink* hwBuffer);
	HardwareBufferLinkItor deleteHardwareBuffer(HardwareBufferLink* hwBuffer);

private:
	void  setWrapMode(const Material& material);
	bool  changeRenderContext(Device* renderWnd);
	GLint getTextureWrapMode(unsigned char clamp);
	void  getGLTextureMatrix(GLfloat gl_matrix[16], const Matrix4x4& mat);
	void  gainVertexColorBuffer(const void* vertices, unsigned int vertexCount);
	void  renderArray(const void* indexList, unsigned int primitiveCount, EPrimitiveType primType);
	void  createMaterialRenderers();
	bool  updateVertexHardwareBuffer(HardwareBufferLink_OpenGL* hwBuffer);
	bool  updateIndexHardwareBuffer(HardwareBufferLink_OpenGL* hwBuffer);

private:
	HDC   _hCurrentDC;
	HGLRC _hCurrentRC;
	HWND  _hCurrentWnd;
	int   _pixelFormat;
	PROPERTY_R(GLint, _maxTextureSize, MaxTextureSize)
private:
	enum ERenderMode
	{
		ERM_NONE,
		ERM_2D,
		ERM_3D
	};
	ERenderMode           _currentRenderMode;
	EColorFormat          _colorBufferFormat;
	Matrix4x4             _matrizes[ETS_COUNT];
	vector<unsigned char> _vertexColorBuffer;
	Material              _curMaterial;
	Material              _lastMaterial;
	int                   _lastSetLight;
	int                   _maxTextureUnits;
	unsigned char         _antiAliasFactor;
	float                 _maxTextureLODBias;
	Dimension2di          _currentRenderTargetSize;
	bool                  _resetRenderStates;
	bool                  _transformation3DChanged;
	bool                  _isFillDisplayList;
	GLfloat               _dimAliasedLine[2];
	GLfloat               _dimAliasedPoint[2];
	GLfloat               _dimSmoothedLine[2];
	GLfloat               _dimSmoothedPoint[2];
	Texture*              _texturesUnitSet[MATERIAL_MAX_TEXTURES];
};

#endif // __GL_RENDER_SYSTEM_H__
