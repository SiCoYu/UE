#include "MyProject.h"
#include "AuxComponent.h"

MY_BEGIN_NAMESPACE(MyNS)

AuxComponent::AuxComponent()
{
	this->mIsNeedPlaceHolderActor = false;
	this->mIsPosDirty = false;
	this->mIsRotDirty = false;
	this->mIsDestroySelf = true;
	this->mPreSelfActor = nullptr;
}

void AuxComponent::init()
{

}

void AuxComponent::dispose()
{
	this->onDestroy();
}

void AuxComponent::onDestroy()
{
	this->onPreDestroy();
	this->onExecDestroy();
	this->onPostDestroy();
}

void AuxComponent::onPreDestroy()
{

}

void AuxComponent::onExecDestroy()
{
	if (this->mIsNeedPlaceHolderActor && this->mPlaceHolderActor != nullptr)
	{
		//UtilEngineWrap::Destroy(this->mPlaceHolderActor);
		this->mPlaceHolderActor = nullptr;
	}

	if (nullptr != this->mSelfActor)
	{
		if (this->mIsDestroySelf)
		{
			//UtilEngineWrap::Destroy(this->mSelfActor);
		}

		this->mSelfActor = nullptr;
	}
}

void AuxComponent::onPostDestroy()
{

}

void AuxComponent::putInPool()
{
	this->onPutInPool();
}

void AuxComponent::onPutInPool()
{
	if (this->mIsNeedPlaceHolderActor && this->mPlaceHolderActor != nullptr)
	{
		//UtilEngineWrap::Destroy(this->mPlaceHolderActor);
		this->mPlaceHolderActor = nullptr;
	}

	if (nullptr != this->mSelfActor)
	{
		//if (this->mIsDestroySelf)
		//{
		//    UtilEngineWrap::Destroy(this->mSelfActor);
		//}

		this->mSelfActor = nullptr;
	}

	this->mIsNeedPlaceHolderActor = false;
	this->mIsPosDirty = false;
	this->mIsRotDirty = false;
	this->mIsDestroySelf = true;
}

void AuxComponent::setSelfName(std::string name_)
{
	if (nullptr != this->mSelfActor)
	{
		//UtilEngineWrap::setActorName(this->mSelfActor, name_);
	}
}

void AuxComponent::setSelfActor(AActor* value)
{
	bool isPntChange = this->_isChange(this->mSelfActor, value);
	this->mPreSelfActor = this->mSelfActor;
	this->mSelfActor = value;

	if (isPntChange && nullptr != this->mSelfActor)
	{
		this->_onSelfChanged();
	}
}

AActor* AuxComponent::getSelfActor()
{
	return this->mSelfActor;
}

bool AuxComponent::isDestroySelf()
{
	return this->mIsDestroySelf;
}

void AuxComponent::setIsDestroySelf(bool value)
{
	this->mIsDestroySelf = value;
}

AActor* AuxComponent::getParentActor()
{
	return this->mParentActor;
}

void AuxComponent::setParentActor(AActor* value)
{
	bool isPntChange = this->_isChange(this->mParentActor, value);
	this->mParentActor = value;

	if (isPntChange)
	{
		this->_onParentChanged();
	}
}

//Transform AuxComponent::getParentTransform()
//{
//	return this->mParentActor.transform;
//}

bool AuxComponent::isNeedPlaceHolderActor()
{
	return this->mIsNeedPlaceHolderActor;
}

void AuxComponent::setIsNeedPlaceHolderActor(bool value)
{
	this->mIsNeedPlaceHolderActor = value;

	if (this->mIsNeedPlaceHolderActor)
	{
		if (this->mPlaceHolderActor == nullptr)
		{
			this->mPlaceHolderActor = UtilEngineWrap::createGameObject("PlaceHolderGO");
		}
	}
}

AActor* AuxComponent::getPlaceHolderActor()
{
	return this->mPlaceHolderActor;
}

AActor* AuxComponent::setPlaceHolderActor(AActor* value)
{
	this->mPlaceHolderActor = value;
}

bool AuxComponent::isSelfValid()
{
	return this->mSelfActor != nullptr;
}

bool AuxComponent::_isChange(AActor* srcActor, AActor* destActor)
{
	bool ret = false;

	if (srcActor == nullptr || !srcActor.Equals(destActor))
	{
		ret = true;
	}

	return ret;
}

// 父节点发生改变
void AuxComponent::_onParentChanged()
{
	this->linkSelf2Parent();
}

// 自己发生改变
void AuxComponent::_onSelfChanged()
{
	this->linkSelf2Parent();
	this->updateLocalTransform();
}

void AuxComponent::linkPlaceHolder2Parent()
{
	if (this->mPlaceHolderActor == nullptr)
	{
		this->mPlaceHolderActor = UtilEngineWrap::createGameObject("PlaceHolderGO");
	}
	UtilEngineWrap::SetParent(this->mPlaceHolderActor, this->mParentActor, false);
}

void AuxComponent::linkSelf2Parent()
{
	if (nullptr != this->mSelfActor && nullptr != this->mParentActor)   // 现在可能还没有创建
	{
		UtilEngineWrap::SetParent(this->mSelfActor, this->mParentActor, false);
	}
}

void AuxComponent::show()
{
	if (!IsVisible())
	{
		UtilEngineWrap::SetActive(this->mSelfActor, true);
	}
}

void AuxComponent::hide()
{
	if (this->IsVisible())
	{
		UtilEngineWrap::SetActive(this->mSelfActor, false);
	}
}

bool AuxComponent::IsVisible()
{
	if (nullptr != this->mSelfActor)
	{
		return UtilEngineWrap::IsActive(this->mSelfActor);
	}

	return false;
}

//Transform AuxComponent::transform()
//{
//	if (nullptr != this->mSelfActor)
//	{
//		return this->mSelfActor.GetComponent<Transform>();
//	}

//	return nullptr;
//}

void AuxComponent::setPos(FVector original)
{
	this->mIsPosDirty = true;

	this->updateLocalTransform();
}

void AuxComponent::setRotate(FQuat rotation)
{
	this->mIsRotDirty = true;

	this->updateLocalTransform();
}

void AuxComponent::setScale(FVector value)
{
	this->mIsScaleDirty = true;

	this->updateLocalTransform();
}

void AuxComponent::updateLocalTransform()
{

}

MY_END_NAMESPACE