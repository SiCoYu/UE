#include "MyProject.h"
#include "Common.h"
#include "DDFileTree.h"
#include "UtilFileTree.h"

void UtilFileTree::createFileTree()
{
	//in the .h of parent class: 

	//TSharedPtr<class SDDFileTree> DDFileTree;

	//in your parent class in which you want to create the widget
	if (!DDFileTree.IsValid())
	{
		//DDFileTree = SAssignNew(DDFileTree, SDDFileTree, Cast<UDDEdEngine>(this));
		SAssignNew(DDFileTree, SDDFileTree, GEngineData->getMyEngine());
	}
}