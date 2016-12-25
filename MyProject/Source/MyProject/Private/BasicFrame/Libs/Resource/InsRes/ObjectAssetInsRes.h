#ifndef __ObjectAssetInsRes_H
#define __ObjectAssetInsRes_H

#include "InsResBase.h"
#include <string>

class UObject;

class ObjectAssetInsRes : public InsResBase
{
public:
	UObject* mGo;
	UObject* mRetGO;

public:
	ObjectAssetInsRes();
protected:
	virtual void initImpl(ResItem* res) override;

public:
	UObject* InstantiateObject(std::string resName);
	UObject* getObject();
	virtual void unload() override;
};

#endif