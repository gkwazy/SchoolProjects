package assignment04;

import static org.junit.jupiter.api.Assertions.*;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.Random;

import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

class SortUtilTest {
	SortUtil<Integer> tools;
	static ArrayList<Integer> testArray, permArray;
	static int sizeOfArray;
	static Comparator<Integer> comparator;
	static Random random;

	@BeforeAll
	static void setUpBeforeClass() throws Exception {
		sizeOfArray = 100;
		comparator = Comparator.naturalOrder();
		random = new Random();
		testArray = new ArrayList<Integer>();
		permArray = new ArrayList<Integer>();

		for (int i = 0; i < sizeOfArray; i++) {
//			int randomNum = random.nextInt((sizeOfArray - 1) + 1) + 1;
//			testArray.add(randomNum);
			testArray.add(i);
		}
//		permArray = new ArrayList<>(testArray);
		System.out.println("start");
	}

	@AfterAll
	static void tearDownAfterClass() throws Exception {
	}

	@BeforeEach
	void setUp() throws Exception {
	}

	@AfterEach
	void tearDown() throws Exception {
	}

	@Test
	void hope() {
		for (int g = 0; g <= 12; g++) {
			testArray.clear();
			sizeOfArray = 5000 + g * 1500;
			permArray = new ArrayList<>();
			for (int i = 0; i <sizeOfArray/2 ; i++) {
				int randomNum = random.nextInt((sizeOfArray - 1) + 1) + 1;
				permArray.add(i);
			}
			for (int i = sizeOfArray/2; i > 0 ; i--) {
				int randomNum = random.nextInt((sizeOfArray - 1) + 1) + 1;
				permArray.add(i);
			}
			
			long startTime = System.nanoTime();
			
			for (int i = 0; i < 1000; i++) {
			testArray = new ArrayList<>();
			testArray.addAll(permArray);
//			SortUtil.insertionSort(comparator, testArray, 0, testArray.size());
			SortUtil.mergeSort(15, testArray, comparator);
			}
			long midtime = System.nanoTime();

			for (int i = 0; i < 1000; i++) {
			testArray = new ArrayList<>();
			testArray.addAll(permArray);
			}

			long stopTime = System.nanoTime();

			System.out.println((((midtime - startTime) - (stopTime - midtime)) / 1000));
		}
//				for(int i = 0; i< sizeOfArray; i++)
//					System.out.println(testArray.get(i));
		System.out.println("done: ");
//		SortUtil.mergeSort(0, testArray, comparator);
//		SortUtil.insertionSort(comparator, testArray, 0, testArray.size());
//		for (int i = 0; i < testArray.size(); i++) {
//			System.out.println(testArray.get(i));
//		}
	}

//	@Test
//	void insert() {
//		SortUtil.insertionSort(comparator, testArray,0,testArray.size());
//}		for (int i = 0; i < sizeOfArray; i++) {
//			System.out.println(testArray.get(i));
//		}
//		System.out.println("yep");
//	}
}
