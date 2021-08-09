package assignment06;

public class MediocreHashFunctor implements HashFunctor{
	@Override
	public int hash(String item) {
		int sum = 0, letter = 0;
		for(int i  = 0; i < item.length(); i++) {
			letter = item.charAt(i);
			sum += letter;
		}
				return sum;
	}
}
