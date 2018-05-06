#pragma once

/**
 * @url https://wiki.unrealengine.com/Slate,_Tree_View_Widget,_Ex:_In-Editor_File_Structure_Explorer
 */

class SDDFileTree;

class UtilFileTree : public UObject
{
public:
	TSharedPtr<class SDDFileTree> DDFileTree;

public:
	void createFileTree();
};