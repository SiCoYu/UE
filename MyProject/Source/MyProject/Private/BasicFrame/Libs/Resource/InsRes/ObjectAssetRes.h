#ifndef __ObjectAssetRes_H
#define __ObjectAssetRes_H

#include "InsResBase.h"
#include <string>

class UObject;

class ObjectAssetRes : public InsResBase
{
public:
	UObject* mGo;
	UObject* mRetGO;

public:
	ObjectAssetRes();
protected:
	virtual void initImpl(ResItem* res) override;

public:
	UObject* InstantiateObject(std::string resName);
	UObject* getObject();
	virtual void unload() override;
};

#endif