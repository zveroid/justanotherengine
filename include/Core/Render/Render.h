#ifndef RENDER_H
#define RENDER_H

class IRender
{
    virtual bool Init() = 0;
    virtual bool Deinit() = 0;
    virtual void Draw() = 0;
};

#endif // RENDER_H

