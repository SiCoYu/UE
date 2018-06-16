#pragma once

#include <string>
#include "SceneEntityRenderBase.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class SceneEntityBase;
class IDispatchObject;
class SceneEntityRenderBase;
class AuxMObjectLoader;

class BeingEntityRender : public SceneEntityRenderBase
{
	M_DECLARE_CLASS(BeingEntityRender, SceneEntityRenderBase)

protected:
	AuxMObjectLoader* mAuxPrefabLoader;
	std::string mResPath;  // 资源目录

public:
	/**
	 * @brief 资源加载之类的基本操作写在这里
	 */
	BeingEntityRender(SceneEntityBase* entity_);

	void setResPath(std::string path);
	virtual void onDestroy() override;
	virtual void onPutInPool() override;

protected:
	// 仅仅是释放资源
	virtual void releaseRes();

public:
	virtual void updateLocalTransform() override;
	// 资源加载
	virtual void load() override;
	virtual void onResLoaded(IDispatchObject* dispObj, uint uniqueId);
	virtual void attachToParentNode(SceneEntityRenderBase* render);

protected:
	virtual void _onSelfChanged() override;
};

MY_END_NAMESPACE