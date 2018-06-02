#include "MyProject.h"
#include "InputMgr.h"
#include "MDictionary.h"

bool InputMgr::showTooltips = true;
FVector2D InputMgr::lastTouchPosition = FVector2D::ZeroVector;
FVector InputMgr::lastWorldPosition = FVector::ZeroVector;
ControlScheme InputMgr::currentScheme = Mouse;
FKey InputMgr::currentKey = EKeys::AnyKey;
int InputMgr::currentTouchID = -1;
bool InputMgr::inputHasFocus = false;

AActor* InputMgr::mCurrentSelection = nullptr;
AActor* InputMgr::mNextSelection = nullptr;
ControlScheme InputMgr::mNextScheme = Controller;

float InputMgr::mNextEvent = 0;
MDictionary<int, MouseOrTouch> InputMgr::mTouches;

int InputMgr::mWidth = 0;
int InputMgr::mHeight = 0;
bool InputMgr::isDragging = false;
bool InputMgr::mNotifying = false;

MouseOrTouch* InputMgr::currentTouch;
AActor* InputMgr::mGenericHandler;
AActor* InputMgr::fallThrough;
MouseOrTouch InputMgr::controller;
AActor* InputMgr::hoveredObject;
MouseOrTouch InputMgr::mMouse[eLength];

InputMgr::InputMgr()
{
	eventType = World_3D;
	eventsGoToColliders = false;
	debug = false;
	useMouse = true;
	useTouch = true;
	allowMultiTouch = true;
	useKeyboard = true;
	useController = true;
	stickyTooltip = true;
	tooltipDelay = 1;
	mouseDragThreshold = 4;
	mouseClickThreshold = 10;
	touchDragThreshold = 40;
	touchClickThreshold = 40;
	rangeDistance = -1;
	scrollAxisName = "Mouse ScrollWheel";
	verticalAxisName = "Vertical";
	horizontalAxisName = "Horizontal";

	submitKey0 = EKeys::Enter;
	submitKey1 = EKeys::Gamepad_LeftThumbstick;
	cancelKey0 = EKeys::Escape;
	cancelKey1 = EKeys::Gamepad_RightThumbstick;

	this->mTooltip = nullptr;
	this->mTooltipTime = 0;
	this->mNextRaycast = 0;
}

bool InputMgr::getStickyPress()
{
	return true;
}

MRay InputMgr::getCurrentRay()
{
	//return (currentCamera != nullptr && currentTouch != nullptr) ?
	//	currentCamera.ScreenPointToRay(currentTouch.pos) : new Ray();

	return MRay();
}

AActor* InputMgr::getGenericEventHandler()
{
	return mGenericHandler;
}

void InputMgr::setGenericEventHandler(AActor* value)
{
	mGenericHandler = value;
}

bool InputMgr::getHandlesEvents()
{
	//return eventHandler == this;
	return false;
}

//Camera InputMgr::getCachedCamera()
//{
//	if (mCam == nullptr)
//	mCam = Camera.main; return mCam;
//}

bool InputMgr::getIsOverUI()
{
	if (currentTouch != nullptr) return currentTouch->getIsOverUI();
	if (hoveredObject == nullptr) return false;
	if (hoveredObject == fallThrough) return false;
	//return NGUITools.FindInParents<UIRoot>(hoveredObject) != nullptr;
	return false;
}

AActor* InputMgr::getSelectedObject()
{
	return mCurrentSelection;
}

void InputMgr::setGameObject(AActor* value)
{
	//SetSelection(value, UICamera.currentScheme);
}

bool InputMgr::IsPressed(AActor* go)
{
	for (int i = 0; i < 3; ++i) if (mMouse[i].pressed == go) return true;
	for(std::pair<int, MouseOrTouch> touch : mTouches) 
		if (touch.second.pressed == go) return true;
	if (controller.pressed == go) return true;
	return false;
}

void InputMgr::SetSelection(AActor* go, ControlScheme scheme)
{
	//if (mNextSelection != nullptr)
	//{
	//	mNextSelection = go;
	//}
	//else if (mCurrentSelection != go)
	//{
	//	mNextSelection = go;
	//	mNextScheme = scheme;

	//	if (UICamera.list.size > 0)
	//	{
	//		UICamera cam = (mNextSelection != nullptr) ? FindCameraForLayer(mNextSelection.layer) : UICamera.list[0];
	//		if (cam != nullptr) cam.StartCoroutine(cam.ChangeSelection());
	//	}
	//}
}

//System.Collections.IEnumerator InputMgr::ChangeSelection()
//{
//	yield return new WaitForEndOfFrame();
//	if (onSelect != nullptr) onSelect(mCurrentSelection, false);
//	Notify(mCurrentSelection, "OnSelect", false);
//	mCurrentSelection = mNextSelection;
//	mNextSelection = nullptr;
//
//	if (mCurrentSelection != nullptr)
//	{
//		current = this;
//		currentCamera = mCam;
//		UICamera.currentScheme = mNextScheme;
//		//inputHasFocus = (mCurrentSelection.GetComponent<UIInput>() != nullptr);
//		inputHasFocus = false;
//		if (onSelect != nullptr) onSelect(mCurrentSelection, true);
//		Notify(mCurrentSelection, "OnSelect", true);
//		current = nullptr;
//	}
//	else inputHasFocus = false;
//}

int InputMgr::getTouchCount()
{
	//int count = 0;

	//for(std::pair<int, MouseOrTouch> touch : mTouches)
	//	if (touch.second.pressed != nullptr)
	//		++count;

	//for (int i = 0; i < EMouseOrTouch.eLength; ++i)
	//	if (mMouse[i].pressed != nullptr)
	//		++count;

	//if (controller.pressed != nullptr)
	//	++count;

	//return count;

	return 0;
}

int InputMgr::getDragCount()
{
	//int count = 0;

	//foreach(KeyValuePair<int, MouseOrTouch> touch in mTouches)
	//	if (touch.Value.dragged != nullptr)
	//		++count;

	//for (int i = 0; i < mMouse.Length; ++i)
	//	if (mMouse[i].dragged != nullptr)
	//		++count;

	//if (controller.dragged != nullptr)
	//	++count;

	//return count;

	return 0;
}

//Camera InputMgr::getMainCamera()
//{
//	UICamera mouse = eventHandler;
//	return (mouse != nullptr) ? mouse.cachedCamera : nullptr;
//}
//
//UICamera InputMgr::getEventHandler()
//{
//	for (int i = 0; i < list.size; ++i)
//	{
//		// Invalid or inactive entry -- keep going
//		UICamera cam = list.buffer[i];
//		if (cam == nullptr || !cam.enabled || !NGUITools.GetActive(cam.gameObject)) continue;
//		return cam;
//	}
//	return nullptr;
//}

//int InputMgr::CompareFunc(UICamera a, UICamera b)
//{
//	if (a.cachedCamera.depth < b.cachedCamera.depth) return 1;
//	if (a.cachedCamera.depth > b.cachedCamera.depth) return -1;
//	return 0;
//}

ARigidBodyBase* InputMgr::FindRootRigidbody(USceneComponent* trans)
{
//	while (trans != nullptr)
//	{
//		//if (trans.GetComponent<UIPanel>() != nullptr) return nullptr;
//#if UNITY_5
//		Rigidbody rb = trans.GetComponent<Rigidbody>();
//#elif UNITY_4_6 || UNITY_4_5
//		Rigidbody rb = trans.rigidbody;
//#endif
//		if (rb != nullptr) return rb;
//		trans = trans.parent;
//	}
	return nullptr;
}

ARigidBodyBase* InputMgr::FindRootRigidbody2D(USceneComponent* trans)
{
//	while (trans != nullptr)
//	{
//		//if (trans.GetComponent<UIPanel>() != nullptr) return nullptr;
//#if UNITY_5
//		Rigidbody2D rb = trans.GetComponent<Rigidbody2D>();
//#elif UNITY_4_6 || UNITY_4_5
//		Rigidbody2D rb = trans.rigidbody2D;
//#endif
//		if (rb != nullptr) return rb;
//		trans = trans.parent;
//	}
	return nullptr;
}

bool InputMgr::Raycast(FVector inPos)
{
	//for (int i = 0; i < list.size; ++i)
	//{
	//	UICamera cam = list.buffer[i];

	//	// Skip inactive scripts
	//	if (!cam.enabled || !NGUITools.GetActive(cam.gameObject)) continue;

	//	// Convert to view space
	//	currentCamera = cam.cachedCamera;
	//	Vector3 pos = currentCamera.ScreenToViewportPoint(inPos);
	//	if (float.IsNaN(pos.x) || float.IsNaN(pos.y)) continue;

	//	// If it's outside the camera's viewport, do nothing
	//	if (pos.x < 0f || pos.x > 1f || pos.y < 0f || pos.y > 1f) continue;

	//	// Cast a ray into the screen
	//	Ray ray = currentCamera.ScreenPointToRay(inPos);

	//	// Raycast into the screen
	//	int mask = currentCamera.cullingMask & (int)cam.eventReceiverMask;
	//	float dist = (cam.rangeDistance > 0f) ? cam.rangeDistance : currentCamera.farClipPlane - currentCamera.nearClipPlane;

	//	if (cam.eventType == EventType.World_3D)
	//	{
	//		if (Physics.Raycast(ray, out lastHit, dist, mask))
	//		{
	//			lastWorldPosition = lastHit.point;
	//			hoveredObject = lastHit.collider.gameObject;

	//			if (!list[0].eventsGoToColliders)
	//			{
	//				Rigidbody rb = FindRootRigidbody(hoveredObject.transform);
	//				if (rb != nullptr) hoveredObject = rb.gameObject;
	//			}
	//			return true;
	//		}
	//		continue;
	//	}
	//}
	return false;
}

bool InputMgr::IsVisible(FVector worldPoint, AActor* go)
{
	//UIPanel panel = NGUITools.FindInParents<UIPanel>(go);

	//while (panel != nullptr)
	//{
	//    if (!panel.IsVisible(worldPoint)) return false;
	//    panel = panel.parentPanel;
	//}
	return true;
}

bool InputMgr::IsVisible(DepthEntry de)
{
	//UIPanel panel = NGUITools.FindInParents<UIPanel>(de.go);

	//while (panel != nullptr)
	//{
	//    if (!panel.IsVisible(de.point)) return false;
	//    panel = panel.parentPanel;
	//}
	return true;
}

bool InputMgr::IsHighlighted(AActor* go)
{
	//if (UICamera.currentScheme == UICamera.ControlScheme.Mouse)
	//	return (UICamera.hoveredObject == go);

	//if (UICamera.currentScheme == UICamera.ControlScheme.Controller)
	//	return (UICamera.selectedObject == go);

	return false;
}

//UICamera InputMgr::FindCameraForLayer(int layer)
//{
//	int layerMask = 1 << layer;
//
//	for (int i = 0; i < list.size; ++i)
//	{
//		UICamera cam = list.buffer[i];
//		Camera uc = cam.cachedCamera;
//		if ((uc != nullptr) && (uc.cullingMask & layerMask) != 0) return cam;
//	}
//	return nullptr;
//}

int InputMgr::GetDirection(FKey up, FKey down)
{
	//if (GetKeyDown(up)) return 1;
	//if (GetKeyDown(down)) return -1;
	return 0;
}

int InputMgr::GetDirection(FKey up0, FKey up1, FKey down0, FKey down1)
{
	//if (GetKeyDown(up0) || GetKeyDown(up1)) return 1;
	//if (GetKeyDown(down0) || GetKeyDown(down1)) return -1;
	return 0;
}

int InputMgr::GetDirection(std::string axis)
{
	//float time = RealTime.time;

	//if (mNextEvent < time && !string.IsNullOrEmpty(axis))
	//{
	//	float val = GetAxis(axis);

	//	if (val > 0.75f)
	//	{
	//		mNextEvent = time + 0.25f;
	//		return 1;
	//	}

	//	if (val < -0.75f)
	//	{
	//		mNextEvent = time + 0.25f;
	//		return -1;
	//	}
	//}
	return 0;
}

void InputMgr::Notify(AActor* go, std::string funcName, AActor* obj)
{
	//if (mNotifying) return;
	//mNotifying = true;

	//if (NGUITools.GetActive(go))
	//{
	//	go.SendMessage(funcName, obj, SendMessageOptions.DontRequireReceiver);

	//	if (mGenericHandler != nullptr && mGenericHandler != go)
	//	{
	//		mGenericHandler.SendMessage(funcName, obj, SendMessageOptions.DontRequireReceiver);
	//	}
	//}
	//mNotifying = false;
}

MouseOrTouch InputMgr::GetMouse(int button)
{
	return mMouse[button];
}

MouseOrTouch* InputMgr::GetTouch(int id)
{
	MouseOrTouch* touch = nullptr;

	//if (id < 0) return GetMouse(-id - 1);

	//if (!mTouches.TryGetValue(id, out touch))
	//{
	//	touch = new MouseOrTouch();
	//	touch.pressTime = RealTime.time;
	//	touch.touchBegan = true;
	//	mTouches.Add(id, touch);
	//}
	return touch;
}

void InputMgr::RemoveTouch(int id)
{
	//mTouches.Remove(id);
}

void InputMgr::Awake()
{
//	mWidth = Screen.width;
//	mHeight = Screen.height;
//
//	if (Application.platform == RuntimePlatform.Android ||
//		Application.platform == RuntimePlatform.IPhonePlayer
//		|| Application.platform == RuntimePlatform.WP8Player
//#if UNITY_4_3
//		|| Application.platform == RuntimePlatform.BB10Player
//#else
//		|| Application.platform == RuntimePlatform.BlackBerryPlayer
//#endif
//		)
//	{
//		useTouch = true;
//
//		if (Application.platform == RuntimePlatform.IPhonePlayer)
//		{
//			useMouse = false;
//			useKeyboard = false;
//			useController = false;
//		}
//	}
//	else if (Application.platform == RuntimePlatform.PS3 ||
//		Application.platform == RuntimePlatform.XBOX360)
//	{
//		useMouse = false;
//		useTouch = false;
//		useKeyboard = false;
//		useController = true;
//	}
//
//	// Save the starting mouse position
//	mMouse[0].pos = Input.mousePosition;
//
//	for (int i = 1; i < 3; ++i)
//	{
//		mMouse[i].pos = mMouse[0].pos;
//		mMouse[i].lastPos = mMouse[0].pos;
//	}
//	lastTouchPosition = mMouse[0].pos;
}

void InputMgr::OnEnable()
{
	//list.Add(this);
	//list.Sort(CompareFunc);
}

void InputMgr::OnDisable()
{
	//list.Remove(this);
}

void InputMgr::Start()
{
	//if (eventType != EventType.World_3D && cachedCamera.transparencySortMode != TransparencySortMode.Orthographic)
	//	cachedCamera.transparencySortMode = TransparencySortMode.Orthographic;

	//if (Application.isPlaying)
	//{
	//	// Always set a fallthrough object
	//	if (fallThrough == nullptr)
	//	{
	//		//UIRoot root = NGUITools.FindInParents<UIRoot>(gameObject);

	//		//if (root != nullptr)
	//		//{
	//		//	fallThrough = root.gameObject;
	//		//}
	//		//else
	//		//{
	//		Transform t = transform;
	//		fallThrough = (t.parent != nullptr) ? t.parent.gameObject : gameObject;
	//		//}
	//	}
	//	if (cachedCamera != nullptr)
	//	{
	//		cachedCamera.eventMask = 0;
	//	}
	//}
	//if (handlesEvents) NGUIDebug.debugRaycast = debug;
}

void InputMgr::Update()
{
//	if (cachedCamera == nullptr)
//	{
//		return;
//	}
//
//	// Only the first UI layer should be processing events
//#if UNITY_EDITOR
//	if (!Application.isPlaying || !handlesEvents) return;
//#else
//	if (!handlesEvents) return;
//#endif
//	current = this;
//
//	// Process touch events first
//	if (useTouch) ProcessTouches();
//	else if (useMouse) ProcessMouse();
//
//	// Custom input processing
//	if (onCustomInput != nullptr) onCustomInput();
//
//	// Clear the selection on the cancel key, but only if mouse input is allowed
//	if (useMouse && mCurrentSelection != nullptr)
//	{
//		if (cancelKey0 != KeyCode.None && GetKeyDown(cancelKey0))
//		{
//			currentScheme = ControlScheme.Controller;
//			currentKey = cancelKey0;
//			selectedObject = nullptr;
//		}
//		else if (cancelKey1 != KeyCode.None && GetKeyDown(cancelKey1))
//		{
//			currentScheme = ControlScheme.Controller;
//			currentKey = cancelKey1;
//			selectedObject = nullptr;
//		}
//	}
//
//	// If nothing is selected, input focus is lost
//	if (mCurrentSelection == nullptr) inputHasFocus = false;
//
//	// Update the keyboard and joystick events
//	if (mCurrentSelection != nullptr) ProcessOthers();
//
//	// If it's time to show a tooltip, inform the object we're hovering over
//	if (useMouse && mHover != nullptr)
//	{
//		float scroll = !string.IsNullOrEmpty(scrollAxisName) ? GetAxis(scrollAxisName) : 0f;
//
//		if (scroll != 0f)
//		{
//			if (onScroll != nullptr) onScroll(mHover, scroll);
//			Notify(mHover, "OnScroll", scroll);
//		}
//
//		if (showTooltips && mTooltipTime != 0f && (mTooltipTime < RealTime.time ||
//			GetKey(KeyCode.LeftShift) || GetKey(KeyCode.RightShift)))
//		{
//			mTooltip = mHover;
//			ShowTooltip(true);
//		}
//	}
//	current = nullptr;
}

void InputMgr::LateUpdate()
{
//#if UNITY_EDITOR
//	if (!Application.isPlaying || !handlesEvents) return;
//#else
//	if (!handlesEvents) return;
//#endif
//	int w = Screen.width;
//	int h = Screen.height;
//
//	if (w != mWidth || h != mHeight)
//	{
//		mWidth = w;
//		mHeight = h;
//
//		//UIRoot.Broadcast("UpdateAnchors");
//
//		if (onScreenResize != nullptr)
//			onScreenResize();
//	}
}

void InputMgr::ProcessMouse()
{
	//// Update the position and delta
	//lastTouchPosition = Input.mousePosition;
	//mMouse[0].delta = lastTouchPosition - mMouse[0].pos;
	//mMouse[0].pos = lastTouchPosition;
	//bool posChanged = mMouse[0].delta.sqrMagnitude > 0.001f;

	//// Propagate the updates to the other mouse buttons
	//for (int i = 1; i < 3; ++i)
	//{
	//	mMouse[i].pos = mMouse[0].pos;
	//	mMouse[i].delta = mMouse[0].delta;
	//}

	//// Is any button currently pressed?
	//bool isPressed = false;
	//bool justPressed = false;

	//for (int i = 0; i < 3; ++i)
	//{
	//	if (Input.GetMouseButtonDown(i))
	//	{
	//		currentScheme = ControlScheme.Mouse;
	//		justPressed = true;
	//		isPressed = true;
	//	}
	//	else if (Input.GetMouseButton(i))
	//	{
	//		currentScheme = ControlScheme.Mouse;
	//		isPressed = true;
	//	}
	//}

	//// No need to perform raycasts every frame
	//if (isPressed || posChanged || mNextRaycast < RealTime.time)
	//{
	//	mNextRaycast = RealTime.time + 0.02f;
	//	if (!Raycast(Input.mousePosition)) hoveredObject = fallThrough;
	//	if (hoveredObject == nullptr) hoveredObject = mGenericHandler;
	//	for (int i = 0; i < 3; ++i) mMouse[i].current = hoveredObject;
	//}

	//bool highlightChanged = (mMouse[0].last != mMouse[0].current);
	//if (highlightChanged) currentScheme = ControlScheme.Mouse;

	//if (isPressed)
	//{
	//	// A button was pressed -- cancel the tooltip
	//	mTooltipTime = 0f;
	//}
	//else if (posChanged && (!stickyTooltip || highlightChanged))
	//{
	//	if (mTooltipTime != 0f)
	//	{
	//		// Delay the tooltip
	//		mTooltipTime = RealTime.time + tooltipDelay;
	//	}
	//	else if (mTooltip != nullptr)
	//	{
	//		// Hide the tooltip
	//		ShowTooltip(false);
	//	}
	//}

	//// Generic mouse move notifications
	//if (posChanged && onMouseMove != nullptr)
	//{
	//	currentTouch = mMouse[0];
	//	onMouseMove(currentTouch.delta);
	//	currentTouch = nullptr;
	//}

	//// The button was released over a different object -- remove the highlight from the previous
	//if ((justPressed || !isPressed) && mHover != nullptr && highlightChanged)
	//{
	//	currentScheme = ControlScheme.Mouse;
	//	currentTouch = mMouse[0];
	//	if (mTooltip != nullptr) ShowTooltip(false);
	//	if (onHover != nullptr) onHover(mHover, false);
	//	Notify(mHover, "OnHover", false);
	//	mHover = nullptr;
	//}

	//// Process all 3 mouse buttons as individual touches
	//for (int i = 0; i < 3; ++i)
	//{
	//	bool pressed = Input.GetMouseButtonDown(i);
	//	bool unpressed = Input.GetMouseButtonUp(i);

	//	if (pressed || unpressed) currentScheme = ControlScheme.Mouse;

	//	currentTouch = mMouse[i];
	//	currentTouchID = -1 - i;
	//	currentKey = KeyCode.Mouse0 + i;

	//	// We don't want to update the last camera while there is a touch happening
	//	if (pressed) currentTouch.pressedCam = currentCamera;
	//	else if (currentTouch.pressed != nullptr) currentCamera = currentTouch.pressedCam;

	//	// Process the mouse events
	//	ProcessTouch(pressed, unpressed);
	//	currentKey = KeyCode.None;
	//}

	//// If nothing is pressed and there is an object under the touch, highlight it
	//if (!isPressed && highlightChanged)
	//{
	//	currentScheme = ControlScheme.Mouse;
	//	mTooltipTime = RealTime.time + tooltipDelay;
	//	mHover = mMouse[0].current;
	//	currentTouch = mMouse[0];
	//	if (onHover != nullptr) onHover(mHover, true);
	//	Notify(mHover, "OnHover", true);
	//}
	//currentTouch = nullptr;

	//// Update the last value
	//mMouse[0].last = mMouse[0].current;
	//for (int i = 1; i < 3; ++i) mMouse[i].last = mMouse[0].last;
}

void InputMgr::ProcessTouches()
{
//	currentScheme = ControlScheme.Touch;
//
//	for (int i = 0; i < Input.touchCount; ++i)
//	{
//		Touch touch = Input.GetTouch(i);
//
//		currentTouchID = allowMultiTouch ? touch.fingerId : 1;
//		currentTouch = GetTouch(currentTouchID);
//
//		bool pressed = (touch.phase == TouchPhase.Began) || currentTouch.touchBegan;
//		bool unpressed = (touch.phase == TouchPhase.Canceled) || (touch.phase == TouchPhase.Ended);
//		currentTouch.touchBegan = false;
//
//		// Although input.deltaPosition can be used, calculating it manually is safer (just in case)
//		currentTouch.delta = pressed ? Vector2.zero : touch.position - currentTouch.pos;
//		currentTouch.pos = touch.position;
//
//		// Raycast into the screen
//		if (!Raycast(currentTouch.pos)) hoveredObject = fallThrough;
//		if (hoveredObject == nullptr) hoveredObject = mGenericHandler;
//		currentTouch.last = currentTouch.current;
//		currentTouch.current = hoveredObject;
//		lastTouchPosition = currentTouch.pos;
//
//		// We don't want to update the last camera while there is a touch happening
//		if (pressed) currentTouch.pressedCam = currentCamera;
//		else if (currentTouch.pressed != nullptr) currentCamera = currentTouch.pressedCam;
//
//		// Double-tap support
//		if (touch.tapCount > 1) currentTouch.clickTime = RealTime.time;
//
//		// Process the events from this touch
//		ProcessTouch(pressed, unpressed);
//
//		// If the touch has ended, remove it from the list
//		if (unpressed) RemoveTouch(currentTouchID);
//		currentTouch.last = nullptr;
//		currentTouch = nullptr;
//
//		// Don't consider other touches
//		if (!allowMultiTouch) break;
//	}
//
//	if (Input.touchCount == 0)
//	{
//		if (useMouse) ProcessMouse();
//#if UNITY_EDITOR
//		else ProcessFakeTouches();
//#endif
//	}
}

void InputMgr::ProcessFakeTouches()
{
	//bool pressed = Input.GetMouseButtonDown(0);
	//bool unpressed = Input.GetMouseButtonUp(0);
	//bool held = Input.GetMouseButton(0);

	//if (pressed || unpressed || held)
	//{
	//	currentTouchID = 1;
	//	currentTouch = mMouse[0];
	//	currentTouch.touchBegan = pressed;
	//	if (pressed) currentTouch.pressTime = RealTime.time;

	//	Vector2 pos = Input.mousePosition;
	//	currentTouch.delta = pressed ? Vector2.zero : pos - currentTouch.pos;
	//	currentTouch.pos = pos;

	//	// Raycast into the screen
	//	if (!Raycast(currentTouch.pos)) hoveredObject = fallThrough;
	//	if (hoveredObject == nullptr) hoveredObject = mGenericHandler;
	//	currentTouch.last = currentTouch.current;
	//	currentTouch.current = hoveredObject;
	//	lastTouchPosition = currentTouch.pos;

	//	// We don't want to update the last camera while there is a touch happening
	//	if (pressed) currentTouch.pressedCam = currentCamera;
	//	else if (currentTouch.pressed != nullptr) currentCamera = currentTouch.pressedCam;

	//	// Process the events from this touch
	//	ProcessTouch(pressed, unpressed);

	//	// If the touch has ended, remove it from the list
	//	if (unpressed) RemoveTouch(currentTouchID);
	//	currentTouch.last = nullptr;
	//	currentTouch = nullptr;
	//}
}

void InputMgr::ProcessOthers()
{
	//currentTouchID = -100;
	//currentTouch = controller;

	//bool submitKeyDown = false;
	//bool submitKeyUp = false;

	//if (submitKey0 != KeyCode.None && GetKeyDown(submitKey0))
	//{
	//	currentKey = submitKey0;
	//	submitKeyDown = true;
	//}

	//if (submitKey1 != KeyCode.None && GetKeyDown(submitKey1))
	//{
	//	currentKey = submitKey1;
	//	submitKeyDown = true;
	//}

	//if (submitKey0 != KeyCode.None && GetKeyUp(submitKey0))
	//{
	//	currentKey = submitKey0;
	//	submitKeyUp = true;
	//}

	//if (submitKey1 != KeyCode.None && GetKeyUp(submitKey1))
	//{
	//	currentKey = submitKey1;
	//	submitKeyUp = true;
	//}

	//if (submitKeyDown || submitKeyUp)
	//{
	//	currentScheme = ControlScheme.Controller;
	//	currentTouch.last = currentTouch.current;
	//	currentTouch.current = mCurrentSelection;
	//	ProcessTouch(submitKeyDown, submitKeyUp);
	//	currentTouch.last = nullptr;
	//}

	//int vertical = 0;
	//int horizontal = 0;

	//if (useKeyboard)
	//{
	//	if (inputHasFocus)
	//	{
	//		vertical += GetDirection(KeyCode.UpArrow, KeyCode.DownArrow);
	//		horizontal += GetDirection(KeyCode.RightArrow, KeyCode.LeftArrow);
	//	}
	//	else
	//	{
	//		vertical += GetDirection(KeyCode.W, KeyCode.UpArrow, KeyCode.S, KeyCode.DownArrow);
	//		horizontal += GetDirection(KeyCode.D, KeyCode.RightArrow, KeyCode.A, KeyCode.LeftArrow);
	//	}
	//}

	//if (useController)
	//{
	//	if (!string.IsNullOrEmpty(verticalAxisName)) vertical += GetDirection(verticalAxisName);
	//	if (!string.IsNullOrEmpty(horizontalAxisName)) horizontal += GetDirection(horizontalAxisName);
	//}

	//// Send out key notifications
	//if (vertical != 0)
	//{
	//	currentScheme = ControlScheme.Controller;
	//	KeyCode key = vertical > 0 ? KeyCode.UpArrow : KeyCode.DownArrow;
	//	if (onKey != nullptr) onKey(mCurrentSelection, key);
	//	Notify(mCurrentSelection, "OnKey", key);
	//}

	//if (horizontal != 0)
	//{
	//	currentScheme = ControlScheme.Controller;
	//	KeyCode key = horizontal > 0 ? KeyCode.RightArrow : KeyCode.LeftArrow;
	//	if (onKey != nullptr) onKey(mCurrentSelection, key);
	//	Notify(mCurrentSelection, "OnKey", key);
	//}

	//if (useKeyboard && GetKeyDown(KeyCode.Tab))
	//{
	//	currentKey = KeyCode.Tab;
	//	currentScheme = ControlScheme.Controller;
	//	if (onKey != nullptr) onKey(mCurrentSelection, KeyCode.Tab);
	//	Notify(mCurrentSelection, "OnKey", KeyCode.Tab);
	//}

	//// Send out the cancel key notification
	//if (cancelKey0 != KeyCode.None && GetKeyDown(cancelKey0))
	//{
	//	currentKey = cancelKey0;
	//	currentScheme = ControlScheme.Controller;
	//	if (onKey != nullptr) onKey(mCurrentSelection, KeyCode.Escape);
	//	Notify(mCurrentSelection, "OnKey", KeyCode.Escape);
	//}

	//if (cancelKey1 != KeyCode.None && GetKeyDown(cancelKey1))
	//{
	//	currentKey = cancelKey1;
	//	currentScheme = ControlScheme.Controller;
	//	if (onKey != nullptr) onKey(mCurrentSelection, KeyCode.Escape);
	//	Notify(mCurrentSelection, "OnKey", KeyCode.Escape);
	//}

	//currentTouch = nullptr;
	//currentKey = KeyCode.None;
}

void InputMgr::ProcessTouch(bool pressed, bool unpressed)
{
	//// Whether we're using the mouse
	//bool isMouse = (currentScheme == ControlScheme.Mouse);
	//float drag = isMouse ? mouseDragThreshold : touchDragThreshold;
	//float click = isMouse ? mouseClickThreshold : touchClickThreshold;

	//// So we can use sqrMagnitude below
	//drag *= drag;
	//click *= click;

	//// Send out the press message
	//if (pressed)
	//{
	//	if (mTooltip != nullptr) ShowTooltip(false);

	//	currentTouch.pressStarted = true;
	//	if (onPress != nullptr) onPress(currentTouch.pressed, false);
	//	Notify(currentTouch.pressed, "OnPress", false);
	//	currentTouch.pressed = currentTouch.current;
	//	currentTouch.dragged = currentTouch.current;
	//	currentTouch.clickNotification = ClickNotification.BasedOnDelta;
	//	currentTouch.totalDelta = Vector2.zero;
	//	currentTouch.dragStarted = false;
	//	if (onPress != nullptr) onPress(currentTouch.pressed, true);
	//	Notify(currentTouch.pressed, "OnPress", true);

	//	// Update the selection
	//	if (currentTouch.pressed != mCurrentSelection)
	//	{
	//		if (mTooltip != nullptr) ShowTooltip(false);
	//		currentScheme = ControlScheme.Touch;
	//		selectedObject = currentTouch.pressed;
	//	}
	//}
	//else if (currentTouch.pressed != nullptr && (currentTouch.delta.sqrMagnitude != 0f || currentTouch.current != currentTouch.last))
	//{
	//	// Keep track of the total movement
	//	currentTouch.totalDelta += currentTouch.delta;
	//	float mag = currentTouch.totalDelta.sqrMagnitude;
	//	bool justStarted = false;

	//	// If the drag process hasn't started yet but we've already moved off the object, start it immediately
	//	if (!currentTouch.dragStarted && currentTouch.last != currentTouch.current)
	//	{
	//		currentTouch.dragStarted = true;
	//		currentTouch.delta = currentTouch.totalDelta;

	//		// OnDragOver is sent for consistency, so that OnDragOut is always preceded by OnDragOver
	//		isDragging = true;

	//		if (onDragStart != nullptr) onDragStart(currentTouch.dragged);
	//		Notify(currentTouch.dragged, "OnDragStart", nullptr);

	//		if (onDragOver != nullptr) onDragOver(currentTouch.last, currentTouch.dragged);
	//		Notify(currentTouch.last, "OnDragOver", currentTouch.dragged);

	//		isDragging = false;
	//	}
	//	else if (!currentTouch.dragStarted && drag < mag)
	//	{
	//		// If the drag event has not yet started, see if we've dragged the touch far enough to start it
	//		justStarted = true;
	//		currentTouch.dragStarted = true;
	//		currentTouch.delta = currentTouch.totalDelta;
	//	}

	//	// If we're dragging the touch, send out drag events
	//	if (currentTouch.dragStarted)
	//	{
	//		if (mTooltip != nullptr) ShowTooltip(false);

	//		isDragging = true;
	//		bool isDisabled = (currentTouch.clickNotification == ClickNotification.None);

	//		if (justStarted)
	//		{
	//			if (onDragStart != nullptr) onDragStart(currentTouch.dragged);
	//			Notify(currentTouch.dragged, "OnDragStart", nullptr);

	//			if (onDragOver != nullptr) onDragOver(currentTouch.last, currentTouch.dragged);
	//			Notify(currentTouch.current, "OnDragOver", currentTouch.dragged);
	//		}
	//		else if (currentTouch.last != currentTouch.current)
	//		{
	//			if (onDragStart != nullptr) onDragStart(currentTouch.dragged);
	//			Notify(currentTouch.last, "OnDragOut", currentTouch.dragged);

	//			if (onDragOver != nullptr) onDragOver(currentTouch.last, currentTouch.dragged);
	//			Notify(currentTouch.current, "OnDragOver", currentTouch.dragged);
	//		}

	//		if (onDrag != nullptr) onDrag(currentTouch.dragged, currentTouch.delta);
	//		Notify(currentTouch.dragged, "OnDrag", currentTouch.delta);

	//		currentTouch.last = currentTouch.current;
	//		isDragging = false;

	//		if (isDisabled)
	//		{
	//			// If the notification status has already been disabled, keep it as such
	//			currentTouch.clickNotification = ClickNotification.None;
	//		}
	//		else if (currentTouch.clickNotification == ClickNotification.BasedOnDelta && click < mag)
	//		{
	//			// We've dragged far enough to cancel the click
	//			currentTouch.clickNotification = ClickNotification.None;
	//		}
	//	}
	//}

	//// Send out the unpress message
	//if (unpressed)
	//{
	//	currentTouch.pressStarted = false;
	//	if (mTooltip != nullptr) ShowTooltip(false);

	//	if (currentTouch.pressed != nullptr)
	//	{
	//		// If there was a drag event in progress, make sure OnDragOut gets sent
	//		if (currentTouch.dragStarted)
	//		{
	//			if (onDragOut != nullptr) onDragOut(currentTouch.last, currentTouch.dragged);
	//			Notify(currentTouch.last, "OnDragOut", currentTouch.dragged);

	//			if (onDragEnd != nullptr) onDragEnd(currentTouch.dragged);
	//			Notify(currentTouch.dragged, "OnDragEnd", nullptr);
	//		}

	//		// Send the notification of a touch ending
	//		if (onPress != nullptr) onPress(currentTouch.pressed, false);
	//		Notify(currentTouch.pressed, "OnPress", false);

	//		// Send a hover message to the object
	//		if (isMouse)
	//		{
	//			if (onHover != nullptr) onHover(currentTouch.current, true);
	//			Notify(currentTouch.current, "OnHover", true);
	//		}
	//		mHover = currentTouch.current;

	//		// If the button/touch was released on the same object, consider it a click and select it
	//		if (currentTouch.dragged == currentTouch.current ||
	//			(currentScheme != ControlScheme.Controller &&
	//			currentTouch.clickNotification != ClickNotification.None &&
	//			currentTouch.totalDelta.sqrMagnitude < drag))
	//		{
	//			if (currentTouch.pressed != mCurrentSelection)
	//			{
	//				mNextSelection = nullptr;
	//				mCurrentSelection = currentTouch.pressed;
	//				if (onSelect != nullptr) onSelect(currentTouch.pressed, true);
	//				Notify(currentTouch.pressed, "OnSelect", true);
	//			}
	//			else
	//			{
	//				mNextSelection = nullptr;
	//				mCurrentSelection = currentTouch.pressed;
	//			}

	//			// If the touch should consider clicks, send out an OnClick notification
	//			if (currentTouch.clickNotification != ClickNotification.None && currentTouch.pressed == currentTouch.current)
	//			{
	//				float time = RealTime.time;

	//				if (onClick != nullptr) onClick(currentTouch.pressed);
	//				Notify(currentTouch.pressed, "OnClick", nullptr);

	//				if (currentTouch.clickTime + 0.35f > time)
	//				{
	//					if (onDoubleClick != nullptr) onDoubleClick(currentTouch.pressed);
	//					Notify(currentTouch.pressed, "OnDoubleClick", nullptr);
	//				}
	//				currentTouch.clickTime = time;
	//			}
	//		}
	//		else if (currentTouch.dragStarted) // The button/touch was released on a different object
	//		{
	//			// Send a drop notification (for drag & drop)
	//			if (onDrop != nullptr) onDrop(currentTouch.current, currentTouch.dragged);
	//			Notify(currentTouch.current, "OnDrop", currentTouch.dragged);
	//		}
	//	}
	//	currentTouch.dragStarted = false;
	//	currentTouch.pressed = nullptr;
	//	currentTouch.dragged = nullptr;
	//}
}

void InputMgr::ShowTooltip(bool val)
{
	//mTooltipTime = 0f;
	//if (onTooltip != nullptr) onTooltip(mTooltip, val);
	//Notify(mTooltip, "OnTooltip", val);
	//if (!val) mTooltip = nullptr;
}

// Ä£ÄâÍ£Ö¹ÍÏ·Å
void InputMgr::simuStopDrag()
{
	//if (currentTouch != nullptr)
	//{
	//	currentTouch.dragStarted = false;
	//	currentTouch.pressed = nullptr;
	//	currentTouch.dragged = nullptr;
	//}
}

void InputMgr::OnApplicationPause()
{
	//MouseOrTouch prev = currentTouch;

	//if (useTouch)
	//{
	//	BetterList<int> ids = new BetterList<int>();

	//	foreach(KeyValuePair<int, MouseOrTouch> pair in mTouches)
	//	{
	//		if (pair.Value != nullptr && pair.Value.pressed)
	//		{
	//			currentTouch = pair.Value;
	//			currentTouchID = pair.Key;
	//			currentScheme = ControlScheme.Touch;
	//			currentTouch.clickNotification = ClickNotification.None;
	//			ProcessTouch(false, true);
	//			ids.Add(currentTouchID);
	//		}
	//	}

	//	for (int i = 0; i < ids.size; ++i)
	//		RemoveTouch(ids[i]);
	//}

	//if (useMouse)
	//{
	//	for (int i = 0; i < 3; ++i)
	//	{
	//		if (mMouse[i].pressed)
	//		{
	//			currentTouch = mMouse[i];
	//			currentTouchID = -1 - i;
	//			currentKey = KeyCode.Mouse0 + i;
	//			currentScheme = ControlScheme.Mouse;
	//			currentTouch.clickNotification = ClickNotification.None;
	//			ProcessTouch(false, true);
	//		}
	//	}
	//}

	//if (useController)
	//{
	//	if (controller.pressed)
	//	{
	//		currentTouch = controller;
	//		currentTouchID = -100;
	//		currentScheme = ControlScheme.Controller;
	//		currentTouch.last = currentTouch.current;
	//		currentTouch.current = mCurrentSelection;
	//		currentTouch.clickNotification = ClickNotification.None;
	//		ProcessTouch(false, true);
	//		currentTouch.last = nullptr;
	//	}
	//}
	//currentTouch = prev;
}