import java.util.AbstractList;
import java.util.List;
import java.util.RandomAccess;

class Solution {
    private static final class IntPairList extends AbstractList<Integer> implements RandomAccess {
        private final int first;
        private final int second;

        IntPairList(int first, int second) {
            this.first = first;
            this.second = second;
        }

        @Override
        public Integer get(int index) {
            if (index == 0) return first;
            if (index == 1) return second;
            throw new IndexOutOfBoundsException();
        }

        @Override
        public int size() {
            return 2;
        }
    }

    public List<Integer> sumProduct(List<Integer> numbers) {
        int sum = 0;
        int product = 1;
        for (int i = 0, n = numbers.size(); i < n; i++) {
            int value = numbers.get(i);
            sum += value;
            product *= value;
        }
        return new IntPairList(sum, product);
    }
}
