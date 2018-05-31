namespace SDK.Lib
{
    public class MLinkedListNode : GObject
    {
        // 一个节点可能在几个列表中，这个 list 字段主要是记录头和尾节点的，如果中间节点就在一个列表中，也可以设置这个字段
        protected MLinkedList mLinkedList;
        protected MLinkedListNode mPreNode;
        protected MLinkedListNode mNextNode;

        public MLinkedListNode()
        {
            this.mLinkedList = null;
            this.mPreNode = null;
            this.mNextNode = null;
        }

        public void init()
        {
            this.addToList();
        }

        public void dispose()
        {
            this.removeFormList();

            this.onDestroy();
        }

        public void onDestroy()
        {
            this.mLinkedList = null;
            this.mPreNode = null;
            this.mNextNode = null;
        }

        public void clear()
        {
            this.removeFormList();

            this.onClear();
        }

        public void onClear()
        {
            this.mPreNode = null;
            this.mNextNode = null;
        }

        // 这个接口尽量不要在接口内部调用，这个接口和逻辑关联可能更大一点，逻辑决定是否设置
        public void setLinkedList(MLinkedList list)
        {
            this.mLinkedList = list;
        }

        public MLinkedList getLinkedList()
        {
            return this.mLinkedList;
        }

        public void setPreNode(MLinkedListNode node)
        {
            this.mPreNode = node;
        }

        public MLinkedListNode getPreNode()
        {
            return this.mPreNode;
        }

        public void setNextNode(MLinkedListNode node)
        {
            this.mNextNode = node;
        }

        public MLinkedListNode getNextNode()
        {
            return this.mNextNode;
        }

        // 如果是在头结点之前插入，List 中头结点就会仍然记录之前的头结点，会错误，这种情况需要逻辑避免，因为一个节点可能在几个列表中
        public void insertBefore(MLinkedListNode node)
        {
            if (null != this.mPreNode)
            {
                this.mPreNode.setNextNode(node);
                node.setPreNode(this.mPreNode);
            }
            else if (null != this.mLinkedList)
            {
                this.mLinkedList.addHead(node);
            }

            node.setNextNode(this);
            this.mPreNode = node;
        }

        public void insertAfter(MLinkedListNode node)
        {
            if (null != this.mNextNode)
            {
                this.mNextNode.setPreNode(node);
                node.setNextNode(this.mNextNode);
            }
            else if (null != this.mLinkedList)
            {
                this.mLinkedList.addTail(node);
            }

            node.setPreNode(this);
            this.mNextNode = node;
        }

        public bool isPreNodeExist()
        {
            return (null != this.mPreNode);
        }

        public bool isNextNodeExist()
        {
            return (null != this.mNextNode);
        }

        public bool isPreAndNextNodeExist()
        {
            return (null != this.mPreNode && null != this.mNextNode);
        }

        public void removeFormList()
        {
            if (null != this.mLinkedList)
            {
                this.mLinkedList.remove(this);
                this.mLinkedList = null;
            }
        }

        public void addToList()
        {
            if (null != this.mLinkedList)
            {
                this.mLinkedList.addTail(this);
            }
        }

        // 获取当前节点到 Tail 数量
        public int toTailCount()
        {
            MLinkedListNode nextNode = null;
            int count = 1;

            nextNode = this.getNextNode();

            while (null != nextNode)
            {
                nextNode = nextNode.getNextNode();
                count += 1;
            }

            return count;
        }

        // 获取当前节点到 Head 数量
        public int toHeadCount()
        {
            MLinkedListNode preNode = null;
            int count = 1;

            preNode = this.getPreNode();

            while (null != preNode)
            {
                preNode = preNode.getPreNode();
                count += 1;
            }

            return count;
        }

        virtual public string getStr()
        {
            return "";
        }

        public void reverse()
        {
            if (null != this.mLinkedList)
            {
                this.mLinkedList.reverse();
            }
        }
    }
}