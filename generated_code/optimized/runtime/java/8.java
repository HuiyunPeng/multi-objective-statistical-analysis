import java.util.*;

class Solution {
    public List<Integer> sumProduct(List<Integer> numbers) {
        int sum = 0;
        int product = 1;

        if (numbers instanceof RandomAccess) {
            for (int i = 0, size = numbers.size(); i < size; i++) {
                int n = numbers.get(i);
                sum += n;
                product *= n;
            }
        } else {
            for (Iterator<Integer> it = numbers.iterator(); it.hasNext(); ) {
                int n = it.next();
                sum += n;
                product *= n;
            }
        }

        return Arrays.asList(sum, product);
    }
}
