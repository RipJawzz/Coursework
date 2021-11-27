import java.util.*;
class Vertex implements Comparable{
    ArrayList<Vertex> to=new ArrayList<>();
    int start=-1,end=-1;
    String name;
    Vertex(String name){
        this.name=name;
    }
    @Override
    public int compareTo(Object v){
        return ((Vertex)v).end -this.end;
    }
}
public class q1 {
    public static  void main(String[] args){
        Scanner sc=new Scanner(System.in);
        HashMap<String,Vertex> map=new HashMap<>();
        ArrayList<Vertex> vert=new ArrayList<>();
        int v,e;
        String str;
        System.out.println("Enter the number of vertices and edges");
        v=Integer.parseInt(sc.nextLine());
        e=Integer.parseInt(sc.nextLine());
        System.out.println("Enter the vertices names");
        for(int i=0;i<v;i++){
            str=sc.nextLine();
            Vertex New=new Vertex(str);
            map.put(str, New);
            vert.add(New);
        }
        System.out.println("Enter the edges in the form a b where a->b");
        for(int i=0;i<e;i++){
            String[] ip=sc.nextLine().split("\\s");
            String a,b;
            a=ip[0];
            b=ip[1];
            if(!map.containsKey(a) || !map.containsKey(b))
                    System.out.println("The vertex isnt present in graph");
            else{
                map.get(a).to.add(map.get(b));
                //map.get(b).from.add(map.get(a));
            }
        }
        int time=0;
        for(Vertex ve:map.values()){
            if(ve.start==-1) {
                time = topo_sort(ve, time);
            }
        }
        topo_print(vert);
    }
    public static int topo_sort(Vertex head,int time){
        head.start=time++;
        for(Vertex ve:head.to){
            if(ve.start==-1){
                time=topo_sort(ve, time);
            }
        }
        head.end=time++;
        return time;
    }
    public static void topo_print(ArrayList<Vertex> vertices){
        Collections.sort(vertices);
        for(Vertex v:vertices)
            System.out.println(v.name+" ");
        System.out.println("\n");
    }
}
