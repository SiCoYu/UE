#pragma once

#include "AuxLoaderBase.h"
#include <string>
#include "EventDispatchDelegate.h"
#include "BaseClassDef.h"
#include "GameFramework/Actor.h"	// AActor
#include "UObject/Object.h"	// UObject
#include "ResPackType.h"
#include "CoreInc.h"

class ObjectAssetInsResBase;
class ResInsEventDispatch;

namespace MyNS
{
    /**
     * @brief 预制
     */
    class AuxMObjectLoaderBase : public AuxLoaderBase
    {
		M_DECLARE_SUPER_KW(AuxLoaderBase)
		M_DECLARE_CLASS(AuxMObjectLoaderBase)

	protected:
		UObject* mSelfGo;                       // 加载的 GameObject
		ObjectAssetInsResBase* mPrefabRes;                     // 预制资源
        ResInsEventDispatch* mResInsEventDispatch; // 实例化的时候使用的分发器
        bool mIsInsNeedCoroutine; // 实例化是否需要协程
        bool mIsDestroySelf;      // 是否释放自己
        bool mIsNeedInsPrefab;    // 是否需要实例化预制

        bool mIsSetFakePos;       // 是否初始化的时候设置到很远的位置
        bool mIsSetInitOrientPos; // 是否 Instantiate 的时候，设置初始化方向位置信息， UI 是不需要的，UI 的初始化信息都保存在 Prefab 里面，直接从 Prefab 里面读取就行了，如果设置了不对的位置信息，可能位置就不对了
        ResInsEventDispatch* mInsEventDispatch;
		ResPackType mResPackType;    // 资源打包类型

	public:
		AuxMObjectLoaderBase(std::string path = "", bool isNeedInsPrefab = true, bool isInsNeedCoroutine = true);
		void setIsInitOrientPos(bool isSet);
		void setIsFakePos(bool isSet);

		virtual void dispose() override;

		UObject* getSelfGo();
		void setSelfGo(UObject* value);
		bool isDestroySelf();
		void setDestroySelf(bool value);
		virtual std::string getOrigPath() override;

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
		virtual void onPrefabLoaded(IDispatchObject* dispObj);
		void onPrefabIns(IDispatchObject* dispObj);
        // 所有的资源都加载完成
		void onAllFinish();
		virtual void unload() override;
		UObject* getGameObject();

        // 获取预制模板
		UObject* getPrefabTmpl();
		void setClientDispose(bool isDispose);
		bool isClientDispose();
		UObject* InstantiateObject(EventDispatchDelegate insHandle = nullptr);
		void onInstantiateObjectFinish(IDispatchObject* dispObj = nullptr);
	};
}