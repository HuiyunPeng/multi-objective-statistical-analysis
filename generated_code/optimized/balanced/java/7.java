import java.util.*;

class Solution {
    public List<String> filterBySubstring(List<String> strings, String substring) {
        int n = strings.size();
        if (n == 0) return new ArrayList<>(0);
        if (substring.isEmpty()) return new ArrayList<>(strings);

        List<String> result = new ArrayList<>(Math.min(n, 16));
        if (strings instanceof RandomAccess) {
            for (int i = 0; i < n; i++) {
                String s = strings.get(i);
                if (s.indexOf(substring) >= 0) {
                    result.add(s);
                }
            }
        } else {
            for (String s : strings) {
                if (s.indexOf(substring) >= 0) {
                    result.add(s);
                }
            }
        }
        return result;
    }
}
