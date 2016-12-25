#ifndef __ClassAssetInsRes_H
#define __ClassAssetInsRes_H

#include "InsResBase.h"
#include <string>

class UClass;

class ClassAssetInsRes : public InsResBase
{
public:
	UClass* mGo;
	UClass* mRetGO;

public:
	ClassAssetInsRes();

protected:
	virtual void initImpl(ResItem* res) override;

public:
	UObject* InstantiateObject(std::string resName);
	UClass* getObject();
	virtual void unload() override;
};

#endif