#include "MyProject.h"
#include "Scene.h"

MY_BEGIN_NAMESPACE(MyNS)

Scene::Scene()
{
	this->mIsSceneLoaded = false;
}

void Scene::init()
{
	this->mIsSceneLoaded = true;
}

void Scene::dispose()
{

}

bool Scene::isSceneLoaded()
{
	return this->mIsSceneLoaded;
}

MY_END_NAMESPACE