//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    public static void main(String[] args) {

    Graph<IntegerVertex,Edge<IntegerVertex,Integer>> g = new Graph<IntegerVertex,Edge<IntegerVertex,Integer>>(false,false);

    IntegerVertex v1 = new IntegerVertex(1);
    IntegerVertex v2 = new IntegerVertex(2);
    IntegerVertex v3 = new IntegerVertex(3);
    g.addNode(v1);
    g.addNode(v2);
    g.addNode(v3);
    Edge<IntegerVertex,Integer> e1 = new Edge<IntegerVertex,Integer>(v1,v2);
    Edge<IntegerVertex,Integer> e2= new Edge<IntegerVertex,Integer>(v1,v3);
    g.addEdge(e1.start,e1.end,e1);
    g.addEdge(e2.start,e2.end,e2);

    Object o = g.getNeighbours(v1);

    }
}