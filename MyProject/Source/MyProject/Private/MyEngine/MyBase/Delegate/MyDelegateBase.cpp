#include "MyProject.h"
#include "MyDelegateBase.h"

UMyDelegateBase::UMyDelegateBase(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	
}

void UMyDelegateBase::testOneDelegate()
{
	this->mMyDelegateThreeParamsTestHandle.BindUObject(this, &UMyDelegateBase::handle);
	//this->mMyDelegateThreeParamsTestHandle.BindRaw(this, &UMyDelegateBase::handle);
	this->mMyDelegateThreeParamsTestHandle.Execute(10, 10, true);
	this->mMyDelegateThreeParamsTestHandle.Unbind();
}

void UMyDelegateBase::testMultiDelegate()
{
	// 不能移除事件
	//this->mMyDelegateMultiThreeParamsTestEvent.AddUObject(this, &UMyDelegateBase::multiHandle);

	// 可以移除事件
	this->mOnMultiThreeParamsTestDelegate = FMyDelegateDef::MyDelegateMultiThreeParamsTestEvent::FDelegate::CreateUObject(this, &UMyDelegateBase::multiHandle);

	this->mOnMultiThreeParamsTestDelegateHandle = this->mMyDelegateMultiThreeParamsTestEvent.Add(this->mOnMultiThreeParamsTestDelegate);

	this->mMyDelegateMultiThreeParamsTestEvent.Remove(this->mOnMultiThreeParamsTestDelegateHandle);
}

void UMyDelegateBase::handle(int aaa, int bbb, bool ccc)
{

}

void UMyDelegateBase::multiHandle(int aaa, int bbb, bool ccc)
{

}