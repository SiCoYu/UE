#pragma once

#include <string>		// std::string

#include "AuxLoaderBase.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "ResPackType.h"
#include "TypeDef.h"
#include "EventDispatchDelegate.h"		// EventDispatchDelegate
#include "PlatformDefine.h"

class UMaterialInstanceDynamic;
class UMaterialInterface;

MY_BEGIN_NAMESPACE(MyNS)

class MaterialInsRes;
class IDispatchObject;

class AuxMaterialLoader : public AuxLoaderBase
{
	M_DECLARE_CLASS(AuxMaterialLoader, AuxLoaderBase)

protected :
	MaterialInsRes* mMaterialRes;		// 纹理资源
	UMaterialInterface* mMaterial;
	UMaterialInstanceDynamic* mMaterialDyn;		// 纹理是 Asset-Object 资源，因此卸载这些资源都在 Ins 管理器处理

public:
	AuxMaterialLoader();

	virtual void dispose() override;

	virtual std::string& getOrigPath() override;
	UMaterialInterface* getMaterialInterface();
	UMaterialInstanceDynamic* getMaterialInterfaceDynamic();

	virtual void syncLoad(
		std::string path,
		EventDispatchDelegate evtHandle = EventDispatchDelegate(),
		EventDispatchDelegate progressHandle = EventDispatchDelegate()
	) override;

    // 异步加载对象
	virtual void asyncLoad(
		std::string path,
		EventDispatchDelegate evtHandle,
		EventDispatchDelegate progressHandle = EventDispatchDelegate()
	) override;

	void onMaterialLoaded(uint eventId, IDispatchObject* dispObj);
	virtual void unload() override;
};

MY_END_NAMESPACE