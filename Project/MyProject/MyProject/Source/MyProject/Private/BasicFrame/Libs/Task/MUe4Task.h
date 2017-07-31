#pragma once

#include "Async/TaskGraphInterfaces.h"		// FGraphEventArray

template <class T>
class MUe4Task
{
protected:
	FString mTaskName;
	FGraphEventArray mCompletionEvents;
	FTimerHandle mOneSecTimerHandle;
	FTimerDelegate mTimerDelegate;

public:
	MUe4Task()
	{
		mTaskName = "MUe4Task"
	}

	static const TCHAR* GetTaskName()
	{
		//return TEXT("FVictoryTestTask");
		return *mTaskName;
	}

	FORCEINLINE static TStatId GetStatId()
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(T, STATGROUP_TaskGraphTasks);
	}

	static ENamedThreads::Type GetDesiredThread()
	{
		return ENamedThreads::AnyThread;
	}

	static ESubsequentsMode::Type GetSubsequentsMode()
	{
		return ESubsequentsMode::TrackSubsequents;
	}

	virtual void DoTask(ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent)
	{
		
	}

	bool TasksAreComplete()
	{
		for (int32 Index = 0; Index < mCompletionEvents.Num(); Index++)
		{
			if (!mCompletionEvents[Index]->IsComplete())
			{
				return false;
			}
		}
		return true;
	}

	void startTask()
	{
		mCompletionEvents.Add(TGraphTask<T>::CreateTask(NULL, ENamedThreads::GameThread).ConstructAndDispatchWhenReady());

		mTimerDelegate = FTimerDelegate::CreateRaw(this, &MUe4Task<T>::onTaskDone);
		EngineApi::GetWorldTimerManager().SetTimer(mOneSecTimerHandle, mTimerDelegate, 1, true);
	}

	void onTaskDone()
	{
		if (TasksAreComplete())
		{
			GetWorldTimerManager().ClearTimer(OneSecTimerHandle);
		}
	}
};