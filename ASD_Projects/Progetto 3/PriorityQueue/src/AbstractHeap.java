import java.util.AbstractMap;

public interface AbstractHeap<T> {
    public int Parent(int index);
    public int Left(int index);
    public int Right(int index);
    public AbstractMap.SimpleEntry<Integer,T> Insert(T value);
    public void Extract();
    public void Heapify(int index);
}
