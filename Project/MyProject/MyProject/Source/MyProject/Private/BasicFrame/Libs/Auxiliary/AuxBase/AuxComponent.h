#pragma once

#include "GObject.h"
#include "IDispatchObject.h"
#include "Math/Vector.h"			// FVector
#include "Math/Quat.h"				// FQuat
#include "Math/Rotator.h"			// FRotator
#include "GameFramework/Actor.h"	// AActor
#include <string>
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class AuxComponent : public GObject, public IDispatchObject
{
protected:
	AActor* mSelfActor;      // 自己节点
	AActor* mPreSelfActor;   // 之前自己节点
	bool mIsDestroySelf;     // 是否释放自己
	AActor* mParentActor;       // 指向父节点
	AActor* mPlaceHolderActor;      // 自己节点，资源挂在 mPlaceHolderActor 上， mPlaceHolderActor 挂在 m_pntGo 上
	bool mIsNeedPlaceHolderActor;    // 是否需要占位 AActor*

	bool mIsPosDirty;         // 位置信息是否需要重新设置
	bool mIsRotDirty;         // 旋转信息是否需要重新设置
	bool mIsScaleDirty;         // 缩放信息是否需要重新设置

public:
	AuxComponent();

	virtual void init();
	virtual void dispose();
	virtual void onDestroy();

protected:
	virtual void onPreDestroy();
	virtual void onExecDestroy();
	virtual void onPostDestroy();

public:
	virtual void putInPool();
	virtual void onPutInPool();
	void setSelfName(std::string name_);
	virtual void setSelfActor(AActor* value);
	virtual AActor* getSelfActor();
	bool isDestroySelf();
	void setIsDestroySelf(bool value);
	AActor* getParentActor();
	virtual void setParentActor(AActor* value);
	//Transform getParentTransform();
	bool isNeedPlaceHolderActor();
	void setIsNeedPlaceHolderActor(bool value);
	AActor* getPlaceHolderActor();
	AActor* setPlaceHolderActor(AActor* value);
	bool isSelfValid();

protected:
	bool _isChange(AActor* srcActor, AActor* destActor);
	// 父节点发生改变
	virtual void _onParentChanged();
	// 自己发生改变
	virtual void _onSelfChanged();
	void linkPlaceHolder2Parent();
	void linkSelf2Parent();

public:
	virtual void show();
	virtual void hide();
	virtual bool IsVisible();
	//virtual Transform transform();
	void setPos(FVector original);
	void setRotate(FQuat rotation);
	void setScale(FVector value);
	virtual void updateLocalTransform();
};

MY_END_NAMESPACE