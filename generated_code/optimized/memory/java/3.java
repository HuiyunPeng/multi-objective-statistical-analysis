import java.util.List;

class Solution {
    public boolean belowZero(List<Integer> operations) {
        int balance = 0;
        for (int i = 0, n = operations.size(); i < n; i++) {
            balance += operations.get(i);
            if (balance < 0) {
                return true;
            }
        }
        return false;
    }
}
