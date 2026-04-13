import java.util.*;

class Solution {
    public List<Integer> parseNestedParens(String paren_string) {
        List<Integer> result = new ArrayList<>();
        int depth = 0;
        int maxDepth = 0;
        boolean inGroup = false;

        for (int i = 0, n = paren_string.length(); i < n; i++) {
            char c = paren_string.charAt(i);
            if (c == ' ') {
                if (inGroup) {
                    result.add(maxDepth);
                    depth = 0;
                    maxDepth = 0;
                    inGroup = false;
                }
            } else {
                inGroup = true;
                if (c == '(') {
                    depth++;
                    if (depth > maxDepth) {
                        maxDepth = depth;
                    }
                } else {
                    depth--;
                }
            }
        }

        if (inGroup) {
            result.add(maxDepth);
        }

        return result;
    }
}
