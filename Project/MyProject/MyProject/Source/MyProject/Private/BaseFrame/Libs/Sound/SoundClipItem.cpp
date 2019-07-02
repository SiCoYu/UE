#include "MyProject.h"
#include "SoundClipItem.h"
#include "Prequisites.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(SoundClipItem, SoundItem)

SoundClipItem::SoundClipItem()
{
    
}

void SoundClipItem::onInit()
{
    Super::onInit();

    this->mIsLoaded = false;
    this->mIsDontDestroy = true;
}

void SoundClipItem::onDestroy()
{
	Super::onDestroy();
}

void SoundClipItem::unload()
{
    if (this->isInCurState(SoundPlayState::eSS_Play))
    {
        this->Stop();
    }

	Super::unload();
}

void SoundClipItem::Play()
{
	Super::Play();
}

MY_END_NAMESPACE