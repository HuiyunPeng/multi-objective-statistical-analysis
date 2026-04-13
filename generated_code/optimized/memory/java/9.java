import java.util.*;
import java.lang.*;

class Solution {
    public List<Integer> rollingMax(List<Integer> numbers) {
        int size = numbers.size();
        List<Integer> result = new ArrayList<>(size);
        if (size == 0) {
            return result;
        }

        Iterator<Integer> it = numbers.iterator();
        int rollingMax = it.next();
        result.add(rollingMax);

        while (it.hasNext()) {
            int value = it.next();
            if (value > rollingMax) {
                rollingMax = value;
            }
            result.add(rollingMax);
        }

        return result;
    }
}
