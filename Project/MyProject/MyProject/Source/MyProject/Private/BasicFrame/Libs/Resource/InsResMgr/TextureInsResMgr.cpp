#include "MyProject.h"
#include "TextureInsResMgr.h"
#include "TextureInsRes.h"

MY_BEGIN_NAMESPACE(MyNS)

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