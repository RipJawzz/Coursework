import java.util.*;
class Edge{
    String a,b;
    Edge(String a,String b){
        this.a=a;
        this.b=b;
    }
}
public class q5 {
    public static  void main(String[] args){
        Scanner sc=new Scanner(System.in);
        List<String> s1=new ArrayList<>();
        List<String> s2=new ArrayList<>();
        List<Edge> edges=new ArrayList<>();
        int size1,size2,nedges;
        String str;
        System.out.println("Enter the number of vertices on each side of graph");
        size1=Integer.parseInt(sc.nextLine());
        size2=Integer.parseInt(sc.nextLine());
        System.out.println("Enter the number of edges");
        nedges=Integer.parseInt(sc.nextLine());
        System.out.println("Enter the "+size1+" number of vertices");
        for(int i=0;i<size1;i++){
            str=sc.nextLine();
            s1.add(str);
        }
        System.out.println("Enter the "+size2+" number of vertices");
        for(int i=0;i<size2;i++){
            str=sc.nextLine();
            s2.add(str);
        }
        System.out.println("Enter the edges in the form a b");
        for(int i=0;i<nedges;i++){
            String[] ip=sc.nextLine().split("\\s");
            String a,b;
            a=ip[0];
            b=ip[1];
            if(!(s1.contains(a) || s2.contains(a)) || !(s1.contains(b) || s2.contains(b))){
                System.out.println("The edge doesn't exist");
            }else if((s1.contains(a) && s1.contains(b)) || (s2.contains(b) && s2.contains(a))){
                edges.add(new Edge(a, b));
            }
        }
        if(edges.isEmpty())
            System.out.println("All edges are violated");
        else {
            System.out.println("The edges that are respected by the cut are:-");
            for (Edge e : edges) {
                System.out.println(e.a + " -- " + e.b);
            }
        }

    }
}
