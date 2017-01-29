#pragma once

#include "AuxMObjectLoaderBase.h"
#include "BaseClassDef.h"
#include "FormType.h"
#include "ResPackType.h"

using namespace NSFormType;

class UClass;
class UUMGWidget;

namespace MyNS
{
    /**
     * @brief 预制
     */
    class AuxMUIClassLoader : public AuxMObjectLoaderBase
    {
		M_DECLARE_SUPER_KW(AuxMObjectLoaderBase)

	protected:
		UMGOuterType mUMGOuterType;
		UClass* mWidgetClass;
		UUMGWidget* mWidgetObject;

	public:
		AuxMUIClassLoader(std::string path = "", bool isNeedInsPrefab = true, bool isInsNeedCoroutine = true);

	public:
		virtual void onPrefabLoaded(IDispatchObject* dispObj) override;
		void setUMGOuterType(UMGOuterType value);
		UUMGWidget* getWidgetObject();
		void insPrefab();
	};
}