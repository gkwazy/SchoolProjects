package com.company;

import org.w3c.dom.ls.LSOutput;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        System.out.println("Hello World");
        int numbers[] = new int[10];
        for (int i = 0; i < 10; i++) {
            numbers[i] = (int) ((Math.random() * 100) + 1);
        }
        int sum = 0;
        for (int i = 0; i < 10; i++) {
            System.out.print(numbers[i] + ", ");
            sum += numbers[i];
        }
        System.out.println("The Sum is: " + sum);
        System.out.println("What is your Name and Age?");
        Scanner myScanner = new Scanner(System.in);
        String userName = myScanner.nextLine();
        String stringAge = myScanner.nextLine();
        int usersAge = Integer.parseInt(stringAge);
        System.out.println("Your Name is: " + userName);
        System.out.println("Your age is: " + usersAge);

        if (usersAge>=18){
            System.out.print("You are old enough to vote, you better register!\n");
        }
        else{
            System.out.print("Sorry, you are not old enough to vote\n");
        }

//This is a list of if that will see what generation they are. It starts out with the oldest possibility and works down from there.
        if (usersAge > 80){
            System.out.print("Well look at that, your part of the Greatest Generation.\n");
        }
        else if (usersAge <=80 && usersAge > 60){
            System.out.print("A Baby Boomer I see, well the Beatles were a great band.\n");
        }
        else if (usersAge <=60 && usersAge > 40){
            System.out.print("Generdation X, So how was the 80's?\n");
        }
        else if (usersAge <= 40 && usersAge > 20){
            System.out.print("The Millennial or Gen Y, How was using dial up as a kid?\n");
        }
        else {
            System.out.print("iKid, well we all have to start somewhere.\n");
        }
    }
}
