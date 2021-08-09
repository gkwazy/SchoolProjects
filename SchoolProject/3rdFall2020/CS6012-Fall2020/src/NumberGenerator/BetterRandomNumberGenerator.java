package lab06;

public class BetterRandomNumberGenerator implements RandomNumberGenerator {
	long seed;
	boolean seedSet = false;
	long const1;
	long const2;

	@Override
	public int nextInt(int max) {
		int randomNumber; 
		if(!seedSet) {
		randomNumber = (int)(System.nanoTime() % max);
		}else {
			randomNumber = (int)(seed % max);
			int randNumberRev = 0;
			 while(randomNumber != 0) {
		            int digit = randomNumber % 10;
		            randNumberRev = randNumberRev * 10 + digit;
		            randomNumber /= 10;
		        }
			 seed -= (randNumberRev);
		}
		return (int)(seed % max);
	}

	@Override
	public void setSeed(long seed) {
		this.seed = Long.MAX_VALUE;
		this.seed = this.seed - seed;
		seedSet = true;

	}

	@Override
	public void setConstants(long const1, long const2) {
		// TODO Auto-generated method stub

	}

}
