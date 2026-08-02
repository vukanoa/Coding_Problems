/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    486) Predict the Winner
    ===========================

    ============
    Description:
    ============

    You are given an integer array nums. Two players are playing a game with
    this array: player 1 and player 2.

    Player 1 and player 2 take turns, with player 1 starting first. Both
    players start the game with a score of 0. At each turn, the player takes
    one of the numbers from either end of the array (i.e., nums[0] or
    nums[nums.length - 1]) which reduces the size of the array by 1. The player
    adds the chosen number to their score. The game ends when there are no more
    elements in the array.

    Return true if Player 1 can win the game. If the scores of both players are
    equal, then player 1 is still the winner, and you should also return true.
    You may assume that both players are playing optimally.

    ===================================================
    FUNCTION: bool predictTheWinner(vector<int>& nums);
    ===================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,5,2]
    Output: false
    Explanation: Initially, player 1 can choose between 1 and 2. 
    If he chooses 2 (or 1), then player 2 can choose from 1 (or 2) and 5. If
    player 2 chooses 5, then player 1 will be left with 1 (or 2). So, final
    score of player 1 is 1 + 2 = 3, and player 2 is 5. Hence, player 1 will
    never be the winner and you need to return false.

    --- Example 2 ---
    Input: nums = [1,5,233,7]
    Output: true
    Explanation: Player 1 first chooses 1. Then player 2 has to choose between
    5 and 7. No matter which number player 2 choose, player 1 can choose 233.
    Finally, player 1 has more score (234) than player 2 (12), so you need to
    return True representing player1 can win.


    *** Constraints ***
    1 <= nums.length <= 20
    0 <= nums[i] <= 10^7

*/

#include <cstring>
#include <numeric>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Classic Skip-Take Memoization.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  85.74% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(N^2) */
class Solution {
private:
    int memo[21][21];

public:
    bool predictTheWinner(vector<int>& nums) 
    {
        const int N = nums.size();

        // Initialize memo with -1
        memset(memo, 0xff, sizeof(memo));

        int total = 0;
        for (const auto& num : nums)
            total += num;

        int max_score = solve(0, N-1, nums, total);

        return is_winner(max_score, total);
    }

private:
    bool is_winner(int score, int total) 
    {
        return score >= total - score;
    }

    int solve(int L, int R, vector<int>& nums, int total) 
    {
        if (L > R)
            return 0;

        if (memo[L][R] != -1)
            return memo[L][R];

        // Skip-Take logic
        int take_left  = total - solve(L+1, R  , nums, total - nums[L]);
        int take_right = total - solve(L  , R-1, nums, total - nums[R]);

        return memo[L][R] = max(take_left, take_right);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Classic example of a "Zero-sum game".

    During Player 1's turn, choosing a value x increases the score difference
    by X. Conversely, during Player 2's turn, choosing a value Y decreases the
    score difference by Y.

    Essentially, this is a "zero−sum" game:

        + Every point gained by one player is effectively a point lost by the
          other.

        + Therefore, instead of tracking both scores separately, we only need
          to track their score difference.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  69.53% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(N^2) */
class Solution_Zero_Sum__Game_Theory__Top_Down__Memoization {
private:
    int memo[21][21];

public:
    bool predictTheWinner(vector<int>& nums)
    {
        const int N = nums.size();

        /* Memset */
        memset(memo, 0xff, sizeof(memo));

        int max_diff_in_favor_of_player1 = max_diff(0, N-1, nums);

        return max_diff_in_favor_of_player1 >= 0;
    }

private:
    int max_diff(int start, int end, vector<int>& nums)
    {
        if (start == end)
            return memo[start][end] = nums[start]; // Or nums[end] it's w/e

        if (memo[start][end] != -1)
            return memo[start][end];

        int take_first = nums[start] - max_diff(start+1, end  , nums);
        int take_last  = nums[end  ] - max_diff(start  , end-1, nums);

        return memo[start][end] = max(take_first, take_last);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 46.53% */
/* Space Beats: 52.55% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(N^2) */
class Solution_Zero_Sum__Game_Theory__Bottom_Up__Tabulation {
public:
    bool predictTheWinner(vector<int>& nums)
    {
        const int N = nums.size();

        vector<vector<int>> dp(N, vector<int>(N, 0));

        for (int start = N-1; start >= 0; start--)
        {
            for (int end = start; end < N; end++)
            {
                if (start == end)
                {
                    dp[start][end] = nums[start];
                    continue;
                }

                int take_first = nums[start] - dp[start+1][end  ];
                int take_last  = nums[end]   - dp[start  ][end-1];

                dp[start][end] = max(take_first, take_last);
            }
        }

        return dp[0][N-1] >= 0;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  85.04% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(N^2) */
class Solution_With_Turns {
private:
    int memo[21][21][2];

public:
    bool predictTheWinner(vector<int>& nums)
    {
        const int N = nums.size();

        /* Memset */
        memset(memo, 0xff, sizeof(memo));

        long long total_sum = accumulate(nums.begin(), nums.end(), 0LL);

        /* Solve */
        int player1 = solve(0, N-1, true, nums);

        return is_winner(player1, total_sum);
    }

private:
    bool is_winner(int score, int total) 
    {
        return score >= (total - score);
    }

    int solve(int L, int R, bool player1_turn, vector<int>& nums)
    {
        if (L > R)
            return 0;

        if (memo[L][R][player1_turn] != -1)
            return memo[L][R][player1_turn];

        int take_first = 0;
        int take_last  = 0;

        if (player1_turn)
        {
            take_first = nums[L] + solve(L+1, R  , false, nums);
            take_last  = nums[R] + solve(L  , R-1, false, nums);
        }
        else
        {
            take_first =     0   + solve(L+1, R  , true,  nums);
            take_last  =     0   + solve(L  , R-1, true,  nums);
        }

        return memo[L][R][player1_turn] = player1_turn ? max(take_first, take_last) :
                                                         min(take_first, take_last);
    }
};
