#include <iostream>
#include <vector>
#include <climits>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    279) Perfect Squares
    ===========================

    ============
    Description:
    ============

    Given an integer n, return the least number of perfect square numbers that
    sum to n.

    A perfect square is an integer that is the square of an integer; in other
    words, it is the product of some integer with itself. For example:
        1, 4, 9, and 16 are perfect squares while 3 and 11 are not.

    ================================
    FUNCTION: int numSquares(int n);
    ================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 12
    Output: 3
    Explanation: 12 = 4 + 4 + 4.


    --- Example 2 ---
    Input: n = 13
    Output: 2
    Explanation: 13 = 4 + 9.


    *** Constraints ***
    1 <= n <= 10^4

*/

/*
    ------------
    --- IDEA ---
    ------------

    Find all the perfect squares in first n numbers using the most simple
    method:
        1. Do a sqrt on number 'i', but make sure you store it in an integer.

        2. Now multiply that integer by itself and if you get number 'i' again,
           then that means it's a perfect square number.
           In that case, push it in vector "perfect_squares".

    From this point on, the problem becomes EQUIVALENT to Problem:
        322. "Coin Change"

    "perfect_squares" are "coins", however they are already sorted, so we don't
    have to worry about that.

*/

/* Time  Beats: 18.41% */
/* Space Beats: 48.61% */

/* Time  Complexity: O(n * unique_perfect_squares) */
/* Space Complexity: O(n * unique_perfect_squares) */
class Solution{
public:
    int numSquares(int n)
    {
        int count = 0;
        std::vector<int> perfect_squares;

        // Find al the perfect squares in first n numbers
        for (int i = 1; i <= n; i++)
        {
            int sqrt = std::sqrt(i);

            if (sqrt * sqrt == i)
                perfect_squares.push_back(i);
        }

        /* ========================================================== */
        /* === Coin Change (though, our coins are already sorted) === */
        /* ========================================================== */
        std::vector<int> dp(n + 1, INT_MAX);

        // For amount of 0, we need 0 coins
        dp[0] = 0;

        for (int i = 1; i <= n; i++)
        {
            for (int j = 0; j < perfect_squares.size(); j++)
            {
                if (i - perfect_squares[j] < 0)
                    break;
                else if (dp[i - perfect_squares[j]] != INT_MAX)
                    dp[i] = std::min(dp[i], dp[i - perfect_squares[j]] + 1);
            }
        }

        return dp[n] == INT_MAX ? -1 : dp[n];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Absolutely the same algorithm, however this one is more efficient due to
    using an array allocated on the stack, rather than using a vector which
    dynamically allocates the memory.

*/

/* Time  Beats: 84.39% */
/* Space Beats: 94.20% */

/* Time  Complexity: O(n * unique_perfect_squares) */
/* Space Complexity: O(n * unique_perfect_squares) */
class Solution {
public:
    int numSquares(int n)
    {
        int count = 0;
        std::vector<int> perfect_squares;

        // Find al the perfect squares in first n numbers
        for (int i = 1; i <= n; i++)
        {
            int sqrt = std::sqrt(i);

            if (sqrt * sqrt == i)
                perfect_squares.push_back(i);
        }

        /* ========================================================== */
        /* === Coin Change (though, our coins are already sorted) === */
        /* ========================================================== */
        int dp[n + 1];

        // For amount of 0, we need 0 coins
        dp[0] = 0;

        for (int i = 1; i <= n; i++)
        {
            dp[i] = INT_MAX;
            for (const int& p : perfect_squares)
            {
                if (i - p < 0)
                    break;
                else if (dp[i - p] != INT_MAX)
                    dp[i] = std::min(dp[i], dp[i - p] + 1);
            }
        }

        return dp[n] == INT_MAX ? -1 : dp[n];
    }
};
