import java.util.*;

class Solution {
    /**
    Filter an input list of strings only for ones that contain given substring
    >>> filterBySubstring(List.of(), "a")
    []
    >>> filterBySubstring(Arrays.asList("abc", "bacd", "cde", "array"), "a")
    ["abc", "bacd", "array"]
     */
    public List<String> filterBySubstring(List<String> strings, String substring) {
        int n = strings.size();
        if (n == 0) return Collections.emptyList();
        List<String> result = new ArrayList<>(n);
        if (strings instanceof RandomAccess) {
            for (int i = 0; i < n; i++) {
                String s = strings.get(i);
                if (s.contains(substring)) result.add(s);
            }
        } else {
            for (String s : strings) {
                if (s.contains(substring)) result.add(s);
            }
        }
        return result;
    }
}
