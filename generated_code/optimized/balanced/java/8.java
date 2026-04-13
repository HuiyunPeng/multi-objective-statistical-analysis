import java.util.*;

class Solution {
    public List<Integer> sumProduct(List<Integer> numbers) {
        int sum = 0;
        int product = 1;

        if (numbers instanceof RandomAccess) {
            for (int i = 0, n = numbers.size(); i < n; i++) {
                int v = numbers.get(i);
                sum += v;
                product *= v;
            }
        } else {
            for (Integer v : numbers) {
                sum += v;
                product *= v;
            }
        }

        return List.of(sum, product);
    }
}
