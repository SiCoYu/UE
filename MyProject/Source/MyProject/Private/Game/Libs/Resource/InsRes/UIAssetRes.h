#ifndef __PrefabResBase_H
#define __PrefabResBase_H

#include "InsResBase.h"
#include <string>

class UIAssetRes : public InsResBase
{
public:
	GameObject m_go;
	GameObject m_retGO;

public:
	UIAssetRes();
protected:
	virtual void initImpl(ResItem* res) override;

public:
	GameObject InstantiateObject(std::string resName);
	GameObject getObject();
	virtual void unload() override;
};

#endif