#include "MyProject.h"
#include "MLinkedListNode.h"

MY_BEGIN_NAMESPACE(MyNS)

MLinkedListNode::MLinkedListNode()
{
	this->mLinkedList = nullptr;
	this->mPreNode = nullptr;
	this->mNextNode = nullptr;
}

void MLinkedListNode::init()
{
	this->addToList();
}

void MLinkedListNode::dispose()
{
	this->removeFormList();

	this->onDestroy();
}

void MLinkedListNode::onDestroy()
{
	this->mLinkedList = nullptr;
	this->mPreNode = nullptr;
	this->mNextNode = nullptr;
}

void MLinkedListNode::clear()
{
	this->removeFormList();

	this->onClear();
}

void MLinkedListNode::onClear()
{
	this->mPreNode = nullptr;
	this->mNextNode = nullptr;
}

// 这个接口尽量不要在接口内部调用，这个接口和逻辑关联可能更大一点，逻辑决定是否设置
void MLinkedListNode::setLinkedList(MLinkedList list)
{
	this->mLinkedList = list;
}

MLinkedList MLinkedListNode::getLinkedList()
{
	return this->mLinkedList;
}

void MLinkedListNode::setPreNode(MLinkedListNode node)
{
	this->mPreNode = node;
}

MLinkedListNode MLinkedListNode::getPreNode()
{
	return this->mPreNode;
}

void MLinkedListNode::setNextNode(MLinkedListNode node)
{
	this->mNextNode = node;
}

MLinkedListNode MLinkedListNode::getNextNode()
{
	return this->mNextNode;
}

// 如果是在头结点之前插入，List 中头结点就会仍然记录之前的头结点，会错误，这种情况需要逻辑避免，因为一个节点可能在几个列表中
void MLinkedListNode::insertBefore(MLinkedListNode node)
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

void MLinkedListNode::insertAfter(MLinkedListNode node)
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

bool MLinkedListNode::isPreNodeExist()
{
	return (nullptr != this->mPreNode);
}

bool MLinkedListNode::isNextNodeExist()
{
	return (nullptr != this->mNextNode);
}

bool MLinkedListNode::isPreAndNextNodeExist()
{
	return (nullptr != this->mPreNode && nullptr != this->mNextNode);
}

void MLinkedListNode::removeFormList()
{
	if (nullptr != this->mLinkedList)
	{
		this->mLinkedList.remove(this);
		this->mLinkedList = nullptr;
	}
}

void MLinkedListNode::addToList()
{
	if (nullptr != this->mLinkedList)
	{
		this->mLinkedList.addTail(this);
	}
}

// 获取当前节点到 Tail 数量
int MLinkedListNode::toTailCount()
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
int MLinkedListNode::toHeadCount()
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

string MLinkedListNode::getStr()
{
	return "";
}

void MLinkedListNode::reverse()
{
	if (nullptr != this->mLinkedList)
	{
		this->mLinkedList.reverse();
	}
}

MY_END_NAMESPACE