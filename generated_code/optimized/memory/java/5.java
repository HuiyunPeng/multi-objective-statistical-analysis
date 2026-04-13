import java.util.*;

class Solution {
    /**
    Insert a number 'delimeter' between every two consecutive elements of input list `numbers'
    >>> intersperse(List.of(), 4)
    []
    >>> intersperse(Arrays.asList(1, 2, 3), 4)
    [1, 4, 2, 4, 3]
     */
    public List<Integer> intersperse(List<Integer> numbers, int delimiter) {
        int n = numbers.size();
        if (n == 0) {
            return Collections.emptyList();
        }
        ArrayList<Integer> result = new ArrayList<>(n * 2 - 1);
        Iterator<Integer> it = numbers.iterator();
        result.add(it.next());
        while (it.hasNext()) {
            result.add(delimiter);
            result.add(it.next());
        }
        return result;
    }
}
