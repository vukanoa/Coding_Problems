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

#include <climits>
#include <cmath>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    First find all the perfect squares in first n numbers using the most simple
    method:

        1. Do a sqrt on number 'i', but make sure you store it in an integer.

        2. Now multiply that integer by itself and if you get number 'i' again,
           then that means it's a perfect square number.
           In that case, push it in vector "perfect_squares".


    From this point on, the problem becomes EQUIVALENT to Problem:

        LeetCode 322: "Coin Change"

    "perfect_squares" are "coins", however they are already sorted, so we don't
    have to worry about that.

*/

/* Time  Beats: 47.04% */
/* Space Beats: 38.84% */

/* Time  Complexity: O(N * sqrt(N)) */
/* Space Complexity: O(N)           */
class Solution_Bottom_Up__Tabulation {
public:
    int numSquares(int n)
    {
        const int INFINITE = n+1; // Effectivelly infinite

        /* Generate Perfect-Squares */
        vector<int> perfect_squares;
        for (int i = 1; i <= n; i++)
        {
            int root = sqrt(i);

            if (root * root == i)
                perfect_squares.push_back(i);
        }

        vector<int> dp(n+1, INFINITE);
        dp[0] = 0;

        for (int i = 1; i <= n; i++)
        {
            for (const int& num : perfect_squares)
            {
                if (i - num < 0)
                    break;

                dp[i] = min(dp[i], 1 + dp[i - num]);
            }
        }

        return dp[n];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above; implemented using Top-Down Memoization technique.

*/

/* Time  Beats: 25.18% */
/* Space Beats: 87.90% */

/* Time  Complexity: O(N * sqrt(N)) */
/* Space Complexity: O(N)           */
class Solution_Top_Down__Memoization {
private:
    int memo[10001];

public:
    int numSquares(int n)
    {
        vector<int> perfect_squares;
        for (int i = 1; i <= n; i++)
        {
            int root = sqrt(i);

            if (root * root == i)
                perfect_squares.push_back(i);
        }

        /* Memset */
        memset(memo, 0xff, sizeof(memo));

        return solve(n, perfect_squares);
    }

private:
    int solve(int target, vector<int>& perfect_squares)
    {
        if (target == 0)
            return 0;

        if (memo[target] != -1)
            return memo[target];

        int result = INT_MAX;
        for (const int& num : perfect_squares)
        {
            if (target - num < 0)
                break;

            result = min(result, 1 + solve(target - num, perfect_squares));
        }

        return memo[target] = result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Usually when we're looking for "miminum jumps/steps", a BFS approach can
    be used. Not always though.

*/

/* Time  Beats: 90.61% */
/* Space Beats: 17.58% */

/* Time  Complexity: O(N * sqrt(N)) */
/* Space Complexity: O(N)           */
class Solution_BFS {
public:
    int numSquares(int n)
    {
        vector<int> dp(n+1, n+1);
        dp[0] = 0;

        vector<int> perfect_squares;
        for (int i = 1; i <= n; i++)
        {
            int root = sqrt(i);

            if (root * root == i)
                perfect_squares.push_back(i);
        }

        queue<int> queue;
        queue.push(0);

        int level = 1;
        while ( ! queue.empty())
        {
            int size = queue.size();
            while (size-- > 0)
            {
                int node = queue.front();
                queue.pop();

                for (const int& num : perfect_squares)
                {
                    if (node + num > n)
                        break;

                    if (node + num == n)
                        return level;

                    if (dp[node + num] == n+1)
                        queue.push(node + num);

                    dp[node + num] = min(dp[node + num], level);
                }
            }

            level++;
        }

        return 0;
    }
};
