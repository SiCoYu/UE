#ifndef __AppFrame_H
#define __AppFrame_H

#include "GObject.h"

class AppFrame : public GObject
{
public:
	void initApp();
	void quitApp();
};

#endif				// __AppFrame_H