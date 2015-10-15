#ifndef __TimerDelegate_H
#define __TimerDelegate_H

#include "FastDelegate.h"

class TimerItemBase;
class FrameTimerItem;

typedef fastdelegate::FastDelegate1<TimerItemBase*> TimerDelegate;
typedef fastdelegate::FastDelegate1<TimerItemBase*>* TimerDelegatePtr;

typedef fastdelegate::FastDelegate1<FrameTimerItem*> FrameTimerDelegate;
typedef fastdelegate::FastDelegate1<FrameTimerItem*>* FrameTimerDelegatePtr;

#endif