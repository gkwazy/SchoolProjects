package assignment02;

import java.util.ArrayList;
import java.util.GregorianCalendar;

/**
 * Testing class for LibraryGeneric.
 *
 */
public class LibraryGenericTest {

	public static void main(String[] args) {

		// test a library that uses names (String) to id patrons
		LibraryGeneric<String> lib1 = new LibraryGeneric<String>();
		lib1.add(9780374292799L, "Thomas L. Friedman", "The World is Flat");
		lib1.add(9780330351690L, "Jon Krakauer", "Into the Wild");
		lib1.add(9780446580342L, "David Baldacci", "Simple Genius");

		String patron1 = "Jane Doe";

		if (!lib1.checkout(9780330351690L, patron1, 1, 1, 2008))
			System.err.println("TEST FAILED: first checkout");
		if (!lib1.checkout(9780374292799L, patron1, 1, 1, 2009))
			System.err.println("TEST FAILED: second checkout");
		ArrayList<LibraryBookGeneric<String>> booksCheckedOut1 = lib1.lookup(patron1);

		if (booksCheckedOut1 == null || booksCheckedOut1.size() != 2
				|| !booksCheckedOut1.get(1).equals(new Book(9780330351690L, "Jon Krakauer", "Into the Wild"))
				|| !booksCheckedOut1.get(0).equals(new Book(9780374292799L, "Thomas L. Friedman", "The World is Flat"))
				|| !booksCheckedOut1.get(0).getHolder().equals(patron1)
				|| !booksCheckedOut1.get(0).getDueDate().equals(new GregorianCalendar(2009, 1, 1))
				|| !booksCheckedOut1.get(1).getHolder().equals(patron1)
				|| !booksCheckedOut1.get(1).getDueDate().equals(new GregorianCalendar(2008, 1, 1)))
			System.err.println("TEST FAILED: lookup(holder)");
		if (!lib1.checkin(patron1))
			System.err.println("TEST FAILED: checkin(holder)");

		// test a library that uses phone numbers (PhoneNumber) to id patrons
		LibraryGeneric<PhoneNumber> lib2 = new LibraryGeneric<PhoneNumber>();
		lib2.add(9780374292799L, "Thomas L. Friedman", "The World is Flat");
		lib2.add(9780330351690L, "Jon Krakauer", "Into the Wild");
		lib2.add(9780446580342L, "David Baldacci", "Simple Genius");

		PhoneNumber patron2 = new PhoneNumber("801.555.1234");

		if (!lib2.checkout(9780330351690L, patron2, 1, 1, 2008))
			System.err.println("TEST FAILED: first checkout");
		if (!lib2.checkout(9780374292799L, patron2, 1, 1, 2008))
			System.err.println("TEST FAILED: second checkout");
		ArrayList<LibraryBookGeneric<PhoneNumber>> booksCheckedOut2 = lib2.lookup(patron2);
		if (booksCheckedOut2 == null || booksCheckedOut2.size() != 2
				|| !booksCheckedOut2.get(1).equals(new Book(9780330351690L, "Jon Krakauer", "Into the Wild"))
				|| !booksCheckedOut2.get(0).equals(new Book(9780374292799L, "Thomas L. Friedman", "The World is Flat"))
				|| !booksCheckedOut2.get(0).getHolder().equals(patron2)
				|| !booksCheckedOut2.get(0).getDueDate().equals(new GregorianCalendar(2008, 1, 1))
				|| !booksCheckedOut2.get(1).getHolder().equals(patron2)
				|| !booksCheckedOut2.get(1).getDueDate().equals(new GregorianCalendar(2008, 1, 1)))
			System.err.println("TEST FAILED: lookup(holder)");
		if (!lib2.checkin(patron2))
			System.err.println("TEST FAILED: checkin(holder)");

		LibraryGeneric<String> lib3 = new LibraryGeneric<String>();
		lib3.add(9780374292799L, "Thomas L. Friedman", "The World is Flat");
		lib3.add(9780330351690L, "Jon Krakauer", "Into the Wild");
		lib3.add(9780446580342L, "David Baldacci", "Simple Genius");
		lib3.add(9780446580341L, "David Baldacci", "Zealous Genius");

		ArrayList<LibraryBookGeneric<String>> arrayLib3 = lib3.getOrderedByAuthor();

		if (lib3 == null || arrayLib3.size() != 4
				|| !arrayLib3.get(0).equals(new Book(9780446580342L, "David Baldacci", "Simple Genius"))
				|| !arrayLib3.get(1).equals(new Book(9780446580341L, "David Baldacci", "Zealous Genius"))
				|| !arrayLib3.get(2).equals(new Book(9780330351690L, "Jon Krakauer", "Into the Wild"))
				|| !arrayLib3.get(3).equals(new Book(9780374292799L, "Thomas L. Friedman", "The World is Flat"))) {
			System.err.println("TEST FAILED: sort by Author");
		}

		lib3.checkout(9780374292799L, patron1, 1, 1, 2008);
		lib3.checkout(9780446580341L, patron1, 1, 1, 2007);
		lib3.checkout(9780330351690L, patron1, 3, 3, 2008);
		ArrayList<LibraryBookGeneric<String>> arrayLibDate = lib3.getOverdueList(1, 1, 2008); 
		
		if (lib3 == null || arrayLibDate.size() != 2
				|| !arrayLibDate.get(0).equals(new Book(9780446580341L, "David Baldacci", "Zealous Genius"))
				|| !arrayLibDate.get(1).equals(new Book(9780374292799L, "Thomas L. Friedman", "The World is Flat"))) {
			System.err.println("TEST FAILED: sort by due date");
		}
			

		System.out.println("Testing done.");
	}
}
