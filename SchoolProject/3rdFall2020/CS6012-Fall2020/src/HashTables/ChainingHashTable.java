package assignment06;

import java.util.Collection;
import java.util.LinkedList;

public class ChainingHashTable implements Set<String> {
	private LinkedList<String>[] storage;
	HashFunctor functor;
	int capacity;
	int size;
	public int collisions;

	@SuppressWarnings("unchecked")
	public ChainingHashTable(int capacity, HashFunctor functor) {
		this.storage = (LinkedList<String>[]) new LinkedList[capacity];
		fillTableArray(this.storage);
		this.functor = functor;
		this.capacity = capacity;
		this.size = 0;
		this.collisions = 0;

	}

	private void fillTableArray(LinkedList<String> newList[]) {
		for (int i = 0; i < capacity; i++) {
			newList[i] = new LinkedList<>();
			newList[i].add(null);
		}

	}

	/*
	 * This is how my table will be finding where to place the hash values.
	 */
	private int findHashLocation(int item) {
		
		return item % capacity;
	}

	private void growTable() {
		capacity *= 2;
		size = 0;
		LinkedList<String>[] tempArray = (LinkedList<String>[]) new LinkedList[capacity];
		for (int i = 0; i < storage.length; i++) {
			if (storage[i] != null) {
				for (int j = 0; j < storage[i].size(); j++) {
					addTemp(storage[i].get(j), tempArray);
				}
			}
		}
		storage = tempArray;
	}

	private boolean addTemp(String item, LinkedList<String>[] temp) {
		if (!containsTemp(item, temp)) {
			int position = findHashLocation(functor.hash(item));
			if (temp[position] == null) {
				LinkedList<String> startList = new LinkedList<>();
				temp[position] = startList;
				temp[position].add(item);
				size++;
				return true;
			} else {
				temp[position].add(item);
				collisions++;
				size++;
				;
				return true;
			}
		}
		return false;
	}

	public boolean containsTemp(String item, LinkedList<String>[] temp) {
		int position = findHashLocation(functor.hash(item));
		if (temp[position] == null) {
			return false;
		}
		for (int i = 0; i < temp[position].size(); i++) {
			if (temp[position].get(i) == item) {
				return true;
			}
		}
		return false;
	}

	@Override
	public boolean add(String item) {
		if (size == capacity) {
			growTable();
		} else if ((1 / (1 - (size / capacity))) > 5) {
			growTable();
		}
		if (!contains(item)) {
			int position = findHashLocation(functor.hash(item));
			if (storage[position] == null) {
				LinkedList<String> startList = new LinkedList<>();
				storage[position] = startList;
				storage[position].add(item);
				size++;
				return true;
			} else {
				storage[position].add(item);
				collisions++;
				size++;
				return true;
			}
		}
		return false;
	}

	@Override
	public boolean addAll(Collection<? extends String> items) {
		for (String word : items) {
			add(word);
		}
		return false;
	}

	/*
	 * makes a new list and sets storage to that list to create an empty list
	 */
	@SuppressWarnings("unchecked")
	@Override
	public void clear() {
		storage = (LinkedList<String>[]) new LinkedList[capacity];
		fillTableArray(storage);
	}

	@Override
	public boolean contains(String item) {
		int position = findHashLocation(functor.hash(item));
		if (storage[position] == null) {
			return false;
		}
		for (int i = 0; i < storage[position].size(); i++) {
			if (storage[position].get(i) == item) {
				return true;
			}
		}

		return false;
	}

	@Override
	public boolean containsAll(Collection<? extends String> items) {
		for (String word : items) {
			if (!contains(word)) {
				return false;
			}
		}
		return true;
	}

	@Override
	public boolean isEmpty() {
		for (int i = 0; i < capacity; i++) {
			if (storage[i] != null) {
				return false;
			}
		}
		return true;
	}

	@Override
	public boolean remove(String item) {
		int position = findHashLocation(functor.hash(item));
		if (storage[position] != null) {
			for (int i = 0; i < storage[position].size(); i++) {
				if (storage[position].get(i) == item) {
					storage[position].remove(i);
					if (storage[position].size() == 0) {
						storage[position] = null;
					}
					size--;
					return true;
				}
			}
		}
		return false;
	}

	@Override
	public boolean removeAll(Collection<? extends String> items) {
		boolean wasRemoved = false;
		for (String word : items) {
			remove(word);
			wasRemoved = true;
		}
		return wasRemoved;
	}

	@Override
	public int size() {
		return size;
	}

}
