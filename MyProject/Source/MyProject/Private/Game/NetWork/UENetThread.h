#ifndef __UENETTHREAD_H
#define __UENETTHREAD_H

/**
 * @brief UE �����̣߳���ʵ����һ�� Task����Ϊ UE �Ѿ�ʵ���˶��̵߳Ļ������̣�ֻ��Ҫ�����������������ˣ����� FRenderingThread ʵ��
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