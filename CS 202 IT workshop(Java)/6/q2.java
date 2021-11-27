class Add{
    public static void main(String[] args) {
        // write your code here
        int sum=0,len=args.length;
        if(len==0 || len==1)
          System.out.println("ERROR: Enter atleast 2 integers");
        else{
        for(String i:args){
            sum+=Integer.parseInt(i);
        }
        System.out.println("The addition gives "+sum);
      }
    }
}
