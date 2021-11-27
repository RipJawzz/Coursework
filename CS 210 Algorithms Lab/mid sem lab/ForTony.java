import java.io.File;
import java.util.Arrays;
import java.util.Random;
import java.util.HashMap;
import java.util.Scanner;


public strictfp class ForTony {
	public static strictfp void main(String... args) throws Exception {
		solve(args);
	}
	
	public static strictfp void createInstance(int size) { // creates a problem instance
		java.util.Random r = new java.util.Random(20);
		System.out.print(size + " ");
		for (int i = 0; i < size; i++) {
			double rn = r.nextDouble();
			System.out.print((rn > 0.0 ? rn : -rn) + " ");
		}
	}
	
	public static strictfp void solve(String... args) throws Exception {
		if(args.length == 0) {
			System.out.println("Pass filename as a command line argument.");
			return;
		}
		Scanner scanner = new Scanner(new File(args[0]));
		int n = scanner.nextInt();
		double [] lengths = new double[n];
		for (int i = 0; i < n; i++) {
			lengths[i] = scanner.nextDouble();
		}
		HashMap<String, Double> memoHashMap = new HashMap<>();
		double v1 = helpTony(lengths, memoHashMap);
		double[][] memoDouble2D = new double[n][n];
		double v2 = helpTony(lengths, 0, lengths.length - 1, memoDouble2D);
		System.out.println(v1 + "\n" + v2);
	}
	
	public static strictfp double helpTony(double []               lengths,
                                           HashMap<String, Double> memo){
		String key = Arrays.toString(lengths);
		Double value = (Double) memo.get(key);
		if (value != null) {
			return value;
		} else if (lengths.length == 0) {
			return 0;
		} else if (lengths.length == 1) {
			memo.put(key, lengths[0]);
			return lengths[0];
		} else if (lengths.length == 2) {
			double time = lengths[0] < lengths[1] 
			            ? lengths[0] + 1.5 * lengths[1]
						: lengths[1] + 1.5 * lengths[0];
			memo.put(key, time);
			return time;
		}
		double[] time = new double[lengths.length];
		double[] right = new double[lengths.length - 1];
		for (int j = 0; j < right.length; j++) {
			right[j] = lengths[j + 1];
		}
		time[0] = lengths[0] + 0.5 * lengths[1] + helpTony(right, memo);
		for (int i = 1; i < lengths.length - 1; i++) { // i-th to be attacked first
			double[] newLengths = new double[lengths.length - 1];
			for (int j = 0, k = 0; j < lengths.length; j++) {
				if (j != i) {
					newLengths[k++] = lengths[j];
				}
			}
			time[i] = lengths[i] + 0.5 * (lengths[i - 1] + lengths[i + 1])
                    + helpTony(newLengths, memo);
		}
		double[] left = new double[lengths.length - 1];
		for (int j = 0; j < left.length; j++) {
			left[j] = lengths[j];
		}
		time[time.length - 1] = lengths[lengths.length - 1]
                              + 0.5 * lengths[lengths.length - 2]
						      + helpTony(left, memo);
		double max = Double.NEGATIVE_INFINITY;
		for (double t: time) {
			max = max > t ? max : t;
		}
		memo.put(key, max);
		return max;
	}
	
	public static strictfp double helpTony(double[]   lengths,
										   int        i,
										   int        j,
										   double[][] memo) {
		if(i > j) {
            return 0;
        } else if (memo[i][j] != 0.0) {
            return memo[i][j];
        }
        double left = (i - 1 >= 0) ? (0.5 * lengths[i - 1]) : 0.0;
        double right = (j + 1 < lengths.length) ? (0.5 * lengths[j + 1]) : 0.0;
		double max = 0.0;
        for(int k = i; k <= j; k++) { // k-th to be attacked last
			double current = lengths[k] + left + right;
			double m = lengths[k];
			current += helpTony(lengths, i, k - 1, memo) +
			           helpTony(lengths, k + 1, j, memo);
			max = max > current ? max : current;
        }
        memo[i][j] = max;
        return max;
    }
}