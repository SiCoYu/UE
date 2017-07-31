#include "MyProject.h"
#include "MyDelegateBase.h"

UMyDelegateBase::UMyDelegateBase(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	
}

void UMyDelegateBase::testOneDelegate()
{
	this->mMyDelegateThreeParamsTestEvent.BindUObject(this, &UMyDelegateBase::handle);
	//this->mMyDelegateThreeParamsTestHandle.BindRaw(this, &UMyDelegateBase::handle);
	this->mMyDelegateThreeParamsTestEvent.Execute(10, 10, true);
	this->mMyDelegateThreeParamsTestEvent.Unbind();
}

void UMyDelegateBase::testMultiDelegate()
{
	// �����Ƴ��¼�
	//this->mMyDelegateMultiThreeParamsTestEvent.AddUObject(this, &UMyDelegateBase::multiHandle);

	// �����Ƴ��¼�
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