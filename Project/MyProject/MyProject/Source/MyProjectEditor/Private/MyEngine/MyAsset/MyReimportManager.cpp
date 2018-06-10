#include "MyReimportManager.h"

//FMyReimportManager::FMyReimportManager(const class FObjectInitializer& PCIP)
//	: Super(PCIP)
MyReimportManager::MyReimportManager()
{
	FReimportManager::Instance()->OnPostReimport().AddRaw(this, &MyReimportManager::OnPostReimport);
}

void MyReimportManager::OnPostReimport(UObject* InObject, bool bSuccess)
{

}