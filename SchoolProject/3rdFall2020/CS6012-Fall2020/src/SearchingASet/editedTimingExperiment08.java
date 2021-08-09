package assignment03;

public class editedTimingExperiment08 {
	//took the base of the TimingExperiment08 and edited it to fit my needs better

	public static void main(String[] args) {

		BinarySearchSet<Integer> numberArray;
		numberArray = new BinarySearchSet<>();
		long[] timeArray = new long[10000];
		double averageTime = 0;

		for (int i = 0; i < 1000000; i++) {
			numberArray.add(i);
		}

		long startTime, midpointTime, stopTime;
		
		long timesToLoop = 10000;
		int max = numberArray.size();
		// First, spin computing stuff until one second has gone by.
		// This allows this thread to stabilize.
		
		startTime = System.nanoTime();

		while (System.nanoTime() - startTime < 1000000000) { // empty block
		}

		// Now, run the test.

		for (long i = 0; i < timesToLoop; i++) {

			startTime = System.nanoTime();

			numberArray.add(max);
//    }
//    midpointTime = System.nanoTime();

			// Run an empty loop to capture the cost of running the loop.

//    for (long i = 0; i < timesToLoop; i++) { // empty block
//    }

			stopTime = System.nanoTime();

			// Compute the time, subtract the cost of running the loop
			// from the cost of running the loop and computing square roots.
			// Average it over the number of runs.
			
			timeArray[(int) i] = stopTime - startTime;

			numberArray.remove(max);
		}

		for (int i = 0; i < timesToLoop; i++) {
			averageTime += timeArray[i];
		}
		averageTime = averageTime / timesToLoop;

//    double averageTime = ((midpointTime - startTime) - (stopTime - midpointTime)) / timesToLoop;

		System.out.println(averageTime);
	}
}
