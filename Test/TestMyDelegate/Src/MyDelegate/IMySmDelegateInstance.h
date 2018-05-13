#ifndef __IMySmDelegateInstance_H
#define __IMySmDelegateInstance_H

namespace MyNS
{
	class IMySmDelegateInstance
	{
	public:
		/**
		* Returns true if this delegate is bound to the specified UserObject,
		*
		* Deprecated.
		*
		* @param InUserObject
		*
		* @return True if delegate is bound to the specified UserObject
		*/
		virtual bool HasSameObject(const void* InUserObject) const = 0;

		/**
		* Checks to see if the user object bound to this delegate can ever be valid again.
		* used to compact multicast delegate arrays so they don't expand without limit.
		*
		* @return True if the user object can never be used again
		*/
		virtual bool IsCompactable() const
		{
			return !IsSafeToExecute();
		}

		/**
		* Checks to see if the user object bound to this delegate is still valid
		*
		* @return True if the user object is still valid and it's safe to execute the function call
		*/
		virtual bool IsSafeToExecute() const = 0;

	public:

		/**
		* Virtual destructor.
		*/
		virtual ~IMySmDelegateInstance() { }
	};
}

#endif