import java.util.*;
public class q5{
    public static void main(String[] args){
        Scanner sc=new Scanner(System.in);
        HashMap<String,Integer> map=new HashMap<>();
        HashMap<Integer,String> map2=new HashMap<>();
        int nVertex,nEdges;
        System.out.println("Enter the number of vertices");
        nVertex=Integer.parseInt(sc.nextLine());
        int[][] edge=ini_edge(nVertex);
        System.out.println("Enter the number of edges present");
        nEdges=Integer.parseInt(sc.nextLine());
        System.out.println("Enter the edges as a b w, where w is the weight and edge is from a to b");

        int index=0;
        for(int i=0;i<nEdges;i++){
            String[] str=sc.nextLine().split("\\s");
            Integer v1=map.get(str[0]),v2=map.get(str[1]),w=Integer.parseInt(str[2]);
            if(v1==null){
                v1=index++;
                map.put(str[0],v1);
                map2.put(v1, str[0]);
            }
            if(v2==null){
                v2=index++;
                map.put(str[1],v2);
                map2.put(v2,str[1]);
            }
            edge[v1][v2]=w;
        }

        edge=floyd_warshall(edge, 1);
        boolean neg=neg_cycle(edge);
        if(neg)
            System.out.println("There is a negative weight cycle in the graph");
        else {
            System.out.println("Printing all pair shortest paths");
            for (int i1 = 0; i1 < nVertex; i1++) {
                System.out.println("For " + map2.get(i1) + " :-");
                for (int i2 = 0; i2 < nVertex; i2++) {
                    System.out.print(map2.get(i2) + " ");
                    if (edge[i1][i2] == Integer.MAX_VALUE)
                        System.out.println("is unreachable");
                    else
                        System.out.println(edge[i1][i2]);

                }
                System.out.print("\n\n");
            }
        }
    }
    public static int[][] floyd_warshall(int[][] edge,int level){

        if(level==edge.length)
            return edge;
        int[][] next_edge=ini_edge(edge.length);
        for(int i1=0;i1<edge.length;i1++){
            for(int i2=0;i2< edge.length;i2++){
                next_edge[i1][i2]=edge[i1][i2];
                for(int im=0;im<edge.length;im++){
                    if(im!=i1 && im!=i2 && edge[i1][im]!=Integer.MAX_VALUE && edge[im][i2]!=Integer.MAX_VALUE && edge[i1][im]+edge[im][i2]<edge[i1][i2]){
                        next_edge[i1][i2]=edge[i1][im]+edge[im][i2];
                    }
                }
            }
        }
        edge=null;
        return floyd_warshall(next_edge, ++level);
    }
    public static boolean neg_cycle(int[][] edge){
        for(int i1=0;i1<edge.length;i1++){
            for(int i2=0;i2< edge.length;i2++){
                for(int im=0;im<edge.length;im++){
                    if(im!=i1 && im!=i2 && edge[i1][im]!=Integer.MAX_VALUE && edge[im][i2]!=Integer.MAX_VALUE && edge[i1][im]+edge[im][i2]<edge[i1][i2]){
                        return true;
                    }
                }
            }
        }
        return false;
    }
    public static int[][] ini_edge(int l){
        int[][] edge=new int[l][l];
        for(int i1=0;i1<l;i1++){
            for(int i2=0;i2<l;i2++){
                if(i1==i2)
                    edge[i1][i2]=0;
                else
                    edge[i1][i2]=Integer.MAX_VALUE;
            }
        }
        return edge;
    }
    public static void print_mat(int[][] edge){
        for(int i1=0;i1<edge.length;i1++){
            for(int i2=0;i2<edge.length;i2++) {
                if(edge[i1][i2]==Integer.MAX_VALUE)
                    System.out.print("inf ");
                else
                    System.out.print(edge[i1][i2] + " ");
            }
            System.out.println();
        }
        System.out.println();
    }
}
