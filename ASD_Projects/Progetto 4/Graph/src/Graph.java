import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.List;

public class Graph<V,L> implements AbstractGraph<V,L> {

    boolean directed;
    boolean labelled;
    private ArrayList<V> vertices;
    private ArrayList<AbstractEdge<V,L>> edges;

    public Graph(boolean directed, boolean labelled) {
        this.directed = directed;
        this.labelled = labelled;
        vertices = new ArrayList<V>();
        edges = new ArrayList<AbstractEdge<V,L>>();
    }

    @Override
    public boolean isDirected() {
        return this.directed;
    }

    @Override
    public boolean isLabelled() {
        return this.labelled;
    }

    @Override
    public boolean addNode(V a) {
        if(a instanceof Vertex) {
            vertices.add(a);
            return true;
        }else{
            return false;
        }
    }

    @Override
    public boolean addEdge(V a, V b, L l) {
        if(a instanceof Vertex && b instanceof Vertex && l instanceof Edge<?,?>) {
            if(((Edge<?, ?>) l).start.equals(a) && ((Edge<?, ?>) l).end.equals(b)) {
                edges.add((Edge<V,L>)l);
                ((Vertex<V>) a).addAdjacentVertex(b);
                ((Vertex<V>) b).addAdjacentVertex(a);
                return true;
            }

        }
        return false;
    }

    @Override
    public boolean containsNode(V a) {
        for(V v : vertices) {
            if(v.equals(a)) {
                return true;
            }
        }
        return false;
    }

    @Override
    public boolean containsEdge(V a, V b) {
        for(AbstractEdge<V,L> e : edges) {
            if(e.getStart().equals(a) && e.getEnd().equals(b)) {
                return true;
            }
        }
        return false;
    }

    @Override
    public boolean removeNode(V a) {
        for(V v : vertices) {
            if(v.equals(a)) {
                vertices.remove(v);
                return true;
            }
        }
        return false;
    }

    @Override
    public boolean removeEdge(V a, V b) {
        for(AbstractEdge<V,L> e : edges) {
            if(e.getStart().equals(a) && e.getEnd().equals(b)) {
                edges.remove(e);
                return true;
            }
        }
        return false;
    }

    @Override
    public int numNodes() {
        return vertices.size();
    }

    @Override
    public int numEdges() {
        return edges.size();
    }

    @Override
    public Collection<V> getNodes() {
        return vertices;
    }

    @Override
    public Collection<? extends AbstractEdge<V, L>> getEdges() {
        return edges;
    }

    @Override
    public Collection<V> getNeighbours(V a) {
        if(a instanceof Vertex){
            for(V v : vertices) {
                if(v.equals(a)) {
                    return (((Vertex)v).getAdjacentVertices());
                }
            }
        }
    return null;
    }

    @Override
    public L getLabel(V a, V b) {
        for(AbstractEdge<V,L> e : edges) {
            if(e.getStart().equals(a) && e.getEnd().equals(b)) {
                e.getLabel();
            }
        }
        return null;
    }
}

