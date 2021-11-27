/*  The partitioning algo was inspired by Kaustav Nag sir's 'IX.java' code sent on whatsapp in the algo group
 */
import java.util.*;

class Vertex {
    int nodeId;
    Integer[] partition;
    ArrayList<Vertex> child = new ArrayList<>();
    boolean visited = false;

    Vertex(int nodeId, Integer[] partition) {
        this.nodeId = nodeId;
        this.partition = partition;
    }
}

class edge implements Comparable{
    Vertex a,b;
    int weight;
    edge(Vertex a,Vertex b,int weight){
        this.a=a;
        this.b=b;
        this.weight=weight;
    }

    @Override
    public int compareTo(Object o) {
        return this.weight - ((edge)o).weight;
    }
}
public class Hasse {
    public static void main(String[] args) {

        Scanner sc=new Scanner(System.in);
        System.out.println("Enter the n for hasse graph(1<=n<=20)");
        ArrayList<edge> edges=new ArrayList<>();
        ArrayList<Vertex> hasseGraph = createHasseGraph(Integer.parseInt(sc.nextLine()),edges);

        System.out.println("\nPerforming Breadth First Search");
        breadth_first_search(hasseGraph.get(0));

        reset(hasseGraph);

        System.out.println("\nPerforming Depth First Search");
        depth_first_search(hasseGraph.get(0));

        reset(hasseGraph);

        System.out.println("\nFinding MST:");
        edges=findMST(edges);
        int w=0;
        for(edge e:edges){
            System.out.println(e.a.nodeId+"-"+e.b.nodeId);
            w+=e.weight;
        }
        System.out.println("The net weight is = "+w);

        sc.close();
    }

    public static ArrayList<edge> findMST(ArrayList<edge> edges){
        ArrayList<Vertex> visited = new ArrayList<>();
        ArrayList<edge> MST=new ArrayList<>();
        edge t;

        Collections.sort(edges);
        t=edges.get(0);
        edges.remove(t);
        visited.add(t.a);
        visited.add(t.b);
        MST.add(t);

        while(!edges.isEmpty()){
            Collections.sort(edges);
            for(int i=0;i<edges.size();i++){
                t=edges.get(i);
                if(visited.contains(t.a) && visited.contains(t.b)){
                    edges.remove(t);
                    break;
                }else if(visited.contains(t.a)){
                    edges.remove(t);
                    visited.add(t.a);
                    visited.add(t.b);
                    MST.add(t);
                    break;
                }else if(visited.contains(t.b)){
                    edges.remove(t);
                    visited.add(t.a);
                    visited.add(t.b);
                    MST.add(t);
                    break;
                }
            }
        }
        return MST;
    }
    public static void reset(ArrayList<Vertex> hasseGraph){

        for (Vertex v: hasseGraph)
            v.visited = false;

    }

    public static void breadth_first_search(Vertex v) {

        LinkedList<Vertex> queue = new LinkedList<>();
        v.visited = true;
        queue.add(v);

        while (queue.size() != 0) {
            v = queue.remove();

            System.out.print("nodeId->"+v.nodeId+"   partition : ");
            for(int i=0;i<v.partition.length;i++) {
                if(i!=0)
                    System.out.print("+");
                System.out.print(v.partition[i]);
            }
            System.out.print("\n");

            for (Vertex ve: v.child) {
                if (!ve.visited) {
                    ve.visited = true;
                    queue.add(ve);
                }
            }
        }
    }

    public static void depth_first_search(Vertex v) {

        System.out.print("nodeId->"+v.nodeId+"   partition : ");
        for(int i=0;i<v.partition.length;i++) {
            if(i!=0)
                System.out.print("+");
            System.out.print(v.partition[i]);
        }
        System.out.print("\n");

        v.visited = true;
        for (Vertex ve: v.child) {
            if (!ve.visited) {
                depth_first_search(ve);
            }
        }

    }

    public static ArrayList<Vertex> createHasseGraph(int n,ArrayList<edge> edges) {

        int id = 1,weight;
        Integer[] partition = new Integer[]{n};
        Vertex start = new Vertex(id, partition);
        LinkedList<Vertex> queue = new LinkedList<>();
        HashMap<String, Vertex> hashMap = new HashMap<>();
        ArrayList<Vertex> graph = new ArrayList<>();


        queue.add(start);
        hashMap.put(Arrays.toString(partition), start);

        while (queue.size() != 0) {
            Vertex v = queue.remove();
            graph.add(v);
            for (int i = 0; i < v.partition.length; i++) {
                if(i==v.partition.length-1 || !v.partition[i].equals(v.partition[i + 1]))
                    for (int j = 1; j <= v.partition[i] / 2; j++) {

                        partition = new Integer[v.partition.length + 1];
                        System.arraycopy(v.partition, 0, partition, 0, v.partition.length);
                        partition[i] = j;
                        partition[v.partition.length] = v.partition[i] - j;
                        Arrays.sort(partition,Collections.reverseOrder());

                        String key = Arrays.toString(partition);
                        Vertex ve = hashMap.get(key);
                        if (ve == null) {
                            ve = new Vertex(++id, partition);
                            queue.add(ve);
                            hashMap.put(key, ve);
                        }
                        weight=0;
                        for(int i1=0;i1<v.partition.length;i1++)
                            weight+=ve.partition[i1]*v.partition[i1];
                        edges.add(new edge(v,ve,weight));
                        v.child.add(ve);
                    }
            }
        }

        return graph;
    }
}

