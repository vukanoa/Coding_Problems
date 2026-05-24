/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    877) Stone Game
    ===========================

    ============
    Description:
    ============

    Alice and Bob play a game with piles of stones. There are an even number of
    piles arranged in a row, and each pile has a positive integer number of
    stones piles[i].

    The objective of the game is to end with the most stones. The total number
    of stones across all the piles is odd, so there are no ties.

    Alice and Bob take turns, with Alice starting first. Each turn, a player
    takes the entire pile of stones either from the beginning or from the end
    of the row. This continues until there are no more piles left, at which
    point the person with the most stones wins.

    Assuming Alice and Bob play optimally, return true if Alice wins the game,
    or false if Bob wins.

    =============================================
    FUNCTION: bool stoneGame(vector<int>& piles); 
    =============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: piles = [5,3,4,5]
    Output: true
    Explanation: 
    Alice starts first, and can only take the first 5 or the last 5.
    Say she takes the first 5, so that the row becomes [3, 4, 5].
    If Bob takes 3, then the board is [4, 5], and Alice takes 5 to win with 10
    points.  If Bob takes the last 5, then the board is [3, 4], and Alice takes
    4 to win with 9 points.  This demonstrated that taking the first 5 was a
    winning move for Alice, so we return true.


    --- Example 2 ---
    Input: piles = [3,7,2,3]
    Output: true


    *** Constraints ***
    2 <= piles.length <= 500
    piles.length is even.
    1 <= piles[i] <= 500
    sum(piles[i]) is odd.

*/

#include <vector>
#include <bits/stdc++.h>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 20.22% */
/* Space Beats: 26.60% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(N^2) */
class Solution_Top_Down__Memoization {
private:
    int memo[501][501];

public:
    bool stoneGame(vector<int>& piles)
    {
        const int N = piles.size();

        int total_sum = accumulate(piles.begin(), piles.end(), 0);

        /* Memset */
        memset(memo, 0xff, sizeof(memo));

        /* Solve */
        int alice_points = solve(0, N-1, 0, true, piles);

        return alice_points > (total_sum / 2);
    }

private:
    int solve(int start, int end, int alice_points, bool alice_turn, vector<int>& piles)
    {
        if (start > end)
            return alice_points;

        if (memo[start][end] != -1)
            return memo[start][end];

        int take_first = 0;
        int take_last  = 0;

        if (alice_turn)
        {
            take_first = solve(start+1, end  , alice_points + piles[start], false, piles);
            take_last  = solve(start  , end-1, alice_points + piles[end]  , false, piles);
        }
        else
        {
            take_first = solve(start+1, end  , alice_points + 0           , true , piles);
            take_last  = solve(start  , end-1, alice_points + 0           , true , piles);
        }

        return memo[start][end] = max(take_first, take_last);
    }
};
