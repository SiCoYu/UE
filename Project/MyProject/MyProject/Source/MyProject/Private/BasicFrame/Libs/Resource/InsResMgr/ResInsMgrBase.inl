#ifndef __ResInsMgrBase_H
#error "ResInsMgrBase.inl file can only include in ResInsMgrBase.h"
#endif

template<class T>
T* ResInsMgrBase::getAndSyncLoad(std::string path, EventDispatchDelegate handle)
{
	this->syncLoad<T>(path, handle);
	return (T*)this->getRes(path);
}

template<class T>
T* ResInsMgrBase::getAndAsyncLoad(std::string path, EventDispatchDelegate handle)
{
	T* ret = nullptr;
	LoadParam* param = GPoolSys->newObject<LoadParam>();

	//LocalFileSys.modifyLoadParam(path, param);
	param->setPath(path);
	param->setIsLoadNeedCoroutine(true);
	param->setIsResNeedCoroutine(true);
	param->setLoadEventHandle(handle);
	param->setResPackType(this->getResPackType());

	ret = this->getAndLoad<T>(param);

	GPoolSys->deleteObj(param);

	return ret;
}

template<class T>
T* ResInsMgrBase::getAndLoad(LoadParam* param)
{
	this->load<T>(param);
	return (T*)this->getRes(param->getPath());
}

// 同步加载，立马加载完成，并且返回加载的资源， syncLoad 同步加载资源不能和异步加载资源的接口同时去加载一个资源，如果异步加载一个资源，这个时候资源还没有加载完成，然后又同步加载一个资源，这个时候获取的资源是没有加载完成的，由于同步加载资源没有回调，因此即使同步加载的资源加载完成，也不可能获取加载完成事件
template<class T>
void ResInsMgrBase::syncLoad(std::string path, EventDispatchDelegate handle)
{
	LoadParam* param;
	param = GPoolSys->newObject<LoadParam>();

	param->setPath(path);
	// param->mLoadEventHandle = onLoadEventHandle;        // 这个地方是同步加载，因此不需要回调，如果写了，就会形成死循环， ResInsBase 中的 init 又会调用 onLoadEventHandle 这个函数，这个函数是外部回调的函数，由于同步加载，没有回调，因此不要设置这个 param.mLoadEventHandle = onLoadEventHandle ，内部会自动调用
	param->setLoadEventHandle(handle);
	param->setIsLoadNeedCoroutine(false);
	param->setIsResNeedCoroutine(false);
	param->setResPackType(this->getResPackType());

	this->load<T>(param);

	GPoolSys->deleteObj(param);
}

template<class T>
T* ResInsMgrBase::createResItem(LoadParam* param)
{
	T* ret = new T();
	ret->getRefCountResLoadResultNotify()->getRefCount()->incRef();
	ret->mPath = param->mPath;

	ret->getRefCountResLoadResultNotify()->getLoadResEventDispatch()->addEventHandle(param->getLoadEventHandle());

	return ret;
}

template<class T>
void ResInsMgrBase::loadWithResCreatedAndNotLoad(LoadParam* param, T* resItem)
{
	this->mPath2ResDic[param->getPath()] = resItem;
	this->mPath2ResDic[param->getPath()]->getRefCountResLoadResultNotify()->getResLoadState()->setLoading();

	param->setLoadEventHandle(MakeEventDispatchDelegate(this, &ResInsMgrBase::onLoadEventHandle));
	GResLoadMgr->loadAsset(param);
}

template<class T>
void ResInsMgrBase::loadWithNotResCreatedAndNotLoad(LoadParam* param)
{
	T* resItem = createResItem<T>(param);
	this->loadWithResCreatedAndNotLoad<T>(param, resItem);
}

// TODO:
//virtual void load(LoadParam* param);	// 模板函数不能使虚函数
template<class T>
void ResInsMgrBase::load(LoadParam* param)
{
	++this->mLoadingDepth;

	if (UtilMap::ContainsKey(this->mPath2ResDic, param->mPath))
	{
		this->loadWithResCreatedAndLoad(param);
	}
	else if (param->getLoadInsRes() != nullptr)
	{
		this->loadWithResCreatedAndNotLoad<T>(param, (T*)(param->getLoadInsRes()));
	}
	else
	{
		this->loadWithNotResCreatedAndNotLoad<T>(param);
	}
	--this->mLoadingDepth;

	if (this->mLoadingDepth == 0)
	{
		this->unloadNoRefResFromList();
	}
}