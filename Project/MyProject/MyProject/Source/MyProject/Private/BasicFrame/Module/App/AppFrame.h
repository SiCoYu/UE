#ifndef __AppFrame_H
#define __AppFrame_H

#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class AppFrame : public GObject
{
public:
	static AppFrame* msAppFrame;

public:
	static void initApp();
	static void quitApp();

public:
	void init();
	void dispose();
};

MY_END_NAMESPACE

#endif				// __AppFrame_H