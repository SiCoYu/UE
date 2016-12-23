#ifndef __UIMgr_H
#define __UIMgr_H

#include <map>
#include "MList.h"
#include "UIFormId.h"
#include "EventDispatchDelegate.h"
#include "UICanvas.h"
#include "UILayer.h"
#include "UIAttrItem.h"
#include "UIAttrSystem.h"
#include "Form.h"

using namespace NSFormId;

class UForm;
class UICanvas;
class UIAttrSystem;
class UILoadingItem;
class IDispatchObject;
class UIAssetRes;

/**
 * @brief ���� UI ����
 * 1. �����´�����Form�����������Ĳ�������ID������
 * 2. UI ���ԭ����Ҫ��������Դ������ɲ������߼���С�Ĺ���������߼�����Դͬʱ���У���Ϊ MVC �ṹʵ����Ҫд�ܶ���룬�����Ҫ���治���� MVC �ṹ
 */
class UIMgr
{
protected:
	std::map<UIFormId, UForm*> mId2FormDic;
	std::vector<UICanvas*> mCanvasList;
	UIAttrSystem* mUiAttrs;

	std::map<UIFormId, UILoadingItem*> mId2CodeLoadingItemDic;         // ��¼��ǰ�������ڼ��ص���
	std::map<UIFormId, UILoadingItem*> mId2WidgetLoadingItemDic;         // ��¼��ǰ���ڿؼ����ڼ��ص���

	MList<UIFormId> mTmpList;
	//GameObject mSceneUIRootGo;           // ÿһ������������һ�������Ľڵ㣬ר�ŷ�һЩ Scene �� UI ��һЩ��Ϣ

public:
	UIMgr();
	template <class T>
	T* loadForm(UIFormId formID);

	template <class T>
	T* getForm(UIFormId formID);

	template <class T>
	T* loadAndShow(UIFormId ID);

	void createCanvas();
	void findCanvasGO();
	void showForm(UIFormId ID);
	void showFormInternal(UIFormId ID);
	void hideFormInternal(UIFormId ID);
	void exitForm(UIFormId ID, bool bForce = false);
	void exitFormInternal(UIFormId ID);
	void addForm(UForm* form);
	UILayer* getLayer(UICanvasId canvasID, UILayerId layerID);
	void addFormNoReady(UForm* form);
	UForm* getForm(UIFormId ID);
	bool hasForm(UIFormId ID);
	void loadForm(UIFormId ID);
	void loadWidgetRes(UIFormId ID);
	void loadFromFile(std::string reaPath, EventDispatchDelegate onLoadEventHandle);
	void onCodeLoadEventHandle(IDispatchObject* dispObj);
	void onWidgetLoadEventHandle(IDispatchObject* dispObj);
	void onCodeloadedByRes(UIAssetRes* res);
	void onCodeLoadedByForm(UForm* form);
	void onWidgetloadedByRes(UIAssetRes* res);
	void onResize(int viewWidth, int viewHeight);
	void exitAllWin();
	void findSceneUIRootGo();
	//void unloadUIBySceneType(UISceneType unloadSceneType, UISceneType loadSceneTpe);
};

#include "UIMgr.inl"			// ģ������ʵ��

#endif				// __UIMANAGER_H