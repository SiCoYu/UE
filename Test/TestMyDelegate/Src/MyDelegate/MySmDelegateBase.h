#pragma once

#include "IMySmDelegateInstance.h"

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
		}

		~MySmDelegateBase()
		{
			Unbind();
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
			Unbind();

			return *this;
		}

		/**
		* Checks to see if the user object bound to this delegate is still valid.
		*
		* @return True if the user object is still valid and it's safe to execute the function call.
		*/
		inline bool IsBound() const
		{
			return mDelegateInstance && mDelegateInstance->IsSafeToExecute();
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

			return mDelegateInstance && mDelegateInstance->HasSameObject(InUserObject);
		}

		/**
		* Unbinds this delegate
		*/
		inline void Unbind()
		{
			mDelegateInstance->~IMySmDelegateInstance();
		}

	protected:
		IMySmDelegateInstance* mDelegateInstance;
	};
}