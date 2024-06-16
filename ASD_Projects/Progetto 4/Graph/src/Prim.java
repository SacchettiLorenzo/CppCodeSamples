import java.util.Collection;
import java.util.HashMap;


public class Prim {
    public static <V extends Vertex, L extends Edge<V, Number>> Collection<? extends AbstractEdge<V, L>> minimumSpanningForest(Graph<V, L> graph) {
        // calcola la minima foresta ricoprente con l'algoritmo di Prim
        // restituisce la collezione degli archi che formano la foresta

        VertexComparator vertexComparator = new VertexComparator();
        PriorityQueue<Vertex> queue = new PriorityQueue<Vertex>(vertexComparator, PriorityQueue.HeapType.MIN);


        for (V v : graph.getNodes()){

            //find the minimum weight of the edge
            Float min = Float.MAX_VALUE;
            for (Vertex b : v.getAdjacentVertices()){
                Float edgeWeight = (Float) graph.getEdge(v,b);
                Float edgeWeight = (Float) edges.get(v.hashCode() + b.hashCode()).getLabel().label;
                if(edgeWeight < min){
                    min = edgeWeight;
                }
            }
            v.value = min;

            queue.push((StringVertex) v);
        }


        return null;
    }
}
