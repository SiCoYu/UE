#pragma once

#include "EventDispatchDelegate.h"
#include <string>
#include "AuxLevelLoader.h"	// AuxLevelLoader, Namespace 必须包含
#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class AddOnceAndCallOnceEventDispatch;
class Scene;
class IDispatchObject;

/**
 * @brief 同一时刻只能有一个场景存在
 */

class SceneSys : public GObject
{
protected:
	AddOnceAndCallOnceEventDispatch* mOnSceneLoadedDispatch;
    Scene* mScene;
	MyNS::AuxLevelLoader* mAuxLevelLoader;

public:
	SceneSys();

public:
	void init();
	void dispose();

	Scene* getCurScene();
	bool isSceneLoaded();
	void loadScene(std::string filename, EventDispatchDelegate func);
	void unloadScene();
	void loadSceneRes(std::string filename);
	void onSceneResLoadded(IDispatchObject* dispObj);
    // 卸载多有的场景
	void unloadAll();
};

MY_END_NAMESPACE