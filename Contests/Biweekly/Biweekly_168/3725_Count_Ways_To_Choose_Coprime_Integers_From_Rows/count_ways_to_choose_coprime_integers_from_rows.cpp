/*
    ============
    === HARD ===
    ============

    =====================================================
    3725) Count Ways to Choose Coprime Integers from Rows
    =====================================================

    ============
    Description:
    ============

    You are given a m x n matrix mat of positive integers.

    Return an integer denoting the number of ways to choose exactly one integer
    from each row of mat such that the greatest common divisor of all chosen
    integers is 1.

    Since the answer may be very large, return it modulo 10^9 + 7.

    =====================================================
    FUNCTION: int countCoprime(vector<vector<int>>& mat);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: mat = [[1,2],[3,4]]
    Output: 3

    --- Example 2 ---
    Input: mat = [[2,2],[2,2]]
    Output: 0
    Explanation:
    Every combination has a greatest common divisor of 2. Therefore, the answer
    is 0.


    *** Constraints ***
    1 <= m == mat.length <= 150
    1 <= n == mat[i].length <= 150
    1 <= mat[i][j] <= 150

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

/* Time  Beats: 68.80% */
/* Space Beats: 95.20% */

/* Time  Complexity: O(ROWS * max(mat[row][col])) */
/* Space Complexity: O(ROWS * max(mat[row][col])) */
class Solution_Top_Down__Memoization {
private:
    const int MOD = 1e9 + 7;
    int memo[151][151];

public:
    int countCoprime(vector<vector<int>>& mat)
    {
        const int ROWS = mat.size();
        const int COLS = mat[0].size();

        /* Memset */
        memset(memo, 0xff, sizeof(memo));

        /* Solve */
        return solve(0, 0, mat);
    }

private:
    int solve(int row, int cumulative_gcd, vector<vector<int>>& mat)
    {
        const int ROWS = mat.size();
        const int COLS = mat[0].size();

        if (row == ROWS)
            return cumulative_gcd == 1 ? 1 : 0;

        if (memo[row][cumulative_gcd] != -1)
            return memo[row][cumulative_gcd];


        long long result = 0LL;
        for (int col = 0; col < COLS; col++)
        {
            int curr_val = mat[row][col];
            int next_gcd;

            if (row == 0)
                next_gcd = curr_val;
            else
                next_gcd = my_gcd_iter(cumulative_gcd, curr_val);

            result = (result + solve(row+1, next_gcd, mat)) % MOD;
        }

        return memo[row][cumulative_gcd] = result; 
    }


    int my_gcd_iter(int a, int b)
    {
        if (b == 0)
            return a;

        while (b > 0)
        {
            int tmp = b;

            b = a % b;
            a = tmp;
        }

        return a;
    }
};
