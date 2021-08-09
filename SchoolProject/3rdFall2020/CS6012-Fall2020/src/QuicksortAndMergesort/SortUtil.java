package assignment04;

import java.util.ArrayList;
import java.util.Comparator;

public class SortUtil<T> {

	public SortUtil() {
	}

	static int breakoff;

	public static <T> void mergeSort(int switchPoint, ArrayList<T> list, Comparator<? super T> comparator) {
		breakoff = switchPoint;

		ArrayList<T> temp = new ArrayList<>();
		for (int i = 0; i < list.size(); i++) {
			temp.add(null);
		}
		int size = (list.size() - 1);

		mergeBreakDown(comparator, list, temp, 0, size);

	}

	private static <T> void mergeBreakDown(Comparator<? super T> comparator, ArrayList<T> list, ArrayList<T> temp,
			int left, int right) {
		
		if (right - left <= breakoff) {
			insertionSort(comparator, list, left, right);

		} else {
		if(left>=right)
			return;
		
			int middle = (left + right) / 2;
			mergeBreakDown(comparator, list, temp, left, middle);
			mergeBreakDown(comparator, list, temp, middle + 1, right);
			merge(comparator, list, temp, left, right);
			}
			
		}
			
	

	private static <T> void merge(Comparator<? super T> comparator, ArrayList<T> list, ArrayList<T> temp, int left,
			int right) {

		int l = left;
		int m = (left + right) / 2;
		int r = m + 1;
		int t = left;
//loop though and merge the arrays
		while (l <= m && r <= right) {
			if (comparator.compare(list.get(l), list.get(r)) <= 0) {
				temp.set(t, list.get(l));
				l++;
			} else {
				temp.set(t, list.get(r));
				r++;
			}
			t++;
		}
// if right side is less then left, finishes left
		while (l <= m) {
			temp.set(t, list.get(l));
			l++;
			t++;
		}
//if left side if less then right, finishes right
		while (r <= right) {
			temp.set(t, list.get(r));
			r++;
			t++;
		}

		for (int i = left; i <= right; i++) {
			list.set(i, temp.get(i));
		}
	}

	public static <T> void insertionSort(Comparator<? super T> comparator, ArrayList<T> list, int left, int right) {
		
			for (int j = left + 1; j < right; j++) {
				T position = list.get(j);
				int i = j - 1;
				while (i > left - 1 && (comparator.compare(list.get(i), position) > 0)) {
					list.set(i + 1, list.get(i));
					i--;
				}
				list.set(i + 1, position);
			}
	}
}
