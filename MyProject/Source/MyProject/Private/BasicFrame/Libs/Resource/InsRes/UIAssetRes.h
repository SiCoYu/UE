#ifndef __PrefabResBase_H
#define __PrefabResBase_H

#include "InsResBase.h"
#include <string>

class UObject;

class UIAssetRes : public InsResBase
{
public:
	UObject* mGo;
	UObject* mRetGO;

public:
	UIAssetRes();
protected:
	virtual void initImpl(ResItem* res) override;

public:
	UObject* InstantiateObject(std::string resName);
	UObject* getObject();
	virtual void unload() override;
};

#endif