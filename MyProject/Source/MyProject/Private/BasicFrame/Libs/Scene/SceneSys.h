#pragma once

#include "EventDispatchDelegate.h"
#include <string>

class AddOnceAndCallOnceEventDispatch;
class Scene;
class AuxLevelLoader;
class IDispatchObject;

/**
 * @brief 同一时刻只能有一个场景存在
 */

class SceneSys
{
protected:
	AddOnceAndCallOnceEventDispatch* mOnSceneLoadedDispatch;
    Scene* mScene;
    AuxLevelLoader* mAuxLevelLoader;

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