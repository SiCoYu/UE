#pragma once

#include "ModuleManager.h"

/**
 * @url https://wiki.unrealengine.com/An_Introduction_to_UE4_Plugins
 * The public interface to this module.  In most cases, this interface is only public to sibling modules
 * within this plugin.
 * @url http://blog.csdn.net/yangxuan0261/article/details/52098104
 * 3����д���
   1- ���ȰѲ����������TestPlugin.uplugin����һ��(�������������)
   ���LoadingPhase��ֵĬ��ΪDefault�������޸�ΪPreDefault����Ȼ����Editor�ᱨ�������ϲ��Դ��Ĵ����мǣ� 
 */
class IMyPlugin : public IModuleInterface
{
public:
	/**
	* Singleton-like access to this module's interface.  This is just for convenience!
	* Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already.
	*
	* @return Returns singleton instance, loading the module on demand if needed
	*/
	static inline IMyPlugin& Get()
	{
		return FModuleManager::LoadModuleChecked< IMyPlugin >("MyPlugin");
	}

	/**
	* Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true.
	*
	* @return True if the module is loaded and ready to use
	*/
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("MyPlugin");
	}

	virtual bool IsThisNumber42(int32 num) = 0;
};