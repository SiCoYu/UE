#include "MyProject.h"
#include "GObject.h"

GObject::GObject()
{
    mTypeId = "GObject";
}

std::string GObject::getTypeId()
{
    return mTypeId;
}