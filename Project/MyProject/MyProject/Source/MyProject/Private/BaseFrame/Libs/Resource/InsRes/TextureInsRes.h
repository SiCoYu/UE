#pragma once

#include "MClassInfo.h"
#include "MClassMacros.h"
#include "ResInsBase.h"
#include "PlatformDefine.h"

class UTexture;
class ResItem;

MY_BEGIN_NAMESPACE(MyNS)

class TextureInsRes : public ResInsBase
{
	M_DECLARE_CLASS(TextureInsRes, ResInsBase);

protected:
	UTexture* mTexture;

public:
	TextureInsRes();

public:
	UTexture* getTexture();

protected:
	virtual void _initWithResImpl(ResItem* res) override;

public:
	virtual void unload() override;
};

MY_END_NAMESPACE