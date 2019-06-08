namespace SDK.Lib
{
    public class MLockQueue<T> : GObject
    {
        protected MLockList<T> mList;

        public MLockQueue(string name)
        {
            this.mList = new MLockList<T>(name);
        }

        public void push(T item)
        {
            this.mList.add(item);
        }

        public T pop()
        {
            return mList.removeAt(0);
        }
    }
}