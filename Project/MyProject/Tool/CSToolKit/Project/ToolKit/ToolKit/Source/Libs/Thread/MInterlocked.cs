using System.Threading;

namespace SDK.Lib
{
    public class MInterlocked
    {
        public MInterlocked()
        {

        }

        public int increment(ref int location)
        {
            return Interlocked.Increment(ref location);
        }

        public int decrement(ref int location)
        {
            return Interlocked.Decrement(ref location);
        }
    }
}