package lab01;

public class DiffUtil {

	public static void main(String[] args) {
		// TODO Auto-generated method stub

	}

	public static int findSmallestDiff(int[] a) {
		if (a.length < 2) {
			return -1;
		}
//		52, 4, -8, 0, -17 
		int diff = a[0] - a[1];
		diff = Math.abs(diff);

		for (int i = 0; i < a.length; i++) {
			for (int j = i + 1; j < a.length; j++) {
				int tmp_diff = a[i] - a[j];
				tmp_diff = Math.abs(tmp_diff);

				if (tmp_diff < diff)
					diff = tmp_diff;
			}
		}

		return diff;
	}

}
