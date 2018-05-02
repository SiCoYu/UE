#pragma once

#include "UObject/Object.h"
#include "MySingletonBP.generated.h"

/**
 * @url https://blog.csdn.net/onafioo/article/details/77994045
 * @url http://www.voidcn.com/article/p-siyhuvlm-bnv.html
 * @url https://answers.unrealengine.com/questions/552321/static-variables-in-bp.html
 */
UCLASS(Blueprintable)
class UMySingletonBP : public UObject
{
	// Á´½Ó´íÎó
	//GENERATED_UCLASS_BODY()
	GENERATED_BODY()

protected:
	static UMySingletonBP* msSingleton;

public:
	static bool isValid();
	/**
	* Singleton access
	*/
	static UMySingletonBP* getSingleton();

public:
	UMySingletonBP(const FObjectInitializer& PCIP);
	void init();
};