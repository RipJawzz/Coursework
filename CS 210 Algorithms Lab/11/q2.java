import java.util.*;
public class q2{
    public static void main(String[] args){
        Scanner sc=new Scanner(System.in);
        int nEdge;
        Vertex a,b;
        HashMap<String,Vertex> map = new HashMap<>();
        ArrayList<Vertex> arr=new ArrayList<>();
        System.out.println("Enter the number of edges");
        nEdge=Integer.parseInt(sc.nextLine());
        System.out.println("Enter all the edges in the form a b, where edges is from a to b");
        for(int i=0;i<nEdge;i++){
            String[] str=sc.nextLine().split("\\s");
            a=map.get(str[0]);
            b=map.get(str[1]);
            if(a==null) {
                a = new Vertex(str[0]);
                map.put(str[0],a);
                arr.add(a);
            }
            if(b==null) {
                b = new Vertex(str[1]);
                map.put(str[1],b);
                arr.add(b);
            }
            a.to.add(b);
            b.from.add(a);
        }
        int time=1;
        for(Vertex ve:map.values()){
            if(ve.start==0) {
                time = DFS(ve,time,false);
            }
        }
        for(Vertex ve:map.values()){
            ve.invert();
        }
        Collections.sort(arr);
        time=1;
        System.out.println("The strongly connected components are");
        for(Vertex v:arr){
            if(v.start==0) {
                time = DFS(v, 1, true);
                System.out.print("\n");
            }
        }
    }
    public static int DFS(Vertex head,int time,boolean print){
        head.start=time++;
        if(print==true)
            System.out.print(head.name+" ");
        for(Vertex ve:head.to){
            if(ve.start==0){
                time=DFS(ve, time,print);
            }
        }
        head.end=time++;
        return time;
    }
}

class Vertex implements Comparable{
    String name;
    int start=0,end=0;
    ArrayList<Vertex> to=new ArrayList<>();
    ArrayList<Vertex> from=new ArrayList<>();
    Vertex(String name){
        this.name=name;
    }
    @Override
    public int compareTo(Object o) {
        return -this.end+((Vertex)o).end;
    }
    public void invert(){
        ArrayList<Vertex> temp=to;
        to=from;
        from=temp;
        start=0;
    }
}