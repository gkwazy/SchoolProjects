package assignment06;

import static org.junit.jupiter.api.Assertions.*;

import java.util.ArrayList;

import org.junit.Assert;
import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

class ChainingHashTableTest {
	GoodHashFunctor badHash = new GoodHashFunctor();
	ChainingHashTable badChain = new ChainingHashTable(2, badHash);
	ArrayList<String> wordList = new ArrayList<String>();

	@BeforeAll
	static void setUpBeforeClass() throws Exception {
		
	}

	@AfterAll
	static void tearDownAfterClass() throws Exception {
	}

	@BeforeEach
	void setUp() throws Exception {
		wordList.add("nope");
		wordList.add("yes");
		wordList.add("yes");
		wordList.add("yellow");
		badChain.addAll(wordList);
		
	}

	@AfterEach
	void tearDown() throws Exception {
	}

	@Test
	void contains() {
		Assert.assertEquals(false, badChain.contains("garret"));
		Assert.assertEquals(true, badChain.contains("yes"));
		Assert.assertEquals(true, badChain.containsAll(wordList));
		wordList.add("monkey");
		Assert.assertEquals(false, badChain.contains("monkey"));
		Assert.assertEquals(false, badChain.containsAll(wordList));
	}
	
	@Test
	void remove() {
		badChain.remove("yellow");
		Assert.assertEquals(true, badChain.contains("yes"));
		Assert.assertEquals(false, badChain.contains("yellow"));
		badChain.add("yellow");
		Assert.assertEquals(true, badChain.contains("yellow"));
		badChain.removeAll(wordList);
		Assert.assertEquals(false, badChain.contains("yellow"));
		
	}

}
