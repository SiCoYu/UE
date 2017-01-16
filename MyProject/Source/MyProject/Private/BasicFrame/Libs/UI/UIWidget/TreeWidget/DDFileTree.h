#pragma once

//DD File Tree Item
#include "DDFileTreeItem.h"
#include "MyGameEngineBase.h"

/**
* @url https://wiki.unrealengine.com/Slate,_Tree_View_Widget,_Ex:_In-Editor_File_Structure_Explorer
*/

DECLARE_LOG_CATEGORY_EXTERN(MFileTree_LogCategory, Log, All);

//~~~ Forward Declarations ~~~
//class UDDEdEngine;
// error C2338: TWeakObjectPtr can only be constructed with UObject types
// 必须包含类型 UMyEngine 的定义，不能仅仅是声明
//class UMyEngine;

typedef STreeView< FDDFileTreeItemPtr > SDDFileTreeView;

/**
* File Tree View
*/
class SDDFileTree : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SDDFileTree)
	{}

	SLATE_END_ARGS()

	//~~~~~~~~
	//		DDEdEngine
	//~~~~~~~~
public:
	//owns this
	//TWeakObjectPtr<class UDDEdEngine> DDEdEngine;
	TWeakObjectPtr<class UMyGameEngineBase> mMyEngine;

	/** Refresh the Tree */
	//bool DoRefresh;

	//~~~
public:
	/** Widget constructor */
	//void Construct(const FArguments& Args, TWeakObjectPtr<class UDDEdEngine> IN_DDEdEngine);
	void Construct(const FArguments& Args, TWeakObjectPtr<class UMyGameEngineBase> IN_DDEdEngine);

	/** Destructor */
	~SDDFileTree();

	/** @return Returns the currently selected category item */
	FDDFileTreeItemPtr GetSelectedDirectory() const;

	/** Selects the specified category */
	void SelectDirectory(const FDDFileTreeItemPtr& CategoryToSelect);

	/** @return Returns true if the specified item is currently expanded in the tree */
	bool IsItemExpanded(const FDDFileTreeItemPtr Item) const;

private:
	/** Called to generate a widget for the specified tree item */
	TSharedRef<ITableRow> DDFileTree_OnGenerateRow(FDDFileTreeItemPtr Item, const TSharedRef<STableViewBase>& OwnerTable);

	/** Given a tree item, fills an array of child items */
	void DDFileTree_OnGetChildren(FDDFileTreeItemPtr Item, TArray< FDDFileTreeItemPtr >& OutChildren);

	/** Called when the user clicks on an  item, or when selection changes by some other means */
	void DDFileTree_OnSelectionChanged(FDDFileTreeItemPtr Item, ESelectInfo::Type SelectInfo);

	/** Rebuilds the category tree from scratch */
	void RebuildFileTree();

	/** SWidget overrides */
	//virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) OVERRIDE;
	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

private:
	/** The tree view widget*/
	TSharedPtr< SDDFileTreeView > DDFileTreeView;

	/** The Core Data for the Tree Viewer! */
	TArray< FDDFileTreeItemPtr > Directories;
};