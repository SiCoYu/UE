#pragma once

#include <string>
#include "GObject.h"
#include "AuxComponent.h"
#include "TickMode.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class SceneEntityBase;

/**
 * @brief 基本的渲染器，所有与显示有关的接口都在这里，这里基本只提供接口，最基本的实现在 BeingEntityRender 里面
 */
class EntityRenderBase : public AuxComponent
{
	M_DECLARE_CLASS(EntityRenderBase, AuxComponent)

protected:
	SceneEntityBase* mEntity;  // Entity 数据

public:
	EntityRenderBase(SceneEntityBase* entity_);

	virtual void setClientDispose(bool isDispose);
	virtual bool isClientDispose();
	virtual void onTick(float delta, TickMode tickMode);
	// 初始化流程
	virtual void init() override;
	// 初始化事件，仅仅是变量初始化，初始化流程不修改
	virtual void onInit();
	// 销毁流程
	virtual void dispose() override;
	// 资源释放事件，仅仅是释放基本的资源，不修改销毁流程
	virtual void onDestroy() override;
	virtual bool checkRender();
	virtual void load();
	// 场景对象不需要设置，因为如果设置了就检测不了隐藏显示了
	virtual void show() override;
	virtual void hide() override;
	bool isValid();
	FVector getPos();
	virtual void setScale(FVector value);
	// 资源加载完成，初始化一些基本资源
	virtual void _onSelfChanged() override;
	virtual void updateLocalTransform() override;
	virtual void setTexture(std::string path);
};

MY_END_NAMESPACE