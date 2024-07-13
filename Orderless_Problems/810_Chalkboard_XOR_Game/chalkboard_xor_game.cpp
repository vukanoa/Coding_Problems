#include <iostream>
#include <vector>

/*
    ============
    === HARD ===
    ============

    ===========================
    810) Chalkboard XOR Game
    ===========================

    ============
    Description:
    ============

    You are given an array of integers nums represents the numbers written on a
    chalkboard.

    Alice and Bob take turns erasing exactly one number from the chalkboard,
    with Alice starting first. If erasing a number causes the bitwise XOR of
    all the elements of the chalkboard to become 0, then that player loses. The
    bitwise XOR of one element is that element itself, and the bitwise XOR of
    no elements is 0.

    Also, if any player starts their turn with the bitwise XOR of all the
    elements of the chalkboard equal to 0, then that player wins.

    Return true if and only if Alice wins the game, assuming both players play
    optimally.

    ==========================================
    FUNCTION: bool xorGame(vector<int>& nums);
    ==========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,1,2]
    Output: false
    Explanation:
    Alice has two choices: erase 1 or erase 2.
    If she erases 1, the nums array becomes [1, 2]. The bitwise XOR of all the
    elements of the chalkboard is 1 XOR 2 = 3. Now Bob can remove any element
    he wants, because Alice will be the one to erase the last element and she
    will lose.
    If Alice erases 2 first, now nums become [1, 1]. The bitwise XOR of all the
    elements of the chalkboard is 1 XOR 1 = 0. Alice will lose.


    --- Example 2 ---
    Input: nums = [0,1]
    Output: true

    --- Example 3 ---
    Input: nums = [1,2,3]
    Output: true


    *** Constraints ***
    1 <= nums.length <= 1000
    0 <= nums[i] < 2^16

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 80.59% */
/* Space Beats: 12.24% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool xorGame(vector<int>& nums)
    {
        const int n = nums.size();

        int xorr = 0;

        if (n == 1 && nums[0] != 0)
            return false;
        else
        {
            for (int i = 0; i < n; i++)
                xorr = (xorr ^ nums[i]);

            if (xorr == 0)
                return true;
        }

        if (n % 2 == 1)
            return false;
        else
            return true;
    }
};
