#ifndef __ResLoadState_H
#define __ResLoadState_H

enum CVResLoadState
{
	eNotLoad,       // 没有加载
	eLoading,       // 正在加载
	eLoaded,        // 加载成功
	eFailed         // 加载失败
};

class ResLoadState
{
protected:
	CVResLoadState m_resLoadState;

public:
	ResLoadState();

	CVResLoadState getResLoadState();
	void setResLoadState(CVResLoadState value);
	void reset();
    // 是否加载完成，可能成功可能失败
	bool hasLoaded();
	bool hasSuccessLoaded();
	bool hasFailed();
    // 没有加载或者正在加载中
	bool hasNotLoadOrLoading();
	void setSuccessLoaded();
	void setFailed();
	void setLoading();
	void copyFrom(ResLoadState& rhv);
};

#endif