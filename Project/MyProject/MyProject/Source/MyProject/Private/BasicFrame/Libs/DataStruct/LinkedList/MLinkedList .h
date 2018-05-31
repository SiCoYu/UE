#pragma once

#include "GContainerObject.h"
#include "MLinkedListNode.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class MLinkedList : public GContainerObject
{
protected:
	MLinkedListNode mHeadNode;
    MLinkedListNode mTailNode;

public:
	MLinkedList()
    {
        this.mHeadNode = nullptr;
        this.mTailNode = nullptr;
    }

    void init()
    {

    }

    void dispose()
    {
        this.mHeadNode = nullptr;
        this.mTailNode = nullptr;
    }

    void clear()
    {
        this.mHeadNode = nullptr;
        this.mTailNode = nullptr;
    }

    bool isHeadExist()
    {
        return (nullptr != this.mHeadNode);
    }

    MLinkedListNode getHead()
    {
        return this.mHeadNode;
    }

    void addHead(MLinkedListNode node)
    {
        if (nullptr != this.mHeadNode)
        {
            node.setNextNode(this.mHeadNode);
            this.mHeadNode.setPreNode(node);
            this.mHeadNode = node;
        }
        else
        {
            this.mHeadNode = node;
            this.mTailNode = node;
        }
    }

    // 直接重新设置
    void setHead(MLinkedListNode node)
    {
        if (nullptr != this.mHeadNode)
        {
            node.setNextNode(this.mHeadNode.getNextNode());

            if (nullptr != this.mHeadNode.getNextNode())
            {
                this.mHeadNode.getNextNode().setPreNode(node);
            }

            this.mHeadNode = node;
        }
        else
        {
            this.mHeadNode = node;
            this.mTailNode = node;
        }
    }

    bool isTailExist()
    {
        bool ret = (nullptr != this.mTailNode);
        return ret;
    }

    bool isTailExistAndNoEqualHead()
    {
        return (nullptr != this.mTailNode && this.mHeadNode != this.mTailNode);
    }

    bool isEmpty()
    {
        return (nullptr == this.mHeadNode && nullptr == this.mTailNode);
    }

    MLinkedListNode getTail()
    {
        return this.mTailNode;
    }

    void addTail(MLinkedListNode node)
    {
        if (nullptr != this.mTailNode)
        {
            node.setPreNode(this.mTailNode);
            this.mTailNode.setNextNode(node);
            this.mTailNode = node;
        }
        else
        {
            this.mHeadNode = node;
            this.mTailNode = node;
        }
    }

    // 直接重新设置
    void setTail(MLinkedListNode node)
    {
        if (nullptr != this.mTailNode)
        {
            node.setPreNode(this.mTailNode.getPreNode());

            if (nullptr != this.mTailNode.getPreNode())
            {
                this.mHeadNode.getPreNode().setNextNode(node);
            }

            this.mTailNode = node;
        }
        else
        {
            this.mHeadNode = node;
            this.mTailNode = node;
        }
    }

    void insertAfterNode(MLinkedListNode preNode, MLinkedListNode node)
    {
        if (nullptr != node)
        {
            if (nullptr != preNode)
            {
                var nextNode = preNode.getNextNode();

                node.setPreNode(preNode);
                preNode.setNextNode(node);

                if (nullptr != nextNode)
                {
                    nextNode.setPreNode(node);
                    node.setNextNode(nextNode);
                }
            }
            else
            {
                this.addTail(node);
            }
        }
    }

    void insertBeforeNode(MLinkedListNode nextNode, MLinkedListNode node)
    {
        if (nullptr != node)
        {
            if (nullptr != nextNode)
            {
                var preNode = node.getPreNode();

                nextNode.setPreNode(node);
                node.setNextNode(nextNode);

                if (nullptr != preNode)
                {
                    node.setPreNode(preNode);
                    preNode.setNextNode(node);
                }
            }
            else
            {
                this.addHead(node);
            }
        }
    }

    void add(MLinkedListNode node)
    {
        this.addTail(node);
    }

    int count()
    {
        MLinkedListNode tmpNode = nullptr;
        tmpNode = this.mHeadNode;
        int count = 0;

        while (nullptr != tmpNode)
        {
            count += 1;
            tmpNode = tmpNode.getNextNode();
        }

        return count;
    }

    void reverse()
    {
        if (!this.isEmpty())
        {
            if (this.mHeadNode == this.mTailNode)
            {
                this.remove(this.mTailNode);
                this.addHead(this.mHeadNode);
            }
            else
            {
                MLinkedListNode curNode = nullptr;
                MLinkedListNode nextNode = nullptr;

                nextNode = this.mHeadNode.getNextNode();

                while (nullptr != nextNode)
                {
                    curNode = nextNode;
                    nextNode = nextNode.getNextNode();

                    this.remove(curNode);
                    this.addHead(curNode);
                }
            }
        }
    }

    void remove(MLinkedListNode node)
    {
        if (nullptr != node.getPreNode())
        {
            node.getPreNode().setNextNode(node.getNextNode());
        }
        else
        {
            this.mHeadNode = node.getNextNode();
        }

        if (nullptr != node.getNextNode())
        {
            node.getNextNode().setPreNode(node.getPreNode());
        }
        else
        {
            this.mTailNode = node.getPreNode();
        }

        node.onClear();
    }

    string getStr()
    {
        string str = "";
        MLinkedListNode tmpNode = nullptr;
        tmpNode = this.mHeadNode;
        bool isFirstNode = true;

        while (nullptr != tmpNode)
        {
            if (isFirstNode)
            {
                isFirstNode = false;
            }
            else
            {
                str += "/n";
            }

            tmpNode = tmpNode.getNextNode();
            str += tmpNode.getStr();
        }

        return str;
    }
};

MY_END_NAMESPACE