import java.util.Collection;
import java.util.HashMap;
import java.util.Objects;
import java.util.Optional;

public class Graph<V ,L> implements AbstractGraph<V,L> {

    boolean directed;
    boolean labelled;
    private HashMap<Integer,V> vertices;

    private HashMap<Integer,AbstractEdge<V,L>> edges;

    public Graph(boolean directed, boolean labelled) {
        this.directed = directed;
        this.labelled = labelled;
        vertices = new HashMap<Integer, V>();
        edges = new HashMap<Integer,AbstractEdge<V,L>>();
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
            //check if the key already exist to avoid replacement
                if(!vertices.containsKey(a.value.toString().hashCode())) {
                    vertices.put(a.value.toString().hashCode(),a);
                }
            return true;
        }else{
            return false;
        }
    }

    @Override
    public boolean addEdge(V a, V b, L l) {
        try {
            if (a instanceof Vertex && b instanceof Vertex) {
                if (labelled) {
                    if (l == null) {
                        throw new NoLabelException("missing label");
                    }
                }
                        //check if vertex are in the map

                        if (!isLabelled()) {
                            edges.put( a.hashCode() + b.hashCode(), new Edge<V,L>(a,b, Optional.empty()));
                        }else{
                            edges.put( a.hashCode() + b.hashCode(), new Edge<V,L>(a,b, Optional.of(l)));
                        }

                        if(Objects.equals((String) a.value, "torino")){
                            int aa = 0;
                        }
                        vertices.get(a.value.toString().hashCode()).addAdjacentVertex(vertices.get(b.value.toString().hashCode()));


                        if (!isDirected()) {
                            vertices.get(b.value.toString().hashCode()).addAdjacentVertex(vertices.get(a.value.toString().hashCode()));
                        }
                        return true;



            }
            return false;
        }catch (Exception e){
            System.out.println(e.getMessage());
            return false;
        }
    }

    public Edge getEdge(V a, V b) {
        return (Edge) edges.get(a.hashCode() + b.hashCode());
    }

    @Override
    public boolean containsNode(V a) {
        return vertices.containsKey(a.value.toString().hashCode());
    }

    @Override
    public boolean containsEdge(V a, V b) {
        return edges.containsKey(a.value.toString().hashCode()+b.value.toString().hashCode());
    }

    @Override
    public boolean removeNode(V a) {
        return vertices.remove(a.value.toString().hashCode()).equals(a);
        //todo: remove all edges with that node
    }

    @Override
    public boolean removeEdge(V a, V b) {
        AbstractEdge<V, L> res = edges.remove(a.value.toString().hashCode()+b.toString().hashCode());
        return res.getStart().equals(a) && res.getEnd().equals(b);
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
        return (Collection<V>) vertices.values();
    }

    @Override
    public Collection<? extends AbstractEdge<V, L>> getEdges() {
        return (Collection<? extends AbstractEdge<V, L>>) edges;
    }

    @Override
    public Collection<V> getNeighbours(V a) {
        if(a instanceof Vertex){
            return (Collection<V>)vertices.get(a.value.toString().hashCode()).getAdjacentVertices();
        }
    return null;
    }

    @Override
    public L getLabel(V a, V b) {
        return edges.get(a.value.toString().hashCode()+b.value.toString().hashCode()).getLabel();
    }

}

