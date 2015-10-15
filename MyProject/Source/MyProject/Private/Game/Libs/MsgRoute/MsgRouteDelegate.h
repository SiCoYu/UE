#ifndef __MsgRouteDelegate_H
#define __MsgRouteDelegate_H

#include "FastDelegate.h"

class MsgRouteBase;

typedef fastdelegate::FastDelegate1<MsgRouteBase*> MsgRouteDelegate;
typedef fastdelegate::FastDelegate1<MsgRouteBase*>* MsgRouteDelegatePtr;

#endif