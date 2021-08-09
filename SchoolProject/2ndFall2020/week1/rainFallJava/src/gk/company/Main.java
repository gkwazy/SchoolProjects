package gk.company;

import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.lang.reflect.Array;

public class Main {

    public static void main(String[] args) throws IOException {
          String[] months = {"January", "February", "March", "April", "May", "June", "July", "August",
                "September", "October", "November", "December"};

        RainReader myFile = new RainReader();
        String fileText = "\n\nRainfall data for " + myFile.cityName +  ":\n";;

        for(String month:months){
            double averageForMonthDouble = (myFile.averageMonthRainFall(myFile.data, month));
            String averageForMonth = String.format("%.02f", averageForMonthDouble);
            fileText += "The average rainfall amount for " + month + " is " + averageForMonth + " inches.\n";
        }

        double[] sortedRainFall = myFile.sortMonths(myFile.data);


        fileText += "The rain amounts (in inches) of the four driest months are: " +
                String.format("%.02f",  sortedRainFall[0]) + ", " +
                String.format("%.02f",  sortedRainFall[1]) + ", " +
                String.format("%.02f",  sortedRainFall[2]) + ", " +
                String.format("%.02f",  sortedRainFall[3]);
        fileText += "\nTThe rain amounts (in inches) of the four wettest months are: " +
                String.format("%.02f",  sortedRainFall[236]) + ", "+
                String.format("%.02f",  sortedRainFall[237]) + ", " +
                String.format("%.02f",  sortedRainFall[238]) + ", " +
                String.format("%.02f",  sortedRainFall[239]);

        cityData medians = myFile.meanMonth(myFile.data);

        fileText += "\nThe median months is " + medians.month + " " + (medians.year) + " " +
                String.format("%.02f", medians.rainFall);






        FileWriter file = new FileWriter("results.txt");
        PrintWriter output = new PrintWriter(file, false);
        output.write(fileText);
        output.flush();
    }
}