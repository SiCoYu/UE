#include "MyProject.h"
#include "Scene.h"

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