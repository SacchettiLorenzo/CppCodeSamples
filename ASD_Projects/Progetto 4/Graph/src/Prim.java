import java.util.Collection;


public class Prim {
    public static <V extends Vertex, L extends Edge<V, Number>> Collection<? extends AbstractEdge<V, L>> minimumSpanningForest(Graph<V, L> graph) {
        // calcola la minima foresta ricoprente con l'algoritmo di Prim
        // restituisce la collezione degli archi che formano la foresta

        StringVertexComparator vertexComparator = new StringVertexComparator();
        PriorityQueue<StringVertex> queue = new PriorityQueue<StringVertex>(vertexComparator, PriorityQueue.HeapType.MAX);

        for (V v : graph.getNodes()){
            queue.push((StringVertex) v);
        }

        return null;
    }
}
