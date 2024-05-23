import java.util.Optional;

public class Edge<V extends Vertex,L> implements AbstractEdge<V,L> {

    V start;
    V end;
    L label;

    public Edge(V start, V end, Optional<L> label) {
        this.start = start;
        this.end = end;
        if(label.isPresent()) {
            this.label = label.get();
        }else{
            this.label = null;
        }
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
