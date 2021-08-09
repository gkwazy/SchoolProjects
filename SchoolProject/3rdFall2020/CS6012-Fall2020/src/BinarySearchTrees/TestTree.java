package assignment05;

import static org.junit.jupiter.api.Assertions.*;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.NoSuchElementException;

import org.junit.Assert;
import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

class TestTree {
	static Comparator<Integer> comparator;
	BinarySearchTree<String> testTree;
	ArrayList<String> wordArray, nullArray;

	@BeforeAll
	static void setUpBeforeClass() throws Exception {
	}

	@AfterAll
	static void tearDownAfterClass() throws Exception {
	}

	@BeforeEach
	void setUp() throws Exception {
		comparator = Comparator.naturalOrder();
		testTree = new BinarySearchTree<>();
		wordArray = new ArrayList<>();
		nullArray = new ArrayList<>();

		wordArray.add("hello");
		wordArray.add("me");
		wordArray.add("garret");
		wordArray.add("garret");
		wordArray.add("bee");
		wordArray.add("mac");
		wordArray.add("hello");
		wordArray.add("cat");
		wordArray.add("apple");
		wordArray.add("yes");
		wordArray.add("phone");
		wordArray.add("zoo");
		wordArray.add("ouch");
		wordArray.add("quit");
		wordArray.add("zoom");

		nullArray.add("yo");
		nullArray.add(null);
		nullArray.add("ouch");
	}

	@AfterEach
	void tearDown() throws Exception {
	}

	@Test
	void printTree() {
		testTree.addAll(wordArray);
		testTree.writeDot("testTree.dot");
		System.out.println("printed");
	}

//	@Test
//	void add() {
//		testTree.add("hello");
//		testTree.add("me");
//		testTree.add("garret");
//		testTree.add("garret");
//		testTree.add("bee");
//		testTree.add("mac");
//		testTree.add("hello");
//		testTree.add("cat");
//		testTree.add("apple");
//		testTree.add("yes");
//
//		String testHello = testTree.rootNode.data;
//		String testBee = testTree.rootNode.left.left.data;
//		String testgar2 = testTree.rootNode.left.right.data;
//		String testYes = testTree.rootNode.right.right.data;
//		Assert.assertEquals("hello", testHello);
//		Assert.assertEquals("bee", testBee);
//		Assert.assertEquals("garret", testgar2);
//		Assert.assertEquals("yes", testYes);
//		Assert.assertThrows(NullPointerException.class, () -> testTree.add(null));
//	}
//
//	@Test
//	void addAll() {
//		testTree.addAll(wordArray);
//		String testHello = testTree.rootNode.data;
//		String testBee = testTree.rootNode.left.left.data;
//		String testgar2 = testTree.rootNode.left.right.data;
//		String testYes = testTree.rootNode.right.right.data;
//		Assert.assertEquals("hello", testHello);
//		Assert.assertEquals("bee", testBee);
//		Assert.assertEquals("garret", testgar2);
//		Assert.assertEquals("yes", testYes);
//		Assert.assertThrows(NullPointerException.class, () -> testTree.addAll(nullArray));
//	}
//
//	@Test
//	void clear() {
//		testTree.addAll(wordArray);
//		testTree.clear();
//		Assert.assertEquals(null, testTree.rootNode);
//	}

	@Test
	void contains() {
		testTree.addAll(wordArray);
		Assert.assertEquals(true, testTree.contains("garret"));
		Assert.assertEquals(true, testTree.contains("me"));
		Assert.assertEquals(false, testTree.contains("monkey"));
		Assert.assertEquals(false, testTree.contains("all"));
		testTree.add("monkey");
		Assert.assertEquals(true, testTree.contains("monkey"));
		Assert.assertThrows(NullPointerException.class, () -> testTree.contains(null));
	}

	@Test
	void containsAll() {
		testTree.addAll(wordArray);
		Assert.assertEquals(true, testTree.containsAll(wordArray));
		testTree.clear();
		testTree.add("ouch");
		testTree.add("elderberry");
		Assert.assertEquals(false, testTree.containsAll(wordArray));
		Assert.assertThrows(NullPointerException.class, () -> testTree.containsAll(nullArray));

	}

	@Test
	void first() {
		testTree.addAll(wordArray);
		Assert.assertEquals("apple", testTree.first());
	}

	@Test
	void last() {
		testTree.addAll(wordArray);
		Assert.assertEquals("zoom", testTree.last());
	}

	@Test
	void toArray() {
		testTree.addAll(wordArray);
		ArrayList<String> tempList = new ArrayList<String>();
		String[] sortedList = new String[] { "apple", "bee", "cat", "garret", "garret", "hello", "hello", "mac", "me",
				 "ouch","phone","quit","yes","zoo","zoom" };
		tempList = testTree.toArrayList();
		for (int i = 0; i < testTree.size(); i++) {
			Assert.assertEquals(sortedList[i], tempList.get(i));
		}
	}
	
	@Test
	void remove() {
		testTree.addAll(wordArray);
//		testTree.remove("mac");
//		Assert.assertEquals(false,testTree.contains("mac"));
		testTree.remove("hello");
		ArrayList<String> tempList = new ArrayList<String>();
		tempList = testTree.toArrayList();
		for (int i = 0; i < testTree.size(); i++) {
			System.out.println(tempList.get(i));
		}
//		Assert.assertEquals(false,testTree.contains("yes"));

		testTree.writeDot("testTree.dot");
		
	}
}
