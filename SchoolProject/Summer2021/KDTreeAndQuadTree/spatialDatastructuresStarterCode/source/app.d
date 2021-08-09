import std.stdio;

import common;
import dumbknn;
import bucketknn;
import quadtree;
import kdtree;
import std. csv;
import std.file;

//import your files here

void main()
{
    File Kfile = File("KDiff", "w");
    File Nfile = File("NDiff", "w");
    File Dfile = File("DDiff", "w");
    int testK = 10;
    int testN = 1000;


    // //because dim is a "compile time parameter" we have to use "static foreach"
    // //to loop through all the dimensions we want to test.
    // //the {{ are necessary because this block basically gets copy/pasted with
    // //dim filled in with 1, 2, 3, ... 7.  The second set of { lets us reuse
    // //variable names.

    Dfile.writeln("Dim,SortMethod,Time")
    writeln("dumbKNN results");
    static foreach (dim; 1 .. 8)
    {
        {
            //get points of the appropriate dimension
            auto trainingPoints = getGaussianPoints!dim(1000);
            auto testingPoints = getUniformPoints!dim(100);
            auto kd = DumbKNN!dim(trainingPoints);
            writeln("tree of dimension ", dim, " built");
            auto sw = StopWatch(AutoStart.no);
            sw.start; //start my stopwatch
            foreach (const ref qp; testingPoints)
            {
                kd.knnQuery(qp, 10);
            }
            sw.stop;
            auto qt =  (sw.peek.total!"usecs");
            Dfile.writeln(dim,",","DumbTree",",",qt);
        }
    }

    writeln("BucketKNN results");
    //Same tests for the BucketKNN
    static foreach (dim; 1 .. 8)
    {
        {
            //get points of the appropriate dimension
            enum numTrainingPoints = 1000;
            auto trainingPoints = getGaussianPoints!dim(numTrainingPoints);
            auto testingPoints = getUniformPoints!dim(100);
            auto kd = BucketKNN!dim(trainingPoints, cast(int) pow(numTrainingPoints / 64, 1.0 / dim)); //rough estimate to get 64 points per cell on average
            writeln("tree of dimension ", dim, " built");
            auto sw = StopWatch(AutoStart.no);
            sw.start; //start my stopwatch
            foreach (const ref qp; testingPoints)
            {
                kd.knnQuery(qp, 10);
            }
            sw.stop;
            auto qt =  (sw.peek.total!"usecs");
            Dfile.writeln(dim,",","BucketTree",",",qt);
        }
    }

    // writeln("QuardTreeKNN results");
    // //Same tests for the QuadTreeKNN
    // {
    //     //get points of the appropriate dimension
    //     //get points of the appropriate dimension
    //     auto trainingPoints = getGaussianPoints!2(1000);
    //     auto testingPoints = getUniformPoints!2(100);
    //     auto qt = QuadTreeKNN(trainingPoints);
    //     writeln("Quadtree of dimension 2 built");
    //     auto sw = StopWatch(AutoStart.no);
    //     sw.start; //start my stopwatch
    //     foreach (const ref qp; testingPoints)
    //     {
    //         qt.knnQuery(qp, 10);
    //     }
    //     sw.stop;
    //     file.writeln(sw.peek.total!"usecs"); //output the time elapsed in microseconds
    //     //NOTE, I SOMETIMES GOT TOTALLY BOGUS TIMES WHEN TESTING WITH DMD
    //     //WHEN YOU TEST WITH LDC, YOU SHOULD GET ACCURATE TIMING INFO...
    // }

    writeln("KDTreeKNN results");

    static foreach (dim; 1 .. 8)
    {
        {
            //get points of the appropriate dimension
            auto trainingPoints = getGaussianPoints!dim(1000);
            auto testingPoints = getUniformPoints!dim(100);
            auto kd = KdTreeKNN!dim(trainingPoints);
            writeln("KDtree of dimension ", dim, " built");
            auto sw = StopWatch(AutoStart.no);
            sw.start; //start my stopwatch
            foreach (const ref qp; testingPoints)
            {
                kd.knnQuery(qp, 10);
            }
            sw.stop;
            auto qt =  (sw.peek.total!"usecs");
            Dfile.writeln(dim,",","KDTree",",",qt);
        }
    }

    long DumbKNNRun(int k,int NumPoint){
        long [] data;
        auto trainingPoints = getGaussianPoints!2(NumPoint);
        auto testingPoints = getUniformPoints!2(100);
        auto kd = DumbKNN!2(trainingPoints);
        auto sw = StopWatch(AutoStart.no);
        for(int i = 0; i < 5; i++){
            sw.start; //start my stopwatch  
            foreach (const ref qp; testingPoints)
            {
                kd.knnQuery(qp, 10);
            }
            sw.stop;
            data~=(sw.peek.total!"usecs");
        }
        long total;
            foreach (num; data)
        {
            total+= num;
        }
        total = total/data.length;
        return total;    
    }

    long BucketKNNRun(int k, int NumPoint){
        long[] data;
        auto numTrainingPoints = NumPoint;
        auto trainingPoints = getGaussianPoints!2(numTrainingPoints);
        auto testingPoints = getUniformPoints!2(100);
        auto kd = BucketKNN!2(trainingPoints, cast(int) pow(numTrainingPoints / 64, 1.0 / 2)); //rough estimate to get 64 points per cell on average
        auto sw = StopWatch(AutoStart.no);
        for(int i = 0; i < 5; i++){
            sw.start; //start my stopwatch
            foreach (const ref qp; testingPoints)
            {
                kd.knnQuery(qp, k);
            }
            sw.stop;
            data ~= (sw.peek.total!"usecs");
        } 
        long total;
        foreach (num; data)
        {
            total+= num;
        }
        total = total/data.length;
        return total;
    }

    long QTKNNRun(int k, int n){
        long[] data;

        auto trainingPoints = getGaussianPoints!2(n);
        auto testingPoints = getUniformPoints!2(100);
        auto qt = QuadTreeKNN(trainingPoints);
        auto sw = StopWatch(AutoStart.no);
        for(int i = 0; i < 5; i++){
            sw.start; //start my stopwatch
            foreach (const ref qp; testingPoints)
            {
                qt.knnQuery(qp, k);
            }
            sw.stop;
            data ~= (sw.peek.total!"usecs"); 
        }
        long total;
        foreach (num; data)
        {
            total+= num;
        }
        total = total/data.length;
        return total;
    }

    long KDKNNRun(int k, int n){
        long[] data;
        auto trainingPoints = getGaussianPoints!2(n);
        auto testingPoints = getUniformPoints!2(100);
        auto kd = KdTreeKNN!2(trainingPoints);
        auto sw = StopWatch(AutoStart.no);
        for(int i = 0; i < 5; i++){
            sw.start; //start my stopwatch
            foreach (const ref qp; testingPoints)
            {
                kd.knnQuery(qp, k);
            }
            sw.stop;
            data ~=(sw.peek.total!"usecs");
        }

        long total;
        foreach (num; data)
        {
            total += num;
        }
        total = total/data.length;
        return total;
    }

    // //run my test;
    Kfile.writeln("kvalue,SortMethod,Time");
    for(int k = 1; k <= 20; k++){
            writeln("testing K: ",k);
            testK = k;
            testN = 1000;
            long dum = DumbKNNRun(testK, testN);
            long buk = BucketKNNRun(testK, testN);
            long qt = QTKNNRun(testK, testN);
            long kd = KDKNNRun(testK, testN);
            Kfile.writeln(testK,",","KDTree",",",kd);
            Kfile.writeln(testK,",","QuadTree",",",qt);
            Kfile.writeln(testK,",","DumbTree",",",dum);
            Kfile.writeln(testK,",","BucketTree",",",buk);
    }

    Nfile.writeln("Nvalue,SortMethod,Time");
    for(int n = 1000; n <= 20000 ; n = n+1000){
            writeln("testing N: ",n);
            testK = 10;
            testN = n;
            long dum = DumbKNNRun(testK, testN);
            long buk = BucketKNNRun(testK, testN);
            long qt = QTKNNRun(testK, testN);
            long kd = KDKNNRun(testK, testN);
            Nfile.writeln(testN,",","KDTree",",",kd);
            Nfile.writeln(testN,",","QuadTree",",",qt);
            Nfile.writeln(testN,",","DumbTree",",",dum);
            Nfile.writeln(testN,",","BucketTree",",",buk);
    }


}
