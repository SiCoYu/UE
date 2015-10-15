#ifndef __ITickedObject_H
#define __ITickedObject_H

class ITickedObject
{
    virtual void onTick(float delta) = 0;
};

#endif