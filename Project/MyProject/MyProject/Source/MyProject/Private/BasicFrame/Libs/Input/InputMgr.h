#ifndef __InputMgr_H
#define __InputMgr_H

#include "MyProject.h"
#include "MCamera.h"
#include "UtilEngineWrap.h"
//#include "FastDelegate.h"
#include <string>
#include <map>
#include "MRay.h"
#include "IOEventDispatchDelegate.h"

enum EMouseOrTouch
{
	eLength = 3,
};

enum ControlScheme
{
	Mouse,
	Touch,
	Controller,
};

enum ClickNotification
{
	None,
	Always,
	BasedOnDelta,
};

class MouseOrTouch
{
public:
	FVector2D pos;
	FVector2D lastPos;
	FVector2D delta;
	FVector2D totalDelta;

	MCamera* pressedCam;

	AActor* last;
	AActor* current;
	AActor* pressed;
	AActor* dragged;

	float pressTime;
	float clickTime;

	ClickNotification clickNotification;
	bool touchBegan;
	bool pressStarted;
	bool dragStarted;

public:
	MouseOrTouch()
	{
		pressTime = 0;
		clickTime = 0;
		clickNotification = Always;
		touchBegan = true;
		pressStarted = false;
		dragStarted = false;
	}

	float getDeltaTime()
	{
		//return touchBegan ? UtilEngineWrap::GetRealTimeSeconds() - pressTime : 0;
		return 0;
	}

	bool getIsOverUI()
	{
		//return current != nullptr && current != InputMgr::fallThrough;
		return true;
	}
};

enum EventType : int
{
	World_3D,
	UI_3D,
	World_2D,
	UI_2D,
};

struct DepthEntry
{
public:
	int depth;
	FHitResult* hit;
	FVector point;
	AActor* go;
};

/**
 * @brief 输入管理器主要是控制场景中的对象的
 */
class InputMgr
{
	

public:
	//static BetterList<UICamera> list = new BetterList<UICamera>();

	static KeyEventDispatchDelegate GetKeyDown;

	static KeyEventDispatchDelegate GetKeyUp;

	static KeyEventDispatchDelegate GetKey;

	static fastdelegate::FastDelegate1<const FName, float> GetAxis;

	static fastdelegate::FastDelegate1<void> onScreenResize;

	EventType eventType;

	bool eventsGoToColliders;

	//LayerMask eventReceiverMask = -1;

	bool debug;

	bool useMouse;

	bool useTouch;

	bool allowMultiTouch;

	bool useKeyboard;

	bool useController;

	bool stickyTooltip;

	float tooltipDelay;

	float mouseDragThreshold;

	float mouseClickThreshold;

	float touchDragThreshold;

	float touchClickThreshold;

	float rangeDistance;

	std::string scrollAxisName;

	std::string verticalAxisName;

	std::string horizontalAxisName;

	FKey submitKey0;
	FKey submitKey1;
	FKey cancelKey0;
	FKey cancelKey1;

	static fastdelegate::FastDelegate1<void> onCustomInput;

	static bool showTooltips;

	static FVector2D lastTouchPosition;

	static FVector lastWorldPosition;

	static FHitResult lastHit;

	//static UICamera current = null;

	//static Camera currentCamera = null;

	static ControlScheme currentScheme;

	static int currentTouchID;

	static FKey currentKey;

	static MouseOrTouch* currentTouch;

	static bool inputHasFocus;

	static AActor* mGenericHandler;

	static AActor* fallThrough;

	static fastdelegate::FastDelegate1<AActor*, void> onClick;
	static fastdelegate::FastDelegate1<AActor*, void> onDoubleClick;
	static fastdelegate::FastDelegate2<AActor*, bool, void> onHover;
	static fastdelegate::FastDelegate2<AActor*, bool, void> onPress;
	static fastdelegate::FastDelegate2<AActor*, bool, void> onSelect;
	static fastdelegate::FastDelegate2<AActor*, float, void> onScroll;
	static fastdelegate::FastDelegate2<AActor*, FVector2D, void> onDrag;
	static fastdelegate::FastDelegate1<AActor*, void> onDragStart;
	static fastdelegate::FastDelegate2<AActor*, AActor*, void> onDragOver;
	static fastdelegate::FastDelegate2<AActor*, AActor*, void> onDragOut;
	static fastdelegate::FastDelegate1<AActor*, void> onDragEnd;
	static fastdelegate::FastDelegate2<AActor*, AActor*, void> onDrop;
	static fastdelegate::FastDelegate2<AActor*, FKey, void> onKey;
	static fastdelegate::FastDelegate2<AActor*, bool, void> onTooltip;
	static fastdelegate::FastDelegate1<FVector2D, void> onMouseMove;

	static AActor* mCurrentSelection;
	static AActor* mNextSelection;
	static ControlScheme mNextScheme;

	static AActor* mHover;

	static MouseOrTouch controller;

	static float mNextEvent;

	static std::map<int, MouseOrTouch> mTouches;

	static int mWidth;
	static int mHeight;

	AActor* mTooltip;

	// Camera mCam = null;
	float mTooltipTime;
	float mNextRaycast;

	static bool isDragging;

	static AActor* hoveredObject;

	static bool mNotifying;

	static MouseOrTouch mMouse[eLength];

public:
	InputMgr();

	bool getStickyPress();
	static MRay getCurrentRay();
	static AActor* getGenericEventHandler();
	static void setGenericEventHandler(AActor* value);
	bool getHandlesEvents();
	// Camera getCachedCamera();

	static bool getIsOverUI();

	static AActor* getSelectedObject();
	static void setGameObject(AActor* value);

	static bool IsPressed(AActor* go);

protected:
	static void SetSelection(AActor* go, ControlScheme scheme);

public:
	//System.Collections.IEnumerator ChangeSelection();
	static int getTouchCount();
	static int getDragCount();
	//static Camera getMainCamera();
	//static UICamera getEventHandler();

	//static int CompareFunc(UICamera a, UICamera b);
	static ARigidBodyBase* FindRootRigidbody(USceneComponent* trans);
	static ARigidBodyBase* FindRootRigidbody2D(USceneComponent* trans);
	static bool Raycast(FVector inPos);
	static bool IsVisible(FVector worldPoint, AActor* go);

	static bool IsVisible(DepthEntry de);
	static bool IsHighlighted(AActor* go);
	//static UICamera FindCameraForLayer(int layer);
	static int GetDirection(FKey up, FKey down);

	static int GetDirection(FKey up0, FKey up1, FKey down0, FKey down1);
	static int GetDirection(std::string axis);
	static void Notify(AActor* go, std::string funcName, AActor* obj);
	static MouseOrTouch GetMouse(int button);
	static MouseOrTouch* GetTouch(int id);
	static void RemoveTouch(int id);

	void Awake();
	void OnEnable();
	void OnDisable();
	void Start();
	void Update();

	void LateUpdate();
	void ProcessMouse();
	void ProcessTouches();
	void ProcessFakeTouches();
	void ProcessOthers();

	void ProcessTouch(bool pressed, bool unpressed);
	void ShowTooltip(bool val);
	// 模拟停止拖放
	static void simuStopDrag();
	void OnApplicationPause();
};

#endif