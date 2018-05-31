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
	MLinkedListNode()
    {
        this->mLinkedList = nullptr;
        this->mPreNode = nullptr;
        this->mNextNode = nullptr;
    }

    void init()
    {
        this->addToList();
    }

    void dispose()
    {
        this->removeFormList();

        this->onDestroy();
    }

    void onDestroy()
    {
        this->mLinkedList = nullptr;
        this->mPreNode = nullptr;
        this->mNextNode = nullptr;
    }

    void clear()
    {
        this->removeFormList();

        this->onClear();
    }

    void onClear()
    {
        this->mPreNode = nullptr;
        this->mNextNode = nullptr;
    }

    // 这个接口尽量不要在接口内部调用，这个接口和逻辑关联可能更大一点，逻辑决定是否设置
    void setLinkedList(MLinkedList list)
    {
        this->mLinkedList = list;
    }

    MLinkedList getLinkedList()
    {
        return this->mLinkedList;
    }

    void setPreNode(MLinkedListNode node)
    {
        this->mPreNode = node;
    }

    MLinkedListNode getPreNode()
    {
        return this->mPreNode;
    }

    void setNextNode(MLinkedListNode node)
    {
        this->mNextNode = node;
    }

    MLinkedListNode getNextNode()
    {
        return this->mNextNode;
    }

    // 如果是在头结点之前插入，List 中头结点就会仍然记录之前的头结点，会错误，这种情况需要逻辑避免，因为一个节点可能在几个列表中
    void insertBefore(MLinkedListNode node)
    {
        if (nullptr != this->mPreNode)
        {
            this->mPreNode.setNextNode(node);
            node.setPreNode(this->mPreNode);
        }
        else if (nullptr != this->mLinkedList)
        {
            this->mLinkedList.addHead(node);
        }

        node.setNextNode(this);
        this->mPreNode = node;
    }

    void insertAfter(MLinkedListNode node)
    {
        if (nullptr != this->mNextNode)
        {
            this->mNextNode.setPreNode(node);
            node.setNextNode(this->mNextNode);
        }
        else if (nullptr != this->mLinkedList)
        {
            this->mLinkedList.addTail(node);
        }

        node.setPreNode(this);
        this->mNextNode = node;
    }

    bool isPreNodeExist()
    {
        return (nullptr != this->mPreNode);
    }

    bool isNextNodeExist()
    {
        return (nullptr != this->mNextNode);
    }

    bool isPreAndNextNodeExist()
    {
        return (nullptr != this->mPreNode && nullptr != this->mNextNode);
    }

    void removeFormList()
    {
        if (nullptr != this->mLinkedList)
        {
            this->mLinkedList.remove(this);
            this->mLinkedList = nullptr;
        }
    }

    void addToList()
    {
        if (nullptr != this->mLinkedList)
        {
            this->mLinkedList.addTail(this);
        }
    }

    // 获取当前节点到 Tail 数量
    int toTailCount()
    {
        MLinkedListNode nextNode = nullptr;
        int count = 1;

        nextNode = this->getNextNode();

        while (nullptr != nextNode)
        {
            nextNode = nextNode.getNextNode();
            count += 1;
        }

        return count;
    }

    // 获取当前节点到 Head 数量
    int toHeadCount()
    {
        MLinkedListNode preNode = nullptr;
        int count = 1;

        preNode = this->getPreNode();

        while (nullptr != preNode)
        {
            preNode = preNode.getPreNode();
            count += 1;
        }

        return count;
    }

    virtual string getStr()
    {
        return "";
    }

    void reverse()
    {
        if (nullptr != this->mLinkedList)
        {
            this->mLinkedList.reverse();
        }
    }
};

MY_END_NAMESPACE