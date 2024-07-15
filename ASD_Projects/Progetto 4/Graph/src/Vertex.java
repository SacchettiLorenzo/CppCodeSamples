import java.util.ArrayList;

public class Vertex{

    Object value;
    private Float distance; //DFS parameter
    private Vertex predecessor;
    Color color;
    private ArrayList<Vertex> adjacentVertices;

    public Vertex(Object value) {
        this.value = value;
        this.distance = 0f;
        this.predecessor = null;
        this.color = Color.WHITE;
        this.adjacentVertices = new ArrayList<>();
    }

    public void setPredecessor(Vertex predecessor) {}
    public Vertex getPredecessor() {return this.predecessor;}
    public void setDistance(Float distance) {this.distance = distance;}
    public Float getDistance() {return this.distance;}
    public void setColor(Color color) {this.color = color;}
    public Color getColor() {return this.color;}
    public void setAdjacentVertices(ArrayList<Vertex> adjacentVertices) {
        this.adjacentVertices = adjacentVertices;
    }
    public ArrayList<Vertex> getAdjacentVertices() {return this.adjacentVertices;}

    public void addAdjacentVertex(Vertex vertex) {
        boolean found = false;
        for(Vertex v: adjacentVertices) {
            if(v.equals(vertex)) {
                found = true;
            }
        }
        if(!found){
            adjacentVertices.add(vertex);
        }
    }

    public void removeAdjacentVertex(Vertex vertex) {
        this.adjacentVertices.remove(vertex);
    }

    public void printAdjacentVertices() {
        for(Vertex vertex : this.adjacentVertices) {
            System.out.println(vertex);
        }
    }

    public boolean isAdjacent(Vertex vertex) {
        for(Vertex adjacentVertex : this.adjacentVertices) {
            if(adjacentVertex.equals(vertex)) {
                return true;
            }
        }
        return false;
    }

}
