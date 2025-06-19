package ch15;

public class Exec1{
    public static void main(String[] args) {
        try{
            Process p=Runtime.getRuntime().exec("mspaint");
            p.waitFor();
         }catch(Exception e){
         }
    }
}
