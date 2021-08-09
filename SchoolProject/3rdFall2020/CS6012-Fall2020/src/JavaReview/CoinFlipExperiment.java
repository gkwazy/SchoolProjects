package lab00;

public class CoinFlipExperiment {

	public static void main(String[] args) {
		int winnings = 0;
		int[] counts = new int[201];

		for (int i = 0; i < 10000; i++) {
			int amount = coinFlipExperiment();
			System.out.println(counts[amount + 100]);
			counts[amount + 100] = counts[amount + 100] + 1;
			System.out.println(counts[amount + 100]);
			winnings += amount;
		}
		System.out.println("Win/loss amount:  " + winnings);
		System.out.println("Likelihood of win/loss amount after 100 flips:");

		System.out.print("Amount");
		System.out.print("\t"); // A tab character
		System.out.print("Probability");
		System.out.println();

		// Loop through amounts

		double attempts = 10000.0;
		for (int i = 0; i <= 200; i++) {
			System.out.print(i - 100);
			System.out.print("\t");
			System.out.print(counts[i] / attempts);
			System.out.println();
		}

	}

	static public int coinFlipExperiment() {
		int winnings = 0;
		for (int i = 0; i < 100; i++) {
			double flip = Math.random();
			if (flip < 0.505) {
				winnings += 1;
			} else {
				winnings -= 1;
			}
		}
		return winnings;

	}

}
