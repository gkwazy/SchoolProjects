package assignment02;

import java.util.ArrayList;
import java.util.GregorianCalendar;

public class LibraryBookGeneric<Type> extends Book {
	Type holder;
	GregorianCalendar dueDate;

	public LibraryBookGeneric(long isbn, String author, String title) {
		super(isbn, author, title);
		holder = null;
		dueDate = null;

	}

	public Type getHolder() {
		return holder;

	}

	public GregorianCalendar getDueDate() {
		return dueDate;

	}

	public void checkBookIn() {
		this.holder = null;
		this.dueDate = null;
	}

	public void checkBookOut(GregorianCalendar dueDate, Type holder) {
		this.holder = holder;
		this.dueDate = dueDate;
	}	
	
	@Override
	public boolean equals(Book other) {
		boolean ISBNCheck = (this.getIsbn() == other.getIsbn());
		boolean authorCheck = (this.getAuthor() == other.getAuthor());
		boolean titleCheck = (this.getTitle() == other.getTitle());
		if (ISBNCheck == true && authorCheck == true && titleCheck == true) {
			return true;
		} else {
			return false;
		}
	}
	
	@Override
	public int hashCode() {
		return (int) isbn + author.hashCode() + title.hashCode();
	}
	
}