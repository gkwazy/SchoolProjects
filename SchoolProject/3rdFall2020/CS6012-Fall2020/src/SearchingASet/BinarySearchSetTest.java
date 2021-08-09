package assignment03;

import static org.junit.jupiter.api.Assertions.*;

import java.net.CacheRequest;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.Collections;
import java.util.Iterator;
import java.util.List;

import org.junit.Assert;
import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

class BinarySearchSetTest {
	BinarySearchSet<Integer> numberArray;
	BinarySearchSet<String> stringArray;
	List<String> stringList;

	@BeforeEach
	void setUp() throws Exception {
		stringList = Arrays.asList(new String[] { "ab", "cd", "ef" });
		numberArray = new BinarySearchSet<>();
		stringArray = new BinarySearchSet<>();
		for (int i = 0; i < 4; i++) {
			numberArray.add(i);
		}
		for (int i = 6; i < 15; i++) {
			numberArray.add(i);
		}
		numberArray.add(5);
		numberArray.add(4);

	}

	@AfterEach
	void tearDown() throws Exception {
	}

	@Test
	void add() {
		stringArray.add("hi");
		stringArray.add("by");
		numberArray.add(5);
		int test00 = (numberArray.get(0)).intValue();
		int test13 = (numberArray.get(13)).intValue();
		int test05 = (numberArray.get(5)).intValue();
		String test = stringArray.get(1);
		Assert.assertEquals(0, test00);
		Assert.assertEquals(13, test13);
		Assert.assertEquals(5, test05);
		Assert.assertEquals("hi", test);
		Assert.assertEquals(15, numberArray.size());

	}

	@Test
	void addAll() {
		stringArray.addAll(stringList);
		Assert.assertEquals(true, stringArray.contains("cd"));
	}

	@Test
	void contains() {
		Assert.assertEquals(15, numberArray.size());
		Assert.assertEquals(true, numberArray.contains(14));
		Assert.assertEquals(false, numberArray.contains(16));
	}

	@Test
	void containsAll() {
		stringArray.add("ab");
		stringArray.add("cd");
		stringArray.add("ef");
		Assert.assertEquals(true, stringArray.containsAll(stringList));
	}

	@Test
	void firstAndLast() {
		int testFirst = numberArray.first();
		int testLast = numberArray.last();

		Assert.assertEquals(0, testFirst);
		Assert.assertEquals(14, testLast);
	}

	@Test
	void remove() {
		Integer testI5 = (numberArray.get(5));
		numberArray.remove(testI5);
		int test00 = (numberArray.get(0)).intValue();
		int test13 = (numberArray.get(13)).intValue();
		int test05 = (numberArray.get(5)).intValue();
		Assert.assertEquals(0, test00);
		Assert.assertEquals(6, test05);
		Assert.assertEquals(14, test13);
		Assert.assertEquals(14, numberArray.size());

	}

	@Test
	void removeAll() {
		stringArray.removeAll(stringList);
		String test = stringArray.get(1);
		Assert.assertEquals(0, stringArray.size());
		Assert.assertEquals(null, test);

	}

	@Test
	void Array() {
		stringArray.add("hi");
		stringArray.add("by");
		Object[] temp = stringArray.toArray();
		Assert.assertEquals("by", temp[0]);
	}

	@Test
	void iterator() {
		stringArray.add("hi");
		stringArray.add("by");
		stringArray.add("car");
		Iterator<String> it = stringArray.iterator();
		Assert.assertEquals("by", it.next());
		Assert.assertEquals("car", it.next());
		Assert.assertEquals("hi", it.next());
		

	}
}
