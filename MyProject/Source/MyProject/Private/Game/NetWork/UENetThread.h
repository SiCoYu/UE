#ifndef __UENETTHREAD_H
#define __UENETTHREAD_H

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