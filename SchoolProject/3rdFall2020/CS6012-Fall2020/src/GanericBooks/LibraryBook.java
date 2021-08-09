package assignment02;

import java.util.GregorianCalendar;

public class LibraryBook extends Book {
	String holder;
	GregorianCalendar dueDate;

	public LibraryBook(long isbn, String author, String title) {
		super(isbn, author, title);
		holder = null;
		dueDate = null;
		
	}
	
	public String getHolder() {
		return holder;
		
	}
	
	public GregorianCalendar getDueDate() {
		return dueDate;
		
	}
	
	public void checkBookIn(){
		this.holder = null;
		this.dueDate = null;
	}
	
	public void checkBookOut(GregorianCalendar dueDate, String holder) {
		this.holder = holder;
		this.dueDate = dueDate;
	}

	
}
