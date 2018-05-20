#pragma once

#include "BaseClassDef.h"
#include "ResInsBase.h"

class UTexture;

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