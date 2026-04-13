import java.util.*;
import java.lang.*;

class Solution {
    public double meanAbsoluteDeviation(List<Double> numbers) {
        final int n = numbers.size();
        if (n == 0) return Double.NaN;

        double sum = 0.0;

        if (numbers instanceof RandomAccess) {
            for (int i = 0; i < n; i++) {
                sum += numbers.get(i);
            }
            final double mean = sum / n;
            double sumAbsDiff = 0.0;
            for (int i = 0; i < n; i++) {
                sumAbsDiff += Math.abs(numbers.get(i) - mean);
            }
            return sumAbsDiff / n;
        } else {
            for (Double num : numbers) {
                sum += num;
            }
            final double mean = sum / n;
            double sumAbsDiff = 0.0;
            for (Double num : numbers) {
                sumAbsDiff += Math.abs(num - mean);
            }
            return sumAbsDiff / n;
        }
    }
}
