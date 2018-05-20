#pragma once

#include "AuxLoaderBase.h"
#include "BaseClassDef.h"
#include "ResPackType.h"
#include <string>		// std::string
#include "EventDispatchDelegate.h"		// EventDispatchDelegate

using namespace MyNS;

class MaterialInsRes;
class UMaterialInstanceDynamic;
class UMaterialInterface;
class IDispatchObject;

namespace MyNS
{
    class AuxMaterialLoader : public AuxLoaderBase
    {
		M_DECLARE_SUPER_KW(AuxLoaderBase)

	protected :
		MaterialInsRes* mMaterialRes;		// 纹理资源
		UMaterialInterface* mMaterial;
		UMaterialInstanceDynamic* mMaterialDyn;		// 纹理是 Asset-Object 资源，因此卸载这些资源都在 Ins 管理器处理

	public:
		AuxMaterialLoader();
		virtual void dispose() override;

		virtual std::string getOrigPath() override;
		UMaterialInterface* getMaterialInterface();
		UMaterialInstanceDynamic* getMaterialInterfaceDynamic();

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
		void onMaterialLoaded(IDispatchObject* dispObj);
		virtual void unload() override;
	};
}