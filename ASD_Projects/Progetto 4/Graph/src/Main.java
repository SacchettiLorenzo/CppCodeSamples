import java.io.File;
import java.io.FileNotFoundException;
import java.util.NoSuchElementException;
import java.util.Optional;
import java.util.Scanner;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    public static void readFromCSV(File file, Graph<StringVertex,Edge<StringVertex,Float>> g){
        Scanner sc = null;
        StringVertex a = null;
        StringVertex b = null;
        Edge<StringVertex,Float> l = null;
        try {
            sc = new Scanner(file);
        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        }
        sc.useDelimiter(",|\\n");
        while (sc.hasNext())
        {
            try{
                a = new StringVertex(sc.next());
                b = new StringVertex(sc.next());
                l = new Edge<StringVertex,Float>(a,b, Optional.of(sc.nextFloat()));
            }catch(Exception e){
                System.out.println(e);
            }

            g.addNode(a);
            g.addNode(b);
            g.addEdge(a,b,l);
        }
        sc.close();
    }

    public static void main(String[] args) {


//    Graph<IntegerVertex,Edge<IntegerVertex,Integer>> g = new Graph<IntegerVertex,Edge<IntegerVertex,Integer>>(false,false);
//
//    IntegerVertex v1 = new IntegerVertex(1);
//    IntegerVertex v2 = new IntegerVertex(2);
//    IntegerVertex v3 = new IntegerVertex(3);
//    g.addNode(v1);
//    g.addNode(v2);
//    g.addNode(v3);
//    Edge<IntegerVertex,Integer> e1 = new Edge<IntegerVertex,Integer>(v1,v2, Optional.empty());
//    Edge<IntegerVertex,Integer> e2= new Edge<IntegerVertex,Integer>(v1,v3, Optional.empty());
//    g.addEdge(e1.start,e1.end,e1);
//    g.addEdge(e2.start,e2.end,e2);
//
//    Object o = g.getNeighbours(v1);

        Graph<StringVertex,Edge<StringVertex,Float>> g = new Graph<StringVertex,Edge<StringVertex,Float>>(false,true);
        readFromCSV(new File("/home/lorenzo/Documents/C/CppCodeSamples/ASD_Projects/Progetto 4/Graph/src/italian_dist_graph.csv"),g);
        Object o = g.getNeighbours(new StringVertex("torino"));

    }
}