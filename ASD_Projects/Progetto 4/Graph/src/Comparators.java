import java.util.Comparator;


class IntegerComparator implements Comparator<Integer> {

    @Override
    public int compare(Integer o1, Integer o2) {
        return o1.compareTo(o2);
    }
}

class FloatComparator implements Comparator<Float> {

    @Override
    public int compare(Float o1, Float o2) {
        return o1.compareTo(o2);
    }
}

class StringComparator implements Comparator<String> {

    @Override
    public int compare(String o1, String o2) {
        return o1.compareTo(o2);
    }

}

class  StringVertexComparator implements Comparator<StringVertex> {
    @Override
    public int compare(StringVertex o1, StringVertex o2) {
        return ((String)o1.value).compareTo((String)o2.value);
    }
}
