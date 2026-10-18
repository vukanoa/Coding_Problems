/*
    ============
    === EASY ===
    ============

    ===========================================
    4083) Minimum Deletions to Make Array Sharp
    ===========================================

    ============
    Description:
    ============

    You are given an integer array nums.

    You may delete any number of elements from nums. The remaining elements
    keep their original order.

    The resulting array a is sharp if the bitwise XOR of every pair of adjacent
    elements is non-zero. That is, a[i] XOR a[i + 1] != 0 for every index i
    such that 0 <= i < a.length - 1. An array with at most one element is
    sharp.

    Return the minimum number of deletions needed to make nums sharp.

    Bitwise XOR compares the corresponding bits of two integers. A bit in the
    result is 1 if the corresponding bits differ, and 0 otherwise.

    ==============================================
    FUNCTION: int minDeletions(vector<int>& nums);
    ==============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,1,2,2,2,3]
    Output: 3
    Explanation:
        The pairs at indices (0, 1), (2, 3), and (3, 4) each have an XOR of 0.
        Deleting one 1 and two 2s leaves [1, 2, 3], where 1 XOR 2 == 3 and 2
        XOR 3 == 1 are both non-zero. Therefore, the answer is 3.

    --- Example 2 ---
    Input: nums = [4,4,9,4]
    Output: 1
    Explanation:
        The pair at indices (0, 1) has an XOR of 0.
        Deleting either of these two 4s leaves [4, 9, 4], where 4 XOR 9 == 13
        and 9 XOR 4 == 13 are both non-zero.


    *** Constraints ***
    2 <= nums.length <= 100
    1 <= nums[i] <= 100

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 38.85% */
/* Space Beats: 60.98% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int minDeletions(vector<int>& nums)
    {
        const int N = nums.size();

        int diffs = 0;
        for (int i = 1; i < N; i++)
        {
            if (nums[i-1] != nums[i])
                ++diffs;
        }

        return N - (diffs + 1);
    }
};

/*
    ------------
    --- IDEA ---
    ------------

    Inverted logic of the above Solution.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  60.98% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_2 {
public:
    int minDeletions(vector<int>& nums)
    {
        const int N = nums.size();

        int same_consecutive = 0;
        for (int i = 1; i < N; i++)
        {
            if (nums[i-1] == nums[i])
                ++same_consecutive;
        }

        return same_consecutive;
    }
};
