/*
    ============
    === EASY ===
    ============

    =======================================
    3354) Make Array Elements Equal to Zero
    =======================================

    ============
    Description:
    ============

    You are given an integer array nums.

    Start by selecting a starting position curr such that nums[curr] == 0, and
    choose a movement direction of either left or right.

    After that, you repeat the following process:

        + If curr is out of the range [0, n - 1], this process ends.

        + If nums[curr] == 0, move in the current direction by incrementing curr
          if you are moving right, or decrementing curr if you are moving left.

        + Else if nums[curr] > 0:
            + Decrement nums[curr] by 1.
            + Reverse your movement direction(left becomes right and vice versa
            + Take a step in your new direction.

    A selection of the initial position curr and movement direction is
    considered valid if every element in nums becomes 0 by the end of the
    process.

    Return the number of possible valid selections.

    ======================================================
    FUNCTION: int countValidSelections(vector<int>& nums);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,0,2,0,3]
    Output: 2
    Explanation:
    The only possible valid selections are the following:
        Choose curr = 3, and a movement direction to the left.
            [1,0,2,0,3] -> [1,0,2,0,3] -> [1,0,1,0,3] -> [1,0,1,0,3] ->
            [1,0,1,0,2] -> [1,0,1,0,2] -> [1,0,0,0,2] -> [1,0,0,0,2] ->
            [1,0,0,0,1] -> [1,0,0,0,1] -> [1,0,0,0,1] -> [1,0,0,0,1] ->
            [0,0,0,0,1] -> [0,0,0,0,1] -> [0,0,0,0,1] -> [0,0,0,0,1] ->
            [0,0,0,0,0].

        Choose curr = 3, and a movement direction to the right.
            [1,0,2,0,3] -> [1,0,2,0,3] -> [1,0,2,0,2] -> [1,0,2,0,2] ->
            [1,0,1,0,2] -> [1,0,1,0,2] -> [1,0,1,0,1] -> [1,0,1,0,1] ->
            [1,0,0,0,1] -> [1,0,0,0,1] -> [1,0,0,0,0] -> [1,0,0,0,0] ->
            [1,0,0,0,0] -> [1,0,0,0,0] -> [0,0,0,0,0].


    --- Example 2 ---
    Input: nums = [2,3,4,0,4,1,0]
    Output: 0
    Explanation:
    There are no possible valid selections.


    *** Constraints ***
    1 <= nums.length <= 100
    0 <= nums[i] <= 100
    There is at least one element i where nums[i] == 0.

*/

#include <cstdlib>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    In order to be able to make Zero-Array, when you're on nums[i], either
    one of the three things have to be the case:

        1) sum of elements to the left  of position of 'i' is equal to
           sum of elements to the right of positoin of 'i'

           or

        2) sum of elements to the left  of position of 'i'
              is GREATER by exactly ONE than
           sum of elements to the right of positoin of 'i'

           or

        3) sum of elements to the left  of position of 'i'
              is SMALLER by exactly ONE than
           sum of elements to the right of positoin of 'i'


    If sum of both sides is EQUAL, then it doesn't really matter if we start
    to the left or to the right. We will be able to make Zero-Array whichever
    direction we go first.

    That means, from position nums[i]==0, we can create Zero-Array in 2 ways.


    On the other hand if they differ by ONE, then we MUST start towards the
    side that has a GREATER sum. That way we can create Zero-Array.

    That means, from position nums[i]==0, we can create Zero-Array in 1 way.


    We do this for every nums[i] == 0 and we return number of ways we got along
    the way.

*/

/* Time  Beats: 67.86% */
/* Space Beats: 44.71% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int countValidSelections(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        vector<int> prefix_sum(N, 0);
        prefix_sum[0] = nums[0];

        vector<int> suffix_sum(N, 0);
        suffix_sum[N-1] = nums[N-1];

        for (int i = 1 ; i < N; i++)
        {
            prefix_sum[i] = nums[i] + prefix_sum[i-1];
            suffix_sum[N-1 - i] = nums[N-1 - i] + suffix_sum[N-1 - i + 1];
        }

        for (int i = 0; i < N; i++)
        {
            if (nums[i] == 0)
            {
                if (prefix_sum[i] == suffix_sum[i])
                    result += 2; // Starting either to the left or to the right
                else if (abs(prefix_sum[i] - suffix_sum[i]) == 1)
                    result += 1;
            }
        }

        return result;
    }
};
