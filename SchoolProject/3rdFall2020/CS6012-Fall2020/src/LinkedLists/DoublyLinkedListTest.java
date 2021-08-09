package lab05;

import static org.junit.jupiter.api.Assertions.*;

import java.util.Iterator;
import java.util.NoSuchElementException;

import org.junit.Assert;
import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

class DoublyLinkedListTest {

	DoublyLinkedList<Integer> testArray = new DoublyLinkedList<>();

	@BeforeEach
	void setUp() throws Exception {
	}

	@AfterEach
	void tearDown() throws Exception {
	}

	@Test
	void addFirst() {
		Assert.assertThrows(NoSuchElementException.class,()->testArray.getFirst());
		testArray.addFirst(1);
		int test01 = testArray.getFirst();
		testArray.addFirst(2);
		int test02 = testArray.getFirst();
		testArray.addFirst(3);
		int test03 = testArray.getFirst();
		testArray.addFirst(4);
		int test04 = testArray.getFirst();
		Assert.assertEquals(4,test04);
		Assert.assertEquals(3,test03);
		Assert.assertEquals(2,test02);
		Assert.assertEquals(1,test01);
	}
	
	@Test
	void addLast() {
		Assert.assertThrows(NoSuchElementException.class,()->testArray.getLast());
		testArray.addLast(1);
		int test01 = testArray.getLast();
		testArray.addLast(2);
		int test02 = testArray.getLast();
		testArray.addLast(3);
		int test03 = testArray.getLast();
		testArray.addLast(4);
		int test04 = testArray.getLast();
		Assert.assertEquals(4,test04);
		Assert.assertEquals(3,test03);
		Assert.assertEquals(2,test02);
		Assert.assertEquals(1,test01);	
	}
	
	@Test
	void add() {
		testArray.addLast(1);
		testArray.addLast(2);
		testArray.addLast(3);
		testArray.addLast(4);
		testArray.add(2, 5);
		Iterator it = testArray.iterator();
		Assert.assertEquals(1,it.next());
		Assert.assertEquals(2,it.next());
		Assert.assertEquals(5,it.next());
		Assert.assertEquals(3,it.next());
		Assert.assertEquals(4,it.next());
		Assert.assertThrows(IndexOutOfBoundsException.class,()->testArray.add(20,20));
		
	}
	
	@Test
	void get() {
		Assert.assertThrows(IndexOutOfBoundsException.class,()->testArray.get(20));
		testArray.addLast(1);
		testArray.addLast(2);
		testArray.addLast(3);
		testArray.addLast(4);
		int test01 = testArray.get(0);
		int test04 = testArray.get(3);
		Assert.assertEquals(1,test01);
		Assert.assertEquals(4,test04);
	}
	
	@Test
	void removeFirst() {
		Assert.assertThrows(NoSuchElementException.class,()->testArray.removeFirst());
		testArray.addLast(1);
		testArray.addLast(2);
		testArray.addLast(3);
		testArray.addLast(4);
		int test01 = testArray.get(0);
		Assert.assertEquals(1,test01);
		int test00 = testArray.removeFirst();
		test01 = testArray.getFirst();
		Assert.assertEquals(1,test00);
		Assert.assertEquals(2,test01);
		
		
	}
	@Test
	void removeLast() {
		Assert.assertThrows(NoSuchElementException.class,()->testArray.removeLast());
		testArray.addLast(1);
		testArray.addLast(2);
		testArray.addLast(3);
		testArray.addLast(4);
		int test01 = testArray.get(0);
		Assert.assertEquals(1,test01);
		int test00 = testArray.removeLast();
		test01 = testArray.getLast();
		Assert.assertEquals(4,test00);
		Assert.assertEquals(3,test01);
	}
	
	@Test
	void iterator() {
		Iterator<Integer> iterator = testArray.iterator();
		testArray.addLast(1);
		testArray.addLast(2);
		testArray.addLast(3);
		testArray.addLast(4);
		
		while(iterator.hasNext()) {
			
			if(iterator.next() == 3) {
				iterator.remove(); 
			}
		}
		int test01 = testArray.get(3);
		Assert.assertEquals(4,test01);
		
	}

	@Test
	void indexOf() {
		testArray.addLast(1);
		testArray.addLast(2);
		testArray.addLast(3);
		testArray.addLast(4);
		int test01 = testArray.indexOf(3);
		Assert.assertEquals(2,test01);
	}

}
