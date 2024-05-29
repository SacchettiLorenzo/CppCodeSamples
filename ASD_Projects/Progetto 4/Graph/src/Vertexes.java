class IntegerVertex extends Vertex {



    public IntegerVertex(Integer value) {
        super.value = value;
    }

    public void setValue(int value) {
        super.value = (int)value;
    }
    public int getValue() {
        return (int) super.value;
    }
}

class StringVertex extends Vertex {


    public StringVertex(String value) {

        super.value = (String)value;
    }

    public void setValue(String value) {
        super.value = value;
    }
    public String getValue() {
        return (String)super.value;
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
