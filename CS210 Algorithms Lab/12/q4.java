import java.util.*;
public class q4 {
    public static void main(String[] args){
        Scanner sc=new Scanner(System.in);
        int nEdge,weight;
        Vertex a,b;
        HashMap<String,Vertex> map = new HashMap<>();
        ArrayList<Edge> edgeList=new ArrayList<>();
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
            Edge e=new Edge(weight,a,b);
            edgeList.add(e);
        }
        int nVertex=map.size();

        for(Vertex s : map.values()){
            s.dist = 0;
            BellFord(edgeList, nVertex);
            boolean negCycle = check_negCycle(edgeList);
            if (negCycle)
                System.out.println("Graph has a negative weight cycle");
            else {
                System.out.println("Distance to all nodes from "+s.name+" :-");
                for (Vertex v : map.values()) {
                    System.out.print(v.name + " ");
                    if (v.dist == Integer.MAX_VALUE)
                        System.out.println("is unreachable");
                    else
                        System.out.println(v.dist);
                }
            }
            reset_Graph(map);
        }
    }
    public static void reset_Graph(HashMap<String,Vertex> map){
        for(Vertex v:map.values()){
            v.dist=Integer.MAX_VALUE;
        }
    }
    public static void BellFord(ArrayList<Edge> edgeList,int nVert){
        for(int i=0;i<nVert-1;i++){
            for(Edge e:edgeList){
                if(e.source.dist!=Integer.MAX_VALUE && e.destination.dist>e.source.dist+e.weight){
                    e.destination.dist=e.source.dist+e.weight;
                }
            }
        }
    }
    public static boolean check_negCycle(ArrayList<Edge> edgeList){
        for(Edge e:edgeList){
            if(e.source.dist!=Integer.MAX_VALUE && e.source.dist+e.weight<e.destination.dist)
                return true;
        }
        return false;
    }
}
class Edge{
    int weight;
    Vertex source,destination;

    Edge(int weight,Vertex source,Vertex destination){
        this.weight=weight;
        this.source=source;
        this.destination=destination;
    }
}
class Vertex{
    String name;
    int dist=Integer.MAX_VALUE;
    Vertex(String name){
        this.name=name;
    }

}