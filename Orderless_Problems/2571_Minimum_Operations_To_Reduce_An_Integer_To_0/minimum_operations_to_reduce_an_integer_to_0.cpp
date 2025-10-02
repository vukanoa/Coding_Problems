/*
    ==============
    === MEDIUM ===
    ==============

    ==================================================
    2573) Minimum Operations to Reduce an Integer to 0
    ==================================================

    ============
    Description:
    ============

    You are given a positive integer n, you can do the following operation any
    number of times:

        + Add or subtract a power of 2 from n.

    Return the minimum number of operations to make n equal to 0.

    A number x is power of 2 if x == 2i where i >= 0.

    ===================================
    FUNCTION: int minOperations(int n);
    ===================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 39
    Output: 3
    Explanation: We can do the following operations:
    - Add 20 = 1 to n, so now n = 40.
    - Subtract 23 = 8 from n, so now n = 32.
    - Subtract 25 = 32 from n, so now n = 0.
    It can be shown that 3 is the minimum number of operations we need to make
    n equal to 0.

    --- Example 2 ---
    Input: n = 54
    Output: 3
    Explanation: We can do the following operations:
    - Add 21 = 2 to n, so now n = 56.
    - Add 23 = 8 to n, so now n = 64.
    - Subtract 26 = 64 from n, so now n = 0.
    So the minimum number of operations is 3.


    *** Constraints ***
    1 <= n <= 10^5

*/

#include <algorithm>
#include <unordered_map>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  60.30% */

/* Time  Complexity: O(logN) */
/* Space Complexity: O(logN) */
class Solution {
public:
    int minOperations(int n)
    {
        if (n == 1)
            return 1;

        int result = __builtin_popcount(static_cast<unsigned int>(n));

        if (n & 1) // If n is ODD
        {
            // O(logN)
            solve(n + 1, 1, result); // Add 1
            solve(n - 1, 1, result); // Subtract 1
        }
        else
        {
            // O(logN)
            solve(n, 0, result);
        }

        return result;
    }

private:
    void solve(int curr_number, int operations_count, int& result)
    {
        if (curr_number > 1e5)
            return;

        // O(1)
        int number_of_set_bits = __builtin_popcount(static_cast<unsigned int>(curr_number));

        result = min(result, operations_count + number_of_set_bits);

        if (number_of_set_bits == 1)
            return;

        int ending_zeroes_count = 0;
        int tmp = curr_number;

        // O(1), since according to Constraints, N = 10^5, which is < 2^17
        // 17 is essentially a constant
        while ((tmp & 1) == 0)
        {
            ending_zeroes_count++;
            tmp >>= 1; // Logical Shift Right
        }

        solve(curr_number + (1 << ending_zeroes_count), operations_count + 1, result);
        solve(curr_number - (1 << ending_zeroes_count), operations_count + 1, result);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats: 10.78% */

/* Time  Complexity: O(log^2(N)) */
/* Space Complexity: O(logN)     */
class Solution_Memoization {
private:
    unordered_map<int, int> memo;

public:
    int minOperations(int n)
    {
        return solve(n);
    }

private:
    int solve(int n)
    {
        if (n == 0)
            return 0;

        if (memo.count(n))
            return memo[n];

        // If n is already a power of 2
        if ((n & (n - 1)) == 0)
            return memo[n] = 1;

        // Find nearest power of 2
        int nearest_pow_of_two = 1;
        while (nearest_pow_of_two < n)
            nearest_pow_of_two <<= 1;

        // Try both: add or subtract power of 2
        int add = 1 + solve(nearest_pow_of_two - n);         // Add      (to reach nearest higher power)
        int sub = 1 + solve(n - (nearest_pow_of_two >> 1));  // Subtract (to reach nearest lower  power)

        return memo[n] = min(add, sub);
    }
};
