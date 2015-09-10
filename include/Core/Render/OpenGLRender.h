#ifndef COPENGLRENDER_H
#define COPENGLRENDER_H

#include "Core/Render/Render.h"

class COpenGLRender : public IRender
{
public:
    COpenGLRender();
    virtual ~COpenGLRender();

    virtual bool Init() override;
    virtual bool Deinit() override;
    virtual void Draw() override;
};

#endif // COPENGLRENDER_H
