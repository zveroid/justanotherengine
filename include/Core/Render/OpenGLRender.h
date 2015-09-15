#ifndef COPENGLRENDER_H
#define COPENGLRENDER_H

#include "Core/Render/Render.h"

class COpenGLRender : public IRender
{
public:
    COpenGLRender();
    virtual ~COpenGLRender();

    virtual bool Init(IDevice* _device) override;
    virtual void Deinit() override;
    virtual void Draw() override;

private:
#ifdef WIN32
	bool	InitWin32(CWin32Device* _device);
	HGLRC	m_RenderContext;
#endif
};

#endif // COPENGLRENDER_H
