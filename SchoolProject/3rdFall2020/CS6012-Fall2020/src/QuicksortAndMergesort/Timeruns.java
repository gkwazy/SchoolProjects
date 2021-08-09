package assignment04;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.Random;

public class Timeruns {

	SortUtil<Integer> tools;
	static ArrayList<Integer> testArray, permArray, switchArray;
	static int sizeOfArray;
	static Comparator<Integer> comparator;

	public static void main(String[] args) {
		long startTime, midpointTime, stopTime;

		sizeOfArray = 10000;
		comparator = Comparator.naturalOrder();
		testArray = new ArrayList<Integer>();
		Random random = new Random();
		switchArray = new ArrayList<Integer>();
		switchArray.add(0);
		switchArray.add(100);
		switchArray.add(500);
		switchArray.add(1000);
		switchArray.add(5000);
		switchArray.add(10000);
		switchArray.add(50000);
		switchArray.add(100000);
		switchArray.add(500000);
		switchArray.add(1000000);

		for (int k = 0; k < 1; k++) {
			sizeOfArray = sizeOfArray * 1;
			testArray.clear();
			for (int i = 0; i < sizeOfArray; i++) {
				int randomNum = random.nextInt((sizeOfArray - 1) + 1) + 1;
				testArray.add(randomNum);
			}
			permArray = new ArrayList<Integer>(testArray.size());

			for (int i = 0; i < testArray.size(); i++) {
				permArray.add(testArray.get(i));
			}
			System.out.println("Array: " + testArray.size());
			// First, spin computing stuff until one second has gone by.
			// This allows this thread to stabilize.

			startTime = System.nanoTime();
			while (System.nanoTime() - startTime < 1000000000) { // empty block
			}

			for (int l = 0; l < 1; l++) {
				System.out.println("switch:" + switchArray.get(l));
				if (switchArray.get(l) < testArray.get(testArray.size() - 1)) {
					for (int f = 0; f < testArray.size(); f++) {
						testArray.set(f,permArray.get(f));
					}
					// Now, run the test.

					long timesToLoop = 100;

					startTime = System.nanoTime();

					for (long i = 0; i < timesToLoop; i++) {
						System.out.println(i);
						System.out.println(testArray.size());
						SortUtil.mergeSort(40,testArray,comparator);
					}

					midpointTime = System.nanoTime();

					// Run an empty loop to capture the cost of running the loop.

					for (long i = 0; i < timesToLoop; i++) { // empty block
					}

					stopTime = System.nanoTime();

					// Compute the time, subtract the cost of running the loop
					// from the cost of running the loop and computing square roots.
					// Average it over the number of runs.

					long averageTime = ((midpointTime - startTime) - (stopTime - midpointTime)) / timesToLoop;

					System.out.println(
							testArray.size() + " " + switchArray.get(l) + " " + averageTime);
				}
			}
		}
		System.out.println("completed");
	}
}
