package gk.company;

/*Question 1- Why are the answers not the same
    with the thread both writing to the in answer they are getting overwriting one other
    and losing information as they do it
*/


public class Main extends Thread{
    static int answer;

    public static void sayHello() throws InterruptedException {
        Thread[] threadArray = new Thread[10];
        for (int i = 0; i<10; i++){
           threadArray[i] = new Thread(() ->{
               for (int j = 0; j<100; j++){
                   if (j %10 == 0){
                       System.out.println("");
                       System.out.println("");
                   }
                   System.out.print(" hello number " + j + " from thread number " + Thread.currentThread().getId());
               }
           });
           threadArray[i].start();
        }
        for(Thread thread : threadArray){
            thread.join();
        }
    }

    public static void badSum() throws InterruptedException {
        answer = 0;
        int maxValue = 40000;
        Thread[] secondArray = new Thread[10];
        for(int i = 0; i < secondArray.length; i++){
            final int finalI = i;
            secondArray[i] = new Thread(() ->{
                for (int j = finalI*maxValue/secondArray.length;
                     j < Math.min((finalI+1)*maxValue/secondArray.length, maxValue); j++){
                    answer += j;
                }
            });
            secondArray[i].start();
        }
        for(Thread thread: secondArray){
            thread.join();
        }
        System.out.println(answer);
    }



    public static void main(String[] args) throws InterruptedException {
        int maxNum = 40000;
        int secondAnswer = 0;
//    sayHello();
        badSum();
        for(int i = 0; i < maxNum;i++){
            secondAnswer =+ (maxNum*(maxNum -1)/2);
        }
        System.out.println(secondAnswer);
    }
}
