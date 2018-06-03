#pragma once

#include <string>
#include "GContainerObject.h"
#include "MLinkedListNode.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class MLinkedListNode;

class MLinkedList : public GContainerObject
{
protected:
	MLinkedListNode* mHeadNode;
    MLinkedListNode* mTailNode;

public:
	MLinkedList();
	
    void init();
    void dispose();
    void clear();
    bool isHeadExist();
    MLinkedListNode* getHead();
    void addHead(MLinkedListNode* node);

    // 直接重新设置
    void setHead(MLinkedListNode* node);
    bool isTailExist();
    bool isTailExistAndNoEqualHead();
    bool isEmpty();
    MLinkedListNode* getTail();

    void addTail(MLinkedListNode* node);
    // 直接重新设置
    void setTail(MLinkedListNode* node);
    void insertAfterNode(MLinkedListNode* preNode, MLinkedListNode* node);
    void insertBeforeNode(MLinkedListNode* nextNode, MLinkedListNode* node);
    void add(MLinkedListNode* node);
    int count();
    void reverse();
    void remove(MLinkedListNode* node);
    std::string getStr();
};

MY_END_NAMESPACE