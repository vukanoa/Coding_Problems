/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    397) Integer Replacement
    ===========================

    ============
    Description:
    ============

    Given a positive integer n, you can apply one of the following operations:

        1. If n is even, replace n with n / 2.
        2. {If n is odd, replace n with either n + 1 or n - 1.

    Return the minimum number of operations needed for n to become 1.

    ========================================
    FUNCTION: int integerReplacement(int n);
    ========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 8
    Output: 3
    Explanation: 8 -> 4 -> 2 -> 1

    --- Example 2 ---
    Input: n = 7
    Output: 4
    Explanation: 7 -> 8 -> 4 -> 2 -> 1
    or 7 -> 6 -> 3 -> 2 -> 1

    --- Example 3 ---
    Input: n = 4
    Output: 2


    *** Constraints ***
    1 <= n <= 2^31 - 1

*/

/*
    ------------
    --- IDEA ---
    ------------

    Classic Recursive problem.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  59.91% */

/* Time  Complexity: O(logN) */
/* Space Complexity: O(logN) */
class Solution {
public:
    int integerReplacement(int n)
    {
        return count_steps_to_reach_one(static_cast<long long>(n), 0);
    }

private:
    int count_steps_to_reach_one(long long curr_val, int step_count)
    {
        if (curr_val == 1)
            return step_count;

        if (is_even(curr_val))
        {
            return count_steps_to_reach_one(divide_by_two(curr_val), step_count + 1);
        }
        else
        {
            if (should_decrement(curr_val))
            {
                return count_steps_to_reach_one(curr_val - 1, step_count + 1);
            }
            else
            {
                return count_steps_to_reach_one(curr_val + 1, step_count + 1);
            }
        }
    }

    bool is_even(long long value)
    {
        return value % 2 == 0;
    }

    long long divide_by_two(long long value)
    {
        return value >> 1;
    }

    bool should_decrement(long long odd_value)
    {
        // If value is 3 or if (value / 2) is even, prefer decrement
        return odd_value == 3 || !((odd_value >> 1) & 1);
    }
};
