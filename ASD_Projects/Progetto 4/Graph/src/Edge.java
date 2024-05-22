public class Edge<V extends Vertex,L> implements AbstractEdge<V,L> {

    V start;
    V end;
    L label;

    public Edge(V start, V end) {
        this.start = start;
        this.end = end;
    }

    @Override
    public V getStart() {
        return this.start;
    }

    @Override
    public V getEnd() {
        return this.end;
    }

    @Override
    public L getLabel() {
        return this.label;
    }
}
