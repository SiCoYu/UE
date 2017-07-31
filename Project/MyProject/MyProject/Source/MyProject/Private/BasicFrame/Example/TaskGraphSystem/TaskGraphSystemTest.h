#pragma once

//The UE4 task graph system allows you to perform many actions, each of which is relatively small, on separate threads from the game thread.
//
//Please note that a task graph will sometimes use the game thread, and therefore for large tasks you should use a FRunnable as demonstrated in my other multi threading wiki.


/**
 * @brief https://wiki.unrealengine.com/Multi-Threading:_Task_Graph_System
 */

class TaskGraphSystemTest
{
public:
	TaskGraphSystemTest();
};