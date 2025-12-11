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
    int memo[21][21]; // dp array

public:
    bool predictTheWinner(vector<int>& nums) 
    {
        const int N = nums.size();

        // Initialize memo with -1
        memset(memo, 0xff, sizeof(memo));

        int total = 0;
        for (const auto& num : nums)
            total += num;

        int max_score = get_max_score(0, N-1, nums, total);

        return is_winner(max_score, total);
    }

private:
    bool is_winner(int score, int total) 
    {
        return score >= total - score;
    }

    int get_max_score(int left, int right, vector<int>& nums, int total) 
    {
        if (left > right)
            return 0;

        if (memo[left][right] != -1)
            return memo[left][right];

        // Skip-Take logic
        int take_left  = total - get_max_score(left+1, right  , nums, total - nums[left]);
        int take_right = total - get_max_score(left  , right-1, nums, total - nums[right]);

        return memo[left][right] = max(take_left, take_right);
    }
};
