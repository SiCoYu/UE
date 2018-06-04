#include "MyProject.h"
#include "TextureInsResMgr.h"
#include "TextureInsRes.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(TextureInsResMgr, ResInsMgrBase)

TextureInsResMgr::TextureInsResMgr()
{

}

TextureInsRes* TextureInsResMgr::getAndSyncLoadRes(
	std::string path, 
	EventDispatchDelegate handle,
	EventDispatchDelegate progressHandle,
	ResLoadPriority priority
)
{
	return Super::getAndSyncLoad<TextureInsRes>(
		path, 
		handle
		);
}

TextureInsRes* TextureInsResMgr::getAndAsyncLoadRes(
	std::string path, 
	EventDispatchDelegate handle,
	EventDispatchDelegate progressHandle,
	ResLoadPriority priority
)
{
	return Super::getAndAsyncLoad<TextureInsRes>(
		path, 
		handle
		);
}

MY_END_NAMESPACE