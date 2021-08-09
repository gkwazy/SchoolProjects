package lab05;

import java.util.Iterator;
import java.util.NoSuchElementException;

import assignment03.BinarySearchSet;

public class DoublyLinkedList<E> implements List<E>, Iterable<E> {
	private Node head;
	private Node tail;
	private Node nodeEle;
	private int size;

	private class Node {
		E data;
		Node next = null;
		Node prev = null;
	}

	public DoublyLinkedList() {

	}

	public DoublyLinkedList(E data) {
		Node tempNode = new Node();
		tempNode.data = data;
		nodeEle = tempNode;
		if (head == null) {
			head = tempNode;
			tail = tempNode;
			size++;
		}
	}

	@Override
	public Iterator<E> iterator() {
		Iterator<E> iterat = new Iterator<E>() {
			private int position;
			Node temp = head;

			@Override
			public boolean hasNext() {
				if (temp != null) {
					if (temp.next != null) {
						return true;
					}
				}
				return false;
			}

			@Override
			public E next() {
				if (position == 0) {
					position++;
					return head.data;
				}
				temp = head;
				for (int i = 0; i < position; i++) {
					temp = temp.next;
				}
				position++;
				return temp.data;
			}

			@Override
			public void remove() {
				temp.prev.next = temp.next;
				temp.next.prev = temp.prev;
			}
		};
		return iterat;
	}

	@Override
	public void addFirst(E element) {
		Node tempNode = new Node();
		tempNode.data = element;
		tempNode.next = head;
		if (head != null) {
			head.prev = tempNode;
		}
		head = tempNode;
		size++;

	}

	@Override
	public void addLast(E o) {
		Node tempNode = new Node();
		tempNode.data = o;
		tempNode.prev = tail;
		if (tail != null) {
			tail.next = tempNode;
		}
		tail = tempNode;
		size++;
		if (head == null) {
			head = tempNode;
		}

	}

	@Override
	public void add(int index, E element) throws IndexOutOfBoundsException {
		if (index >= size) {
			throw new IndexOutOfBoundsException();
		}
		Node tempNode = head;
		for (int i = 0; i < index; i++) {
			tempNode = tempNode.next;
		}
		Node newNode = new Node();
		newNode.data = element;
		newNode.prev = tempNode.prev;
		tempNode.prev.next = newNode;
		tempNode.prev = newNode;
		newNode.next = tempNode;
		size++;
	}

	@Override
	public E getFirst() throws NoSuchElementException {
		if (head == null) {
			throw new NoSuchElementException();
		}
		return head.data;
	}

	@Override
	public E getLast() throws NoSuchElementException {
		if (head == null) {
			throw new NoSuchElementException();
		}
		return tail.data;
	}

	@Override
	public E get(int index) throws IndexOutOfBoundsException {
		if (index >= size) {
			throw new IndexOutOfBoundsException();
		}
		Node tempNode = head;
		for (int i = 0; i < index; i++) {
			tempNode = tempNode.next;
		}
		return tempNode.data;
	}

	@Override
	public E removeFirst() throws NoSuchElementException {
		if (head == null) {
			throw new NoSuchElementException();
		}
		E temp = head.data;
		head.next.prev = null;
		head = head.next;
		return temp;
	}

	@Override
	public E removeLast() throws NoSuchElementException {
		if (head == null || tail == null) {
			throw new NoSuchElementException();
		}
		E temp = tail.data;
		tail.prev.next = null;
		tail = tail.prev;
		return temp;
	}

	@Override
	public E remove(int index) throws IndexOutOfBoundsException {
		if (index >= size) {
			throw new IndexOutOfBoundsException();
		}
		Node tempNode = head;
		for (int i = 0; i < index; i++) {
			tempNode = tempNode.next;
		}

		tempNode.prev.next = tempNode.next;
		tempNode.next.prev = tempNode.prev;

		return tempNode.data;
	}

	@Override
	public int indexOf(E element) {
		Node tempNode = head;

		for (int i = 0; i < size; i++) {
			if (tempNode.data == element) {
				return i;
			}
			tempNode = tempNode.next;

		}
		return -1;
	}

	@Override
	public int lastIndexOf(E element) {
		Node tempNode = head;
		int last = -1;
		for (int i = 0; i < size; i++) {
			if (tempNode.data == element) {
				last = i;
			}
			tempNode = tempNode.next;

		}
		return -1;
	}

	@Override
	public int size() {
		return size;
	}

	@Override
	public boolean isEmpty() {
		return (head==null);
	}

	@Override
	public void clear() {
		for(int i = 0; i< size; i++) {
			remove(i);
		}
	}

	@Override
	public Object[] toArray() {
		Object[] temp = new Object[size];
		for(int i = 0; i< size; i++) {
			temp[i] = get(i);
		}
		return temp;
	}

}
