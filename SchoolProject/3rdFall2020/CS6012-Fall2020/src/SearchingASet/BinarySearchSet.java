package assignment03;

import java.util.Collection;
import java.util.Comparator;
import java.util.Iterator;
import java.util.NoSuchElementException;

public class BinarySearchSet<E> implements SortedSet<E>, Iterable<E> {
	private E[] array;
	private int capacity;
	private int size;
	Comparator<? super E> comparator;

	@SuppressWarnings("unchecked")
	public BinarySearchSet() {
		// TODO If this constructor is used to create the sorted set,
//		it is assumed that the elements are ordered using their natural
//		ordering (i.e., E implements Comparable<? super E>).
		this.array = (E[]) new Object[10];
		this.capacity = 10;
		this.size = 0;
		comparator = (Comparator<? super E>) Comparator.naturalOrder();

	}

	public BinarySearchSet(Comparator<? super E> comparator) {
//		If this constructor is used to create the sorted set,
//		it is assumed that the elements are ordered using the provided comparator.
		this.array = (E[]) new Object[10];
		this.capacity = 10;
		this.size = 0;
		this.comparator = comparator;
	}

	public E get(int position) {
		return array[position];
	}

	/*
	 * This method will loop through the array and look for the position that i
	 * element should be added. if the element is already in the array it will
	 * return a -1.
	 */
	private int lookForPosition(E wanted) {
		if (array[0] == null) {
			return 0;
		}
		if (comparator.compare(wanted, array[0]) < 0) {
			return 0;
		} else {
			for (int i = 0; i < size; i++) {
				if (comparator.compare(wanted, array[i]) == 0) {
					return -1;

				} else if (comparator.compare(wanted, array[i]) < 0) {
					return i;
				}
			}
			return size;
		}
	}

	@Override
	public Comparator<? super E> comparator() {
		return null;
	}

	/*
	 * looks at the first element of the array and returns the values or returns
	 * null of the values is null
	 */
	@Override
	public E first() throws NoSuchElementException {
		if (array[0] != null) {
			return array[0];
		}
		return null;
	}

	/*
	 * looks at the last element of the array and returns the value or returns null
	 * of the array is empty.
	 */
	@Override
	public E last() throws NoSuchElementException {
		if (array[0] != null) {
			return array[size - 1];
		}
		return null;
	}

	@Override
	public boolean add(E element) {
		int position = lookForPosition(element);
		if (position != -1) {

			if ((size + 1 >= capacity)) {
				this.capacity = capacity * 2;
				E[] temp = (E[]) new Object[capacity];
				for (int i = 0; i < array.length; i++) {
					temp[i] = array[i];
				}
				;
				array = temp;
			}
			for (int i = size; i > position; i--) {
				array[i] = array[i - 1];
			}
			array[position] = element;
			size++;
			return true;

		}
		return false;
	}

	@Override
	public boolean addAll(Collection<? extends E> elements) {
		try {
			for (Iterator i = elements.iterator(); i.hasNext();)
				add((E) i.next());
		} catch (Exception e) {
			return false;
		}
		return true;

	}

	@Override
	public void clear() {
		for (int i = 0; i < capacity; i++) {
			array[i] = null;
		}
		size = 0;
	}

	@SuppressWarnings("unchecked")
	@Override
	public boolean contains(Object element) {
		if (lookForPosition((E) element) == -1) {
			return true;
		}
		return false;
	}

	@Override
	public boolean containsAll(Collection<?> elements) {
		boolean containItem = true;
		for (Iterator i = elements.iterator(); i.hasNext();) {
			containItem = contains(i.next());
			if (!containItem) {
				return false;
			}
		}
		return true;
	}

	@Override
	public boolean isEmpty() {
		if (size == 0) {
			return true;
		}
		return false;
	}

	@Override
	public Iterator<E> iterator() {
		Iterator<E> iterat = new Iterator<E>() {

            private int position = 0;

            @Override
            public boolean hasNext() {
                return position < size && array[position] != null;
            }

            @Override
            public E next() {
            	
                return array[position++];
            }

            @Override
            public void remove() {
                BinarySearchSet.this.remove(array[position]);
            }
        };
        return iterat;
	}

	@Override
	public boolean remove(Object element) {
			for(int i = 0; i<size;i++) {
				if (comparator.compare((E)element, array[i]) == 0) {
					for(int j = i; j<size;j++) {
						array[j] = array[j+1];
					}
					array[size] = null;
					size--;
					return true;
				}
			}
			return false;
	}

	@Override
	public boolean removeAll(Collection<?> elements) {
		boolean found = false;
		for (Iterator i = elements.iterator(); i.hasNext();) {
			if(remove(i.next())) {
				found = true;
			}
			
		}
				
		return found;
	}

	@Override
	public int size() {
		return this.size;
	}

	@Override
	public Object[] toArray() {
		E[] temp = (E[]) new Object[size];
		for(int i = 0; i<size;i++) {
			temp[i] = array[i];
		}
		return temp;
	}

}
