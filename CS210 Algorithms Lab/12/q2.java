import java.util.*;
class q2 {
    public static void main(String[] args){
        Scanner sc=new Scanner(System.in);
        int nEdge,weight;
        Vertex a,b;
        HashMap<String,Vertex> map = new HashMap<>();
        System.out.println("Enter the number of edges in the directed graph without negative weight cycle");
        nEdge=Integer.parseInt(sc.nextLine());
        System.out.println("Enter all the edges in the form a b w, where a and b are the name of the two vertices and w is the weight\nThe edge is from a to b");
        for(int i=0;i<nEdge;i++){
            String[] str=sc.nextLine().split("\\s");
            a=map.get(str[0]);
            b=map.get(str[1]);
            weight=Integer.parseInt(str[2]);
            if(a==null) {
                a = new Vertex(str[0]);
                map.put(str[0],a);
            }
            if(b==null) {
                b = new Vertex(str[1]);
                map.put(str[1],b);
            }
            Edge e=new Edge(weight,b);
            a.adjacent.add(e);
        }
        System.out.println("Enter the name of the source node");
        a=map.get(sc.nextLine());
        a.dist=0;
        Djik(a);
        System.out.println("Distance to all nodes from source node:-");
        for(Vertex v:map.values()){
            System.out.print(v.name+" ");
            if(v.dist==Integer.MAX_VALUE)
                System.out.println("is unreachable");
            else
                System.out.println(v.dist);
        }
    }
    public static void Djik(Vertex v){
        for(Edge e : v.adjacent){
            if(v.dist+e.weight<e.v.dist){
                e.v.dist=v.dist+e.weight;
                Djik(e.v);
            }
        }
    }
}
class Edge{
    int weight;
    Vertex v;
    Edge(int weight,Vertex v){
        this.weight=weight;
        this.v=v;
    }
}
class Vertex{
    String name;
    int dist=Integer.MAX_VALUE;
    ArrayList<Edge> adjacent=new ArrayList<>();
    Vertex(String name){
        this.name=name;
    }

}