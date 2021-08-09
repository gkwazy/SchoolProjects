package assignment06;

public class BadHashFunctor implements HashFunctor {

	@Override
	public int hash(String item) {
	 int hashNumber = item.charAt(1);
		return hashNumber;
	}

}
