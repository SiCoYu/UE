#ifndef __ClassAssetRes_H
#define __ClassAssetRes_H

#include "InsResBase.h"
#include <string>

class UClass;

class ClassAssetRes : public InsResBase
{
public:
	UClass* mGo;
	UClass* mRetGO;

public:
	ClassAssetRes();

protected:
	virtual void initImpl(ResItem* res) override;

public:
	UObject* InstantiateObject(std::string resName);
	UClass* getObject();
	virtual void unload() override;
};

#endif