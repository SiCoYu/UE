#pragma once

#include "MySmDelegateInstanceInterface.h"

using namespace MyNS;

namespace MyNS
{
	/**
	* Base class for unicast delegates.
	*/
	class MySmDelegateBase
	{
	public:
		/**
		* Creates and initializes a new instance.
		*
		* @param InDelegateInstance The delegate instance to assign.
		*/
		explicit MySmDelegateBase()
		{
			this->mDelegateInstance = nullptr;
		}

		~MySmDelegateBase()
		{
			this->Unbind();
		}

		/**
		* Move constructor.
		*/
		MySmDelegateBase(MySmDelegateBase& Other)
		{

		}

		/**
		* Move assignment.
		*/
		MySmDelegateBase& operator=(MySmDelegateBase& Other)
		{
			this->Unbind();

			return *this;
		}

		void setDelegateInstance(IMySmDelegateInstance* value)
		{
			this->mDelegateInstance = value;
		}

		/**
		* Checks to see if the user object bound to this delegate is still valid.
		*
		* @return True if the user object is still valid and it's safe to execute the function call.
		*/
		inline bool IsBound() const
		{
			return this->mDelegateInstance && this->mDelegateInstance->IsSafeToExecute();
		}

		/**
		* Checks to see if this delegate is bound to the given user object.
		*
		* @return True if this delegate is bound to InUserObject, false otherwise.
		*/
		inline bool IsBoundToObject(void const* InUserObject) const
		{
			if (!InUserObject)
			{
				return false;
			}

			return this->mDelegateInstance && this->mDelegateInstance->HasSameObject(InUserObject);
		}

		/**
		* Unbinds this delegate
		*/
		inline void Unbind()
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