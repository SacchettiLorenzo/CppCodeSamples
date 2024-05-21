import java.util.ArrayList;

public class Vertex<V>{
    private int distance;
    private Vertex predecessor;
    Color color;
    private ArrayList<V> adjacentVertices;

    public Vertex() {
        this.distance = 0;
        this.predecessor = null;
        this.color = Color.WHITE;
        this.adjacentVertices = new ArrayList<>();
    }

    public void setPredecessor(Vertex predecessor) {}
    public Vertex getPredecessor() {return this.predecessor;}
    public void setDistance(int distance) {this.distance = distance;}
    public int getDistance() {return this.distance;}
    public void setColor(Color color) {this.color = color;}
    public Color getColor() {return this.color;}
    public void setAdjacentVertices(ArrayList<V> adjacentVertices) {
        this.adjacentVertices = adjacentVertices;
    }
    public ArrayList<V> getAdjacentVertices() {return this.adjacentVertices;}

    public void addAdjacentVertex(V vertex) {
        this.adjacentVertices.add(vertex);
    }

    public void removeAdjacentVertex(V vertex) {
        this.adjacentVertices.remove(vertex);
    }

    public void printAdjacentVertices() {
        for(V vertex : this.adjacentVertices) {
            System.out.println(vertex);
        }
    }

    public boolean isAdjacent(V vertex) {
        for(V adjacentVertex : this.adjacentVertices) {
            if(adjacentVertex.equals(vertex)) {
                return true;
            }
        }
        return false;
    }

}
