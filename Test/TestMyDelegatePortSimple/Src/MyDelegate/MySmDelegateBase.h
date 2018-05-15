#pragma once

#include "MySmDelegateInstanceInterface.h"

using namespace MyNS;

namespace MyNS
{
	class MySmDelegateBase
	{
	public:
		explicit MySmDelegateBase()
		{
			this->mDelegateInstance = nullptr;
		}

		~MySmDelegateBase()
		{
			this->unbind();
		}

		MySmDelegateBase(MySmDelegateBase& Other)
		{

		}

		MySmDelegateBase& operator=(MySmDelegateBase& Other)
		{
			this->unbind();

			return *this;
		}

		void setDelegateInstance(IMySmDelegateInstance* value)
		{
			this->mDelegateInstance = value;
		}

		inline bool isValid() const
		{
			return this->mDelegateInstance && this->mDelegateInstance->isValid();
		}

		inline bool isBoundToObject(void const* InUserObject) const
		{
			if (!InUserObject)
			{
				return false;
			}

			return this->mDelegateInstance && this->mDelegateInstance->hasSameObject(InUserObject);
		}

		inline void unbind()
		{
			if (nullptr != this->mDelegateInstance)
			{
				this->mDelegateInstance->~IMySmDelegateInstance();
			}
		}

	protected:
		IMySmDelegateInstance* mDelegateInstance;
	};
}