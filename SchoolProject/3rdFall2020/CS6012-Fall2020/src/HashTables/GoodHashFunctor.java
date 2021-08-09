package assignment06;

public class GoodHashFunctor implements HashFunctor {

	@Override
	public int hash(String item) {
		int sum = 0; 
		int letter = 0;
		for(int i  = 0; i < item.length(); i++) {
			letter = item.charAt(i) + 31*i;
			sum += letter;
		}
				return sum;
		
	}

}
