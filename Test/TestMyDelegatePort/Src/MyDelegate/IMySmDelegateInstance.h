#ifndef __IMySmDelegateInstance_H
#define __IMySmDelegateInstance_H

namespace MyNS
{
	class IMySmDelegateInstance
	{
	public:
		virtual bool hasSameObject(const void* InUserObject) const = 0;
		virtual bool isValid() const = 0;

	public:
		IMySmDelegateInstance()
		{

		}

		virtual ~IMySmDelegateInstance()
		{
			
		}
	};
}

#endif