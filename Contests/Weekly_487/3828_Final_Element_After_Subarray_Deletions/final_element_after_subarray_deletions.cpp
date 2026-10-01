/*
    ==============
    === MEDIUM ===
    ==============

    ============================================
    3828) Final Element After Subarray Deletions
    ============================================

    ============
    Description:
    ============

    You are given an integer array nums.

    Two players, Alice and Bob, play a game in turns, with Alice playing first.

        + In each turn, the current player chooses any nums[l..r] such that r -
          l + 1 < m, where m is the current length of the array.

        + The selected subarray is removed, and the remaining elements are
          concatenated to form the new array.

        + The game continues until only one element remains.

    Alice aims to maximize the final element, while Bob aims to minimize it.
    Assuming both play optimally, return the value of the final remaining
    element.

    ==============================================
    FUNCTION: int finalElement(vector<int>& nums);
    ==============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,5,2]
    Output: 2
    Explanation:
    One valid optimal strategy:
        Alice removes [1], array becomes [5, 2].
        Bob removes [5], array becomes [2]. Thus, the answer is 2.

    --- Example 2 ---
    Input: nums = [3,7]
    Output: 7
    Explanation:
    Alice removes [3], leaving the array [7]. Since Bob cannot play a turn now,
    the answer is 7.


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^5

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    THis is a Game-Theory brain teaser.

    I'm not sure I can formally prove this, but let's think logically:

        nums = [19, 4, 7, 18, 3, 82, 5, 17, 15, 9]
                 0  1  2   3  4   5  6   7   8  9

    Alice starts first and can remove N-1 elements. We're told both players
    will play OPTIMALLY.

    Therefore, she can remove everything but the 19 or everything but the 9.
    Since she is trying to MAXIMIZE the end result, she'd want to have 19 as
    a result.

    But, can she do better?
    Well, yes if Bob does NOT plays optimally.

    So 19 is GUARANTEED for Alice since she plays first. But let's say Alice
    actually takes off these elements, from 6 to 9, inclusive.

        nums = [19, 4, 7, 18, 3, 82, 5, 17, 15, 9]
                 0  1  2   3  4   5  6   7   8  9
                                     ^^^^^^^^^^^^^

    Bob would be left with:

        nums = [19, 4, 7, 18, 3, 82]
                 0  1  2   3  4   5

    Since Bob wants to MINIMIZE, he can either be left with 19 or 82.
    (of course he can try some other, smaller subarray, but he'll then give
     Alice the chance to greedily win)


    So then, let's ask ourselves--If Alice plays OPTIMALLY, how can Bob get
    a SMALLER end result than either nums[0] or nums[N-1]?

    Once you ask that question, you're done. You will NOT be able to find such
    example.

    Therefore, you try with this simple one-liner and it'll pass.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  16.98% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution {
public:
    int finalElement(vector<int>& nums)
    {
        return max(nums[0], nums.back());
    }
};
