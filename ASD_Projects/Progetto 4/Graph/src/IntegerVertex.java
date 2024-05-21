public class IntegerVertex extends Vertex<Integer> {
    int value;
    public IntegerVertex(Integer value) {
        this.value = value;
    }

    public void setValue(int value) {
        this.value = value;
    }
    public int getValue() {
        return value;
    }
}
