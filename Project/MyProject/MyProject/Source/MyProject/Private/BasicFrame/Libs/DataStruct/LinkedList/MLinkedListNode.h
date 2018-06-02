#pragma once

#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

public class MLinkedListNode : public GObject
{
    // 一个节点可能在几个列表中，这个 list 字段主要是记录头和尾节点的，如果中间节点就在一个列表中，也可以设置这个字段
protected:
	MLinkedList mLinkedList;
    MLinkedListNode mPreNode;
    MLinkedListNode mNextNode;

public:
	MLinkedListNode();
	
    void init();
    void dispose();
    void onDestroy();
    void clear();
    void onClear();

    // 这个接口尽量不要在接口内部调用，这个接口和逻辑关联可能更大一点，逻辑决定是否设置
    void setLinkedList(MLinkedList list);
    MLinkedList getLinkedList();
    void setPreNode(MLinkedListNode node);
    MLinkedListNode getPreNode();
    void setNextNode(MLinkedListNode node);
    MLinkedListNode getNextNode();
    // 如果是在头结点之前插入，List 中头结点就会仍然记录之前的头结点，会错误，这种情况需要逻辑避免，因为一个节点可能在几个列表中
    void insertBefore(MLinkedListNode node);
    void insertAfter(MLinkedListNode node);
    bool isPreNodeExist();
    bool isNextNodeExist();
    bool isPreAndNextNodeExist();
    void removeFormList();

    void addToList();
    // 获取当前节点到 Tail 数量
    int toTailCount();
    // 获取当前节点到 Head 数量
    int toHeadCount();
    virtual string getStr();
    void reverse();
};

MY_END_NAMESPACE