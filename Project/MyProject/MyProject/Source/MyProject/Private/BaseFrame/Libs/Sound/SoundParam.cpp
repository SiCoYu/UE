#include "MyProject.h"
#include "SoundItem.h"

MY_BEGIN_NAMESPACE(MyNS)

SoundParam::SoundParam()
{
    
}

// 所有都执行完成后调用
void SoundParam::init()
{
    this->onInit();
}

void SoundParam::onInit()
{
    //base.onInit();

    this->mPath = "";
    this->mIsLoop = true;
    this->volume = 1.0f;
    this->soundtype = 1;
    this->mUniqueId = 0;
}

void SoundParam::dispose()
{
    //this->onClear();
    //this->onDestroy();
}

MY_END_NAMESPACE