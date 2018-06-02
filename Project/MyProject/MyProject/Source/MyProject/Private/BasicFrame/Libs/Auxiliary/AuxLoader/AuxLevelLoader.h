#pragma once

#include "AuxLoaderBase.h"
#include "BaseClassDef.h"
#include <string>
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class LevelResItem;
class LoadParam;

/**
 * @brief 关卡加载
 */
class AuxLevelLoader : public AuxLoaderBase
{
	M_DECLARE_SUPER_KW(AuxLoaderBase)

protected:
	LevelResItem* mLevelResItem;

public:
	AuxLevelLoader(std::string path = "");
	virtual void dispose() override;
	virtual void syncLoad(
		std::string path, 
		EventDispatchDelegate evtHandle = nullptr,
		EventDispatchDelegate progressHandle = nullptr
	) override;
    // 异步加载对象
	virtual void asyncLoad(
		std::string path, 
		EventDispatchDelegate evtHandle,
		EventDispatchDelegate progressHandle = nullptr
	) override;
	void onLevelLoaded(IDispatchObject* dispObj);
	virtual void unload() override;
};

MY_END_NAMESPACE