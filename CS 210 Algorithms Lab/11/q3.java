import java.util.*;
public class q3{
    public static  void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        ArrayList<Group> components=new ArrayList<>();
        int nEdges;
        System.out.println("Enter the number of edges");
        nEdges=Integer.parseInt(sc.nextLine());
        System.out.println("Enter the edges in the form u v");
        for(int i=0;i<nEdges;i++){
            String[] str=sc.nextLine().split("\\s");
            Group g1=null,g2=null;
            for(Group g : components){
                if(g.component.contains(str[0])){
                    g1=g;
                }
                if(g.component.contains(str[1])){
                    g2=g;
                }
            }
            if(g1==g2){
                if(g1==null){
                    g1=new Group();
                    g1.component.add(str[1]);
                    g1.component.add(str[0]);
                    components.add(g1);
                }
            }else if(g1==null){
                g2.component.add(str[0]);
            }else if(g2==null){
                g1.component.add(str[1]);
            }else{
                g1.unionComponent(g2);
                components.remove(g2);
            }
        }
        System.out.println("The connectd components are:-");
        for(Group g:components){
            for(String a:g.component){
                System.out.print(a+" ");
            }
            System.out.print("\n\n");
        }
    }
}
class Group{
    ArrayList<String> component=new ArrayList<>();
    void unionComponent(Group a){
        component.addAll(a.component);

    }
}