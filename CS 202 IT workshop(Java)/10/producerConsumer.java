import java.util.*;
class Q {
    Queue<Integer> buffer=new LinkedList<>();
    int size;
    boolean done=false;
    Q(int size){
        this.size=size;
    }
    synchronized void get()
    {
        System.out.println("Got: " + buffer.remove());

    }
    synchronized void put(int n)
    {
        buffer.add(n);
        System.out.println("Put: " + n);
    }
}

class producer extends Thread
{
    Q q;
    producer(Q q) {
        this.q = q;
    }

    public void run() {
        int i = 0;
        while(i<q.size*3) {
            if(q.buffer.size()<=q.size)
            q.put(i++);
        }
        q.done=true;
    }
}

class consumer extends Thread{
    Q q;
    consumer(Q q) {
        this.q = q;
    }
    public void run() {
        while(!q.done) {
            if(!q.buffer.isEmpty())q.get();
        }
    }
}

public class producerConsumer{

    public static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        System.out.println("Enter the buffer size");
        int size=Integer.parseInt(sc.nextLine());
        Q q = new Q(size);
        producer p=new producer(q);
        consumer c=new consumer(q);
        p.start();
        c.start();

    }

}
