/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    55) Jump Game
    ===========================

    ============
    Description:
    ============

    You are given an integer array "nums". You are initially positioned at the
    array's first index, and each element in the array represents your maximum
    jump length at that position.

    Return "true" if you can reach the last index, or "false" otherwise.

    ==========================================
    FUNCTION: bool canJump(vector<int>& nums);
    ==========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  nums = [2, 3, 1, 1, 4]
    Output: true

    --- Example 2 ---
    Input:  nums = [3, 2, 1, 0, 4]
    Output: false

    --- Example 3 ---
    Input:  nums = [2, 3, 1, 1, 2, 4, 1, 2, 1, 3]
    Output: true

    *** Constraints ***
    1 <= nums.length <= 10^4
    0 <= nums[i] <= 10^5

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    We check each element only once.

    Consider this Example:
    [2, 3, 1, 1, 2, 4, 1, 2, 1, 3]
     0  1  2  3  4  5  6  7  8  9

    We begin by putting both "start" and "end" variables at 0.

    In the very first iteration we only check if there's a max_reach that is
    longer than 0. If there's not => return false.

    Since we're updating our start to begin each iteration at "end + 1" if
    we exceed our "max_reach", that is "start" becomes a higher index than we
    calculated is possible to reach, we return false.

    So how do we check each element only once?

    The idea is simple.
    1st Iteration    - Find max_reach and move to nums[1];
    Other Iterations - Check if any element from "start" to our "max_reach"
                       reaches or exceeds the very last element.
                       If it does => return true.
                       If it does NOT => start from "old max_reach" + 1
                       "old max_reach" is "end".

*/

/*
    ------------
    --- IDEA ---
    ------------

    A truly Greedy approach.

*/

/* Time  Beats: 94.09% */
/* Space Beats: 52.77% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Greedy {
public:
    bool canJump(vector<int>& nums)
    {
        const int N = nums.size();
        int goal = N-1; // Leftmost index that can reach >= N-1

        for (int i = N-2; i >= 0; i--)
        {
            if (i + nums[i] >= goal)
                goal = i;
        }

        return goal == 0;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Similar to above, though conceptually different.

    This one goes left-to-right, instead of the other way around. I believe
    this one is much easier to grasp.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  82.12% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Greedy_2 {
public:
    bool canJump(vector<int>& nums)
    {
        const int N = nums.size();

        int idx = 0;
        int max_reach = 0;

        while (idx <= max_reach)
        {
            max_reach = max(max_reach, idx + nums[idx]);

            if (max_reach >= N-1)
                return true;

            // Increment
            idx++;
        }

        return false;
    }
};
