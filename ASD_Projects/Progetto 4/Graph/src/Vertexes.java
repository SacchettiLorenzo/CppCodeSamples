class IntegerVertex extends Vertex {
    public IntegerVertex(Integer value) {
        this.value = value;
    }

    public void setValue(int value) {
        this.value = value;
    }
    public int getValue() {
        return (int)value;
    }
}

class StringVertex extends Vertex {
    public StringVertex(String value) {
        this.value = value;
    }

    public void setValue(String value) {
        this.value = value;
    }
    public String getValue() {
        return (String)value;
    }
}

class FloatVertex extends Vertex {
    public FloatVertex(Float value) {
        this.value = value;
    }
    public void setValue(Float value) {
        this.value = value;
    }
    public Float getValue() {
        return (Float)value;
    }
}
