#pragma once

#include "BaseClassDef.h"
#include "ResInsBase.h"
#include "PlatformDefine.h"

class UTexture;

MY_BEGIN_NAMESPACE(MyNS)

class TextureInsRes : public ResInsBase
{
	M_DECLARE_SUPER_KW(ResInsBase);

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