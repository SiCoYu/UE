#pragma once

#include "BaseClassDef.h"
#include "InsResBase.h"

class UTexture;

class TextureInsRes : public InsResBase
{
	M_DECLARE_SUPER_KW(InsResBase);

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