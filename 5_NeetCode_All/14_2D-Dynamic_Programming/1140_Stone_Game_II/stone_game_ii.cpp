/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    1140) Stone Game II
    ===========================

    ============
    Description:
    ============

    Alice and Bob continue their games with piles of stones.  There are a
    number of piles arranged in a row, and each pile has a positive integer
    number of stones piles[i].  The objective of the game is to end with the
    most stones.

    Alice and Bob take turns, with Alice starting first.  Initially, M = 1.

    On each player's turn, that player can take all the stones in the first X
    remaining piles, where 1 <= X <= 2M.  Then, we set M = max(M, X).

    The game continues until all the stones have been taken.

    Assuming Alice and Bob play optimally, return the maximum number of stones
    Alice can get.

    ==============================================
    FUNCTION: int stoneGameII(vector<int>& piles);
    ==============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: piles = [2,7,9,4,4]
    Output: 10
    Explanation:  If Alice takes one pile at the beginning, Bob takes two
                  piles, then Alice takes 2 piles again. Alice can get 2 + 4 +
                  4 = 10 piles in total. If Alice takes two piles at the
                  beginning, then Bob can take all three piles left. In this
                  case, Alice get 2 + 7 = 9 piles in total. So we return 10
                  since it's larger.


    --- Example 2 ---
    Input: piles = [1,2,3,4,5,100]
    Output: 104


    *** Constraints ***
    1 <= piles.length <= 100
    1 <= piles[i] <= 10^4

*/

#include <cstring>
#include <vector>
#include <climits>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 39.12% */
/* Space Beats: 92.15% */

/* Time  Complexity: O(N^3) */
/* Space Complexity: O(N^2) */
class Solution_Memooooo {
private:
    int memo[101][101][2];

public:
    int stoneGameII(vector<int>& piles)
    {
        const int N = piles.size();

        /* Memset */
        memset(memo, 0xff, sizeof(memo));

        return solve(0, 1, true, piles);
    }

private:
    int solve(int idx, int M, bool alice_turn, vector<int>& piles)
    {
        const int N = piles.size();

        if (idx >= N)
            return 0;

        if (memo[idx][M][alice_turn] != -1)
            return memo[idx][M][alice_turn];

        int result = alice_turn ? 0 : INT_MAX;
        int value  = 0;

        for (int X = 1; X <= 2*M; X++)
        {
            if (idx + X-1 >= N)
                break;

            value += piles[idx + X-1];

            if (alice_turn)
                result = max(result, value + solve(idx + X, max(M, X), false, piles));
            else
                result = min(result, 0     + solve(idx + X, max(M, X),  true, piles));
        }

        return memo[idx][M][alice_turn] = result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 73.45% */
/* Space Beats: 52.69% */

/* Time  Complexity: O(n^3) */
/* Space Complexity: O(n^2) */
class Solution_Bottom_Up {
public:
    int stoneGameII(vector<int>& piles)
    {
        const int N = piles.size();
        
        vector<vector<int>> dp(N, vector<int>(N + 1, 0));
        vector<int> suffix_sum(N, 0);

        suffix_sum[N - 1] = piles[N - 1];
        
        for (int i = N-2; i >= 0; i--)
            suffix_sum[i] = suffix_sum[i + 1] + piles[i];
        
        for (int i = N-1; i >= 0; i--)
        {
            for (int j = 1; j <= N; j++)
            {
                if (i + 2*j >= N)
                {
                    dp[i][j] = suffix_sum[i];
                }
                else
                {
                    for (int x = 1; x <= 2 * j; x++)
                        dp[i][j] = max(dp[i][j], suffix_sum[i] - dp[i + x][max(j, x)]);
                }
            }
        }
        
        return dp[0][1];
    }
};
