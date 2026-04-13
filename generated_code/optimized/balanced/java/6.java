import java.util.*;

class Solution {
    public List<Integer> parseNestedParens(String paren_string) {
        int n = paren_string.length();
        List<Integer> result = new ArrayList<>();
        int depth = 0;
        int maxDepth = 0;
        boolean inGroup = false;

        for (int i = 0; i < n; i++) {
            char c = paren_string.charAt(i);
            if (c == '(') {
                depth++;
                if (depth > maxDepth) {
                    maxDepth = depth;
                }
                inGroup = true;
            } else if (c == ')') {
                depth--;
                inGroup = true;
            } else if (c == ' ') {
                if (inGroup) {
                    result.add(maxDepth);
                    depth = 0;
                    maxDepth = 0;
                    inGroup = false;
                }
            }
        }

        if (inGroup) {
            result.add(maxDepth);
        }

        return result;
    }
}
