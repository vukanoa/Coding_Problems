/*
    ============
    === EASY ===
    ============

    =========================================
    2928) Distribute Candies Among Children I
    =========================================

    ============
    Description:
    ============

    You are given two positive integers n and limit.

    Return the total number of ways to distribute n candies among 3 children
    such that no child gets more than limit candies.

    ==================================================
    FUNCTION: int distributeCandies(int n, int limit);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 5, limit = 2
    Output: 3
    Explanation: There are 3 ways to distribute 5 candies such that no child
                 gets more than 2 candies: (1, 2, 2), (2, 1, 2) and (2, 2, 1).

    --- Example 2 ---
    Input: n = 3, limit = 3
    Output: 10
    Explanation: There are 10 ways to distribute 3 candies such that no child
                 gets more than 3 candies: (0, 0, 3), (0, 1, 2), (0, 2, 1),
                                           (0, 3, 0), (1, 0, 2), (1, 1, 1),
                                           (1, 2, 0), (2, 0, 1), (2, 1, 0) and
                                           (3, 0, 0).


    *** Constraints ***
    1 <= n <= 50
    1 <= limit <= 50

*/

/*
    ------------
    --- IDEA ---
    ------------

    To solve this problem, we need to find the number of ways to distribute n
    candies among 3 children such that no child gets more than limit candies.

    We can use combinations to calculate the number of ways.

        1. Define a function for "combinations", which calculates the number of
           ways to choose 2 elements from x elements.

        2. Check if n is greater than 3 times limit. If true, it is not
           possible to distribute the candies, so return 0.

        3. Calculate the total combinations (ans) considering all possible
           distributions.

        4. If n is greater than limit, subtract the combinations where a child
           gets more than limit candies.

        5. If n - 2 is greater than or equal to 2 * limit, add the combinations
           where a child gets more than 2 * limit candies.

        6. Return the final result ans an integer.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  23.67% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution {
public:
    int distributeCandies(int n, int limit)
    {
        // Define a lambda function for combinations
        // "Number of ways to choose 2 elements from x"
        auto combinations = [](int x) -> long long {
            return 1LL * x * (x - 1) / 2;
        };

        // Check if n is greater than 3 times limit
        if (n > 3 * limit)
            return 0;

        long long result = combinations(n + 2);

        if (n > limit)
            result -= 3 * combinations(n - limit + 1);

        if (n - 2 >= 2 * limit)
            result += 3 * combinations(n - 2 * limit);

        return static_cast<int>(result);
    }
};
