#ifndef __ResLoadResultNotify_H
#define __ResLoadResultNotify_H

class ResLoadState;
class ResEventDispatch;
class IDispatchObject;

/**
    * @brief 非引用计数资源加载结果通知
    */
class ResLoadResultNotify
{
protected:
	ResLoadState* m_resLoadState;          // 资源加载状态
    ResEventDispatch* m_loadResEventDispatch;    // 事件分发器

public:
	ResLoadResultNotify();
	~ResLoadResultNotify();

	ResLoadState* getResLoadState();
	void setResLoadState(ResLoadState* value);
	ResEventDispatch* getLoadResEventDispatch();
	void setLoadResEventDispatch(ResEventDispatch* value);
	void onLoadEventHandle(IDispatchObject* dispObj);
	virtual void copyFrom(ResLoadResultNotify& rhv);
};

#endif