#ifndef __ITickedObject_H
#define __ITickedObject_H

class ITickedObject
{
public:
    virtual void onTick(float delta) = 0;
};

#endif