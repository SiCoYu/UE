#ifndef __ClassAssetRes_H
#define __ClassAssetRes_H

#include "InsResBase.h"
#include <string>

class UObject;

class ClassAssetRes : public InsResBase
{
public:
	UObject* mGo;
	UObject* mRetGO;

public:
	ClassAssetRes();
protected:
	virtual void initImpl(ResItem* res) override;

public:
	UObject* InstantiateObject(std::string resName);
	UObject* getObject();
	virtual void unload() override;
};

#endif