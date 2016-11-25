#pragma once

#include "MyProject.h"

/**
 * @brief https://wiki.unrealengine.com/Multi-Threading:_How_to_Create_Threads_in_UE4
 */

 //In the .h for the player controller
 // this is the actual data
//TArray<uint32> PrimeNumbers;


//player controller .cpp
//Multi-threading, returns handle that could be cached.
//		use static function FPrimeNumberWorker::Shutdown() if necessary
//FPrimeNumberWorker::JoyInit(PrimeNumbers, 50000, this);

//FPlatformProcess::Sleep(seconds);


//Do not try to modify, create, or delete UObjects from other threads!
//
//You can prepare all the data / do all the calculations, but only the game thread should be actually spawning / modifying / deleting UObjects / AActors.
//
//Dont try to use TimerManager outside of the game thread : )
//
//Don't try to draw debug lines/points etc, as it will likely crash, ie DrawDebugLine(etc...)
//
//Notice(since 4.11) :
//
//	If you want to use the timer, remove, and modify variables use it :
//
//#include "Async.h"
//...
//AsyncTask(ENamedThreads::GameThread, []() {
//	// code to execute on game thread here
//})

class AMyProjectPlayerController;

//~~~~~ Multi Threading ~~~
class FMultiThreadWorker : public FRunnable
{
	/** Singleton instance, can access the thread any time via static accessor, if it is active! */
	static  FMultiThreadWorker* Runnable;

	/** Thread to run the worker FRunnable on */
	FRunnableThread* Thread;

	/** The Data Ptr */
	TArray<uint32>* PrimeNumbers;

	/** The PC */
	AMyProjectPlayerController* ThePC;

	/** Stop this thread? Uses Thread Safe Counter */
	FThreadSafeCounter StopTaskCounter;

	//The actual finding of prime numbers
	int32 FindNextPrimeNumber();

private:
	int32				PrimesFoundCount;
public:

	int32				TotalPrimesToFind;

	//Done?
	bool IsFinished() const
	{
		return PrimesFoundCount >= TotalPrimesToFind;
	}

	//~~~ Thread Core Functions ~~~

	//Constructor / Destructor
	FMultiThreadWorker(TArray<uint32>& TheArray, const int32 IN_PrimesToFindPerTick, AMyProjectPlayerController* IN_PC);
	virtual ~FMultiThreadWorker();

	// Begin FRunnable interface.
	virtual bool Init();
	virtual uint32 Run();
	virtual void Stop();
	// End FRunnable interface

	/** Makes sure this thread has stopped properly */
	void EnsureCompletion();



	//~~~ Starting and Stopping Thread ~~~



	/*
	Start the thread and the worker from static (easy access)!
	This code ensures only 1 Prime Number thread will be able to run at a time.
	This function returns a handle to the newly started instance.
	*/
	static FMultiThreadWorker* JoyInit(TArray<uint32>& TheArray, const int32 IN_TotalPrimesToFind, AMyProjectPlayerController* IN_PC);

	/** Shuts down the thread. Static so it can easily be called from outside the thread context */
	static void Shutdown();

	static bool IsThreadFinished();

};