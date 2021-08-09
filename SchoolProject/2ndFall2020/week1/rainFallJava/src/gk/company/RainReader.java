package gk.company;

import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.Scanner;

public class RainReader {
    String myFile = "rainfall_results.txt";
    ArrayList<cityData> data = new ArrayList<cityData>();
    String cityName;

    public RainReader() throws FileNotFoundException {
       Scanner scanner = new Scanner(new FileInputStream(myFile));
       cityName = scanner.next();
        while (scanner.hasNext()){
            cityData newData = new cityData();
            newData.month = scanner.next();
            newData.year = Integer.parseInt(scanner.next());
            newData.rainFall = Float.parseFloat(scanner.next());
            data.add(newData);
        }
        scanner.close();
    }

    double averageRainFall(ArrayList<cityData> dates){
        double average = 0;
        for( cityData date: dates){
            average += date.rainFall;
        }
        average = average/dates.size();
        return average;
    }

    double averageMonthRainFall(ArrayList<cityData> dates, String month){
        ArrayList<cityData> tempDates = new ArrayList<cityData>();
        for(cityData date:dates){
            if (date.month.equals(month)){
                tempDates.add(date);
            }
        }
        return averageRainFall(tempDates);
    }

    //pushing the first 4 values then compairing the vectors to though four;
    double[] sortMonths(ArrayList<cityData> dates){
        double[] rainNumber;
        rainNumber = new double[240];
        for(int i = 0; i < 240; i++){
            rainNumber[i] = dates.get(i).rainFall;
        }
        return rainNumber;
    }

    cityData meanMonth(ArrayList<cityData> dates){
        double wantedRain = sortMonths(dates)[120];
        cityData wantedMonth = dates.get(0);
        for(int i = 0; i < 240; i++){
            if(wantedRain == dates.get(i).rainFall){
                wantedMonth = dates.get(i);
                return wantedMonth;
            }
        }
        return wantedMonth;
    }
}
