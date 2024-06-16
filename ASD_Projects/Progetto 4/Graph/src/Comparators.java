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

class  VertexComparator implements Comparator<Vertex> {
    @Override
    public int compare(Vertex o1, Vertex o2) {
        return (((Float)o1.getDistance()).compareTo((Float) o2.getDistance()) );
    }
}