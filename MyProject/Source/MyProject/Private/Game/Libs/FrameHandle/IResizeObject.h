#ifndef __IResizeObject_H
#define __IResizeObject_H

class IResizeObject
{
    virtual void onResize(int viewWidth, int viewHeight) = 0;
};

#endif