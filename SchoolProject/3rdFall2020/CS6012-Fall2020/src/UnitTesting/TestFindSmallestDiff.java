package lab01;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

class TestFindSmallestDiff {
	private int[] arr1, arr2, arr3, arr4, arr5;

	@BeforeAll
	static void setUpBeforeClass() throws Exception {
	}

	@AfterAll
	static void tearDownAfterClass() throws Exception {
	}

	@BeforeEach
	void setUp() throws Exception {
		arr1 = new int[0];
		arr2 = new int[] { 3, 3, 3 };
		arr3 = new int[] { 52, 4, -8, 0, -17 };
		arr4 = new int[] { -17,-8,2,8,30,50,60};
		arr5 = new int[] {-10,0,-10,0,-10,0,-10,0};
	}

	@AfterEach
	void tearDown() throws Exception {
	}


	@Test
	public void emptyArray() {
		assertEquals(-1, DiffUtil.findSmallestDiff(arr1));
	}

	@Test
	public void allArrayElementsEqual() {
		assertEquals(0, DiffUtil.findSmallestDiff(arr2));
	}

	@Test
	public void smallRandomArrayElements() {
		assertEquals(4, DiffUtil.findSmallestDiff(arr3));
	}
	@Test
	public void orderedNumbersArrayElements() {
		assertEquals(6, DiffUtil.findSmallestDiff(arr4));
		
	}
	@Test
	public void arrayOf() {
		assertEquals(6, DiffUtil.findSmallestDiff(arr5));
		
	}

}
