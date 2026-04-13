import java.util.*;

class Solution {
    public boolean belowZero(List<Integer> operations) {
        int balance = 0;
        if (operations instanceof RandomAccess) {
            for (int i = 0, n = operations.size(); i < n; i++) {
                balance += operations.get(i);
                if (balance < 0) return true;
            }
        } else {
            for (Iterator<Integer> it = operations.iterator(); it.hasNext();) {
                balance += it.next();
                if (balance < 0) return true;
            }
        }
        return false;
    }
}
