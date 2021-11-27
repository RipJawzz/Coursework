import java.util.*;
class Edge{
    String a,b;
    int weight=0;
    Edge(String a,String b,int weight){
        this.a=a;
        this.b=b;
        this.weight=weight;
    }
}
public class q6 {
    public static  void main(String[] args){
        Scanner sc=new Scanner(System.in);
        List<String> s1=new ArrayList<>();
        List<String> s2=new ArrayList<>();
        int size1,size2,nedges;
        Edge edge=null;
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
        System.out.println("Enter the edges in the form a b weight");
        for(int i=0;i<nedges;i++){
            String[] ip=sc.nextLine().split("\\s");
            String a,b;
            int w;
            a=ip[0];
            b=ip[1];
            w=Integer.parseInt(ip[2]);
            if(!(s1.contains(a) || s2.contains(a)) || !(s1.contains(b) || s2.contains(b))){
                System.out.println("The edge doesn't exist");
            }else if((s1.contains(a) && s2.contains(b)) || (s1.contains(b) && s2.contains(a))){
                if(edge==null || w<edge.weight)
                    edge=new Edge(a, b, w);
            }
        }
        if(edge==null)
            System.out.println("No edges crossing the cut");
        else
            System.out.println(edge.a+" -- "+edge.b+" with weight = "+edge.weight+" is the lightest edge to cross the cut");
    }
}
