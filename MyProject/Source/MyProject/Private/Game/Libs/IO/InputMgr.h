#ifndef __InputMgr_H
#define __InputMgr_H

#include "MyProject.h"
#include "MCamera.h"
#include "EngineApi.h"

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
		return touchBegan ? EngineApi::GetRealTimeSeconds() - pressTime : 0;
	}

	bool getIsOverUI()
	{
		return current != nullptr && current != InputMgr::fallThrough;
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
	static BetterList<UICamera> list = new BetterList<UICamera>();

	delegate bool GetKeyStateFunc(KeyCode key);
	delegate float GetAxisFunc(string name);

	static GetKeyStateFunc GetKeyDown = Input.GetKeyDown;

	static GetKeyStateFunc GetKeyUp = Input.GetKeyUp;

	static GetKeyStateFunc GetKey = Input.GetKey;

	static GetAxisFunc GetAxis = Input.GetAxis;

	delegate void OnScreenResize();

	static OnScreenResize onScreenResize;

	EventType eventType = EventType.World_3D;

	bool eventsGoToColliders = false;

	LayerMask eventReceiverMask = -1;

	bool debug = false;

	bool useMouse = true;

	bool useTouch = true;

	bool allowMultiTouch = true;

	bool useKeyboard = true;

	bool useController = true;

	bool stickyTooltip = true;

	float tooltipDelay = 1f;

	float mouseDragThreshold = 4f;

	float mouseClickThreshold = 10f;

	float touchDragThreshold = 40f;

	float touchClickThreshold = 40f;

	float rangeDistance = -1f;

	string scrollAxisName = "Mouse ScrollWheel";

	string verticalAxisName = "Vertical";

	string horizontalAxisName = "Horizontal";

	KeyCode submitKey0 = KeyCode.Return;
	KeyCode submitKey1 = KeyCode.JoystickButton0;
	KeyCode cancelKey0 = KeyCode.Escape;
	KeyCode cancelKey1 = KeyCode.JoystickButton1;

	delegate void OnCustomInput();

	static OnCustomInput onCustomInput;

	static bool showTooltips = true;

	static Vector2 lastTouchPosition = Vector2.zero;

	static Vector3 lastWorldPosition = Vector3.zero;

	static RaycastHit lastHit;

	static UICamera current = null;

	static Camera currentCamera = null;

	static ControlScheme currentScheme = ControlScheme.Mouse;

	static int currentTouchID = -1;

	static KeyCode currentKey = KeyCode.None;

	static MouseOrTouch currentTouch = null;

	static bool inputHasFocus = false;

	static GameObject mGenericHandler;

	static GameObject fallThrough;

	delegate void MoveDelegate(Vector2 delta);
	delegate void VoidDelegate(GameObject go);
	delegate void BoolDelegate(GameObject go, bool state);
	delegate void FloatDelegate(GameObject go, float delta);
	delegate void VectorDelegate(GameObject go, Vector2 delta);
	delegate void ObjectDelegate(GameObject go, GameObject obj);
	delegate void KeyCodeDelegate(GameObject go, KeyCode key);

	static VoidDelegate onClick;
	static VoidDelegate onDoubleClick;
	static BoolDelegate onHover;
	static BoolDelegate onPress;
	static BoolDelegate onSelect;
	static FloatDelegate onScroll;
	static VectorDelegate onDrag;
	static VoidDelegate onDragStart;
	static ObjectDelegate onDragOver;
	static ObjectDelegate onDragOut;
	static VoidDelegate onDragEnd;
	static ObjectDelegate onDrop;
	static KeyCodeDelegate onKey;
	static BoolDelegate onTooltip;
	static MoveDelegate onMouseMove;

	static GameObject mCurrentSelection = null;
	static GameObject mNextSelection = null;
	static ControlScheme mNextScheme = ControlScheme.Controller;

	static GameObject mHover;

	static MouseOrTouch controller = new MouseOrTouch();

	static float mNextEvent = 0f;

	static Dictionary<int, MouseOrTouch> mTouches = new Dictionary<int, MouseOrTouch>();

	static int mWidth = 0;
	static int mHeight = 0;

	GameObject mTooltip = null;

	Camera mCam = null;
	float mTooltipTime = 0f;
	float mNextRaycast = 0f;

	static bool isDragging = false;

	static GameObject hoveredObject;

	static bool mNotifying = false;

	static MouseOrTouch[] mMouse = new MouseOrTouch[] { new MouseOrTouch(), new MouseOrTouch(), new MouseOrTouch() };

public:
	InputMgr();

	bool getStickyPress();
	static Ray getCurrentRay();
	static GameObject getGenericEventHandler();
	static void setGenericEventHandler(GameObject value);
	bool getHandlesEvents();
	Camera getCachedCamera();

	static bool getIsOverUI();

	static GameObject getSelectedObject();
	static void setGameObject(GameObject value);

	static bool IsPressed(GameObject go);

protected:
	static void SetSelection(GameObject go, ControlScheme scheme);

public:
	System.Collections.IEnumerator ChangeSelection();
	static int getTouchCount();
	static int getDragCount();
	static Camera getMainCamera();
	static UICamera getEventHandler();

	static int CompareFunc(UICamera a, UICamera b);
	static Rigidbody FindRootRigidbody(Transform trans);
	static Rigidbody2D FindRootRigidbody2D(Transform trans);
	static bool Raycast(Vector3 inPos);
	static bool IsVisible(Vector3 worldPoint, GameObject go);

	static bool IsVisible(ref DepthEntry de);
	static bool IsHighlighted(GameObject go);
	static UICamera FindCameraForLayer(int layer);
	static int GetDirection(KeyCode up, KeyCode down);

	static int GetDirection(KeyCode up0, KeyCode up1, KeyCode down0, KeyCode down1);
	static int GetDirection(string axis);
	static void Notify(GameObject go, string funcName, object obj);
	static MouseOrTouch GetMouse(int button);
	static MouseOrTouch GetTouch(int id);
	static void RemoveTouch(int id);

	void Awake();
	void OnEnable();
	void OnDisable();
	void Start();
	void Update();

	void LateUpdate();
	public void ProcessMouse();
	public void ProcessTouches();
	void ProcessFakeTouches();
	public void ProcessOthers();

	public void ProcessTouch(bool pressed, bool unpressed);
	public void ShowTooltip(bool val);
	// 模拟停止拖放
	static public void simuStopDrag();
	void OnApplicationPause();
};

#endif