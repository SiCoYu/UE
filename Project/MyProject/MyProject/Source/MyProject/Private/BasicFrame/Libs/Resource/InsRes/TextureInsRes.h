#pragma once

#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

class UTexture;

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
	virtual void initImpl(ResItem* res) override;

public:
	virtual void unload() override;
};

MY_END_NAMESPACE