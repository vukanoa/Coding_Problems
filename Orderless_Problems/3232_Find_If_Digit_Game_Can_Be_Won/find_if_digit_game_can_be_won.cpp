/*
    ============
    === EASY ===
    ============

    ===================================
    3232) Find if Digit Game Can Be Won
    ===================================

    ============
    Description:
    ============

    You are given an array of positive integers nums.

    Alice and Bob are playing a game. In the game, Alice can choose either all
    single-digit numbers or all double-digit numbers from nums, and the rest of
    the numbers are given to Bob. Alice wins if the sum of her numbers is
    strictly greater than the sum of Bob's numbers.

    Return true if Alice can win this game, otherwise, return false.

    ==============================================
    FUNCTION: bool canAliceWin(vector<int>& nums);
    ==============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3,4,10]
    Output: false
    Explanation:
    Alice cannot win by choosing either single-digit or double-digit numbers.

    --- Example 2 ---
    Input: nums = [1,2,3,4,5,14]
    Output: true
    Explanation:
    Alice can win by choosing single-digit numbers which have a sum equal to 15

    --- Example 3 ---
    Input: nums = [5,5,5,25]
    Output: true
    Explanation:
    Alice can win by choosing double-digit numbers which have a sum equal to 25


    *** Constraints ***
    1 <= nums.length <= 100
    1 <= nums[i] <= 99

*/

#include <numeric>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    The easiest problem on LeetCode.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  46.04% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool canAliceWin(vector<int>& nums)
    {
        const int N = nums.size();

        int total = accumulate(nums.begin(), nums.end(), 0);

        int one_digit_sum = 0;
        for (int i = 0 ; i < N; i++)
        {
            if (nums[i] < 10)
                one_digit_sum += nums[i];
        }

        return one_digit_sum != (total - one_digit_sum);
    }
};
