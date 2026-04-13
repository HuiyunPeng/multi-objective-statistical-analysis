import java.util.List;
import java.util.RandomAccess;

class Solution {
    public double meanAbsoluteDeviation(List<Double> numbers) {
        int n = numbers.size();
        if (n == 0) return Double.NaN;

        double sum = 0.0;
        if (numbers instanceof RandomAccess) {
            for (int i = 0; i < n; i++) {
                sum += numbers.get(i);
            }
            double mean = sum / n;
            double absSum = 0.0;
            for (int i = 0; i < n; i++) {
                absSum += Math.abs(numbers.get(i) - mean);
            }
            return absSum / n;
        } else {
            for (Double num : numbers) {
                sum += num;
            }
            double mean = sum / n;
            double absSum = 0.0;
            for (Double num : numbers) {
                absSum += Math.abs(num - mean);
            }
            return absSum / n;
        }
    }
}
