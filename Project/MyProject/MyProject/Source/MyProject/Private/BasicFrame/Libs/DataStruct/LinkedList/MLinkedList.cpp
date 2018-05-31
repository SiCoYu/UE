namespace SDK.Lib
{
    public class MLinkedList : GContainerObject
    {
        protected MLinkedListNode mHeadNode;
        protected MLinkedListNode mTailNode;

        public MLinkedList()
        {
            this.mHeadNode = nullptr;
            this.mTailNode = nullptr;
        }

        public void init()
        {

        }

        public void dispose()
        {
            this.mHeadNode = nullptr;
            this.mTailNode = nullptr;
        }

        public void clear()
        {
            this.mHeadNode = nullptr;
            this.mTailNode = nullptr;
        }

        public bool isHeadExist()
        {
            return (nullptr != this.mHeadNode);
        }

        public MLinkedListNode getHead()
        {
            return this.mHeadNode;
        }

        public void addHead(MLinkedListNode node)
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
        public void setHead(MLinkedListNode node)
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

        public bool isTailExist()
        {
            bool ret = (nullptr != this.mTailNode);
            return ret;
        }

        public bool isTailExistAndNoEqualHead()
        {
            return (nullptr != this.mTailNode && this.mHeadNode != this.mTailNode);
        }

        public bool isEmpty()
        {
            return (nullptr == this.mHeadNode && nullptr == this.mTailNode);
        }

        public MLinkedListNode getTail()
        {
            return this.mTailNode;
        }

        public void addTail(MLinkedListNode node)
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
        public void setTail(MLinkedListNode node)
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

        public void insertAfterNode(MLinkedListNode preNode, MLinkedListNode node)
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

        public void insertBeforeNode(MLinkedListNode nextNode, MLinkedListNode node)
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

        public void add(MLinkedListNode node)
        {
            this.addTail(node);
        }

        public int count()
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

        public void reverse()
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

        public void remove(MLinkedListNode node)
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

        public string getStr()
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
    }
}