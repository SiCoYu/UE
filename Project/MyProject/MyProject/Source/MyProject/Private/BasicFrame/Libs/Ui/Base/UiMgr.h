#ifndef __UiMgr_H
#define __UiMgr_H

#include <map>
#include "MList.h"
#include "UiFormId.h"
#include "EventDispatchDelegate.h"
#include "UiCanvas.h"
#include "UiLayer.h"
#include "UiAttrItem.h"
#include "UiAttrSystem.h"
#include "Form.h"
#include "GObject.h"
#include "PlatformDefine.h"

using namespace NSFormId;

class UForm;

MY_BEGIN_NAMESPACE(MyNS)

class UiCanvas;
class UiAttrSystem;
class UiLoadingItem;
class IDispatchObject;
class ClassAssetInsRes;

/**
 * @brief ���� UI ����
 * 1. �����´�����Form�����������Ĳ�������formId������
 * 2. UI ���ԭ����Ҫ��������Դ������ɲ������߼���С�Ĺ���������߼�����Դͬʱ���У���Ϊ MVC �ṹʵ����Ҫд�ܶ���룬�����Ҫ���治���� MVC �ṹ
 */
class UiMgr : public GObject
{
protected:
	std::map<UiFormId, UForm*> mId2FormDic;
	std::vector<UiCanvas*> mCanvasList;
	UiAttrSystem* mUiAttrSystem;

	std::map<UiFormId, UiLoadingItem*> mId2CodeLoadingItemDic;         // ��¼��ǰ�������ڼ��ص���
	std::map<UiFormId, UiLoadingItem*> mId2WidgetLoadingItemDic;         // ��¼��ǰ���ڿؼ����ڼ��ص���

	MList<UiFormId> mTmpList;
	//GameObject mSceneUIRootGo;           // ÿһ������������һ�������Ľڵ㣬ר�ŷ�һЩ Scene �� UI ��һЩ��Ϣ

public:
	UiMgr();

	void init();
	void dispose();

	template <class T>
	T* loadForm(UiFormId formId);

	template <class T>
	T* getForm(UiFormId formId);

	template <class T>
	T* loadAndShow(UiFormId formId);

	void createCanvas();
	void findCanvasActor();

	void showForm(UiFormId formId);
	void _showFormInternal(UiFormId formId);
	void _hideFormInternal(UiFormId formId);
	void exitForm(UiFormId formId, bool bForce = false);
	void _exitFormInternal(UiFormId formId);
	void addForm(UForm* form);

	UiLayer* getLayer(UiCanvasId canvasID, UiLayerId layerID);

	void addFormNoReady(UForm* form);
	bool hasForm(UiFormId formId);

	void loadWidgetRes(UiFormId formId);
	void loadFromFile(std::string reaPath, EventDispatchDelegate onLoadEventHandle);

	void onCodeLoadEventHandle(IDispatchObject* dispObj);
	void onWidgetLoadEventHandle(IDispatchObject* dispObj);
	void onCodeloadedByRes(ClassAssetInsRes* res);
	void onCodeLoadedByForm(UForm* form);
	void onWidgetloadedByRes(ClassAssetInsRes* res);
	void onWidgetAuxUIClassloadedByRes(IDispatchObject* res);

	void onResize(int viewWidth, int viewHeight);

	void exitAllForm();
	void findSceneUIRootActor();
	//void unloadUIBySceneType(UISceneType unloadSceneType, UISceneType loadSceneTpe);
};

#include "UiMgr.inl"			// ģ������ʵ��

MY_END_NAMESPACE

#endif				// __UiMgr_H