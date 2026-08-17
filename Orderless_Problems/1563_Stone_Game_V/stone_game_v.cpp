/*
    ============
    === HARD ===
    ============

    ===========================
    1563) Stone Game V
    ===========================

    ============
    Description:
    ============

    There are several stones arranged in a row, and each stone has an
    associated value which is an integer given in the array stoneValue.

    In each round of the game, Alice divides the row into two non-empty rows
    (i.e. left row and right row), then Bob calculates the value of each row
    which is the sum of the values of all the stones in this row. Bob throws
    away the row which has the maximum value, and Alice's score increases by
    the value of the remaining row. If the value of the two rows are equal, Bob
    lets Alice decide which row will be thrown away. The next round starts with
    the remaining row.

    The game ends when there is only one stone remaining. Alice's score is
    initially zero.

    Return the maximum score that Alice can obtain.

    ==================================================
    FUNCTION: int stoneGameV(vector<int>& stoneValue);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: stoneValue = [6,2,3,4,5,5]
    Output: 18
    Explanation: In the first round, Alice divides the row to [6,2,3], [4,5,5].
    The left row has the value 11 and the right row has value 14. Bob throws
    away the right row and Alice's score is now 11. In the second round Alice
    divides the row to [6], [2,3]. This time Bob throws away the left row and
    Alice's score becomes 16 (11 + 5). The last round Alice has only one choice
    to divide the row which is [2], [3]. Bob throws away the right row and
    Alice's score is now 18 (16 + 2). The game ends because only one stone is
    remaining in the row.

    --- Example 2 ---
    Input: stoneValue = [7,7,7,7,7,7,7]
    Output: 28

    --- Example 3 ---
    Input: stoneValue = [4]
    Output: 0


    *** Constraints ***
    1 <= stoneValue.length <= 500
    1 <= stoneValue[i] <= 10^6

*/

#include <cstring>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 95.10% */
/* Space Beats: 98.65% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(N^2) */
class Solution_Top_Down__Memoization__Exclusive_Prefix_Sum {
private:
    int memo[501][501];
    int prefix_sum[501];

public:
    int stoneGameV(vector<int>& stoneValue)
    {
        const int N = stoneValue.size();

        /* Prefix Sum */
        for (int i = 0; i < N; i++)
            prefix_sum[i + 1] = prefix_sum[i] + stoneValue[i];

        /* Memset */
        memset(memo, 0xff, sizeof(memo));

        return solve(0, N-1, stoneValue);
    }

private:
    int solve(int left, int right, vector<int>& stoneValue)
    {
        if (left >= right)
            return 0;

        if (memo[left][right] != -1)
            return memo[left][right];

        int result = 0;

        for (int mid = left; mid < right; mid++)
        {
            int left_sum  = prefix_sum[mid   + 1] - prefix_sum[left   ];
            int right_sum = prefix_sum[right + 1] - prefix_sum[mid + 1];

            if (left_sum <= right_sum)
                result = max(result, left_sum  + solve(left   , mid  , stoneValue));

            if (left_sum >= right_sum)
                result = max(result, right_sum + solve(mid + 1, right, stoneValue));

            /* Prunning branch */
            if (2 * min(left_sum, right_sum) <= result)
                break;
        }

        return memo[left][right] = result;
    }
};
