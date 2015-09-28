#ifndef __UENETTHREAD_H
#define __UENETTHREAD_H

/**
 * @brief UE 网络线程，其实就是一个 Task，因为 UE 已经实现了多线程的基本流程，只需要向里面添加任务就行了，参照 FRenderingThread 实现
 */
class UENetThread
{
public:
	UENetThread();
	~UENetThread();

	void Run();
	void setExitFlag(bool exit);

private:
	UENetThread(const UENetThread& s) {}
	UENetThread& operator=(const UENetThread&) { return *this; }

	bool m_ExitFlag;
};

#endif