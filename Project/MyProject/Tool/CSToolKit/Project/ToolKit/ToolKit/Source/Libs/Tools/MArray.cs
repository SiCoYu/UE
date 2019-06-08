namespace SDK.Lib
{
    public class MArray
    {
        public static void Copy(System.Array sourceArray, int sourceIndex, System.Array destinationArray, int destinationIndex, int length)
        {
            System.Array.Copy(sourceArray, sourceIndex, destinationArray, destinationIndex, length);
        }

        public static void Clear(System.Array array, int index, int length)
        {
            System.Array.Clear(array, index, length);
        }

        public static void Reverse(System.Array array, int index = 0, int length = 0)
        {
            if(0 == length)
            {
                length = array.Length;
            }

            System.Array.Reverse(array, index, length);
        }

        public static int IndexOf<T>(T[] array, T value, int startIndex = 0, int count = 0)
        {
            if(0 == count)
            {
                count = array.Length;
            }

            return System.Array.IndexOf(array, value, startIndex, count);
        }
    }
}