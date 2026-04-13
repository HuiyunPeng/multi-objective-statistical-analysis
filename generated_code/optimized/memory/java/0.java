import java.util.*;
import java.lang.*;

class Solution {
    public boolean hasCloseElements(List<Double> numbers, double threshold) {
        int size = numbers.size();
        for (int i = 0; i < size - 1; i++) {
            double a = numbers.get(i);
            for (int j = i + 1; j < size; j++) {
                if (Math.abs(a - numbers.get(j)) < threshold) {
                    return true;
                }
            }
        }
        return false;
    }
}
