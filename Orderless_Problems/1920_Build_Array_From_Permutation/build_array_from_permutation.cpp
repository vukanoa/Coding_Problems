/*
    ============
    === EASY ===
    ============

    ==================================
    1920) Build Array from Permutation
    ==================================

    ============
    Description:
    ============

    Given a zero-based permutation nums (0-indexed), build an array ans of the
    same length where ans[i] = nums[nums[i]] for each 0 <= i < nums.length and
    return it.

    A zero-based permutation nums is an array of distinct integers from 0 to
    nums.length - 1 (inclusive).


    ---------------
    -- Follow Up --
    ---------------

    Can you solve it without using an extra space (i.e., O(1) memory)?

    ====================================================
    FUNCTION: vector<int> buildArray(vector<int>& nums);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [0,2,1,5,3,4]
    Output: [0,1,2,4,5,3]
    Explanation: The array ans is built as follows:
    ans = [nums[nums[0]], nums[nums[1]], nums[nums[2]], nums[nums[3]], nums[nums[4]], nums[nums[5]]]
        = [nums[0], nums[2], nums[1], nums[5], nums[3], nums[4]]
        = [0,1,2,4,5,3]


    --- Example 2 ---
    Input: nums = [5,0,1,2,3,4]
    Output: [4,5,0,1,2,3]
    Explanation: The array ans is built as follows:
    ans = [nums[nums[0]], nums[nums[1]], nums[nums[2]], nums[nums[3]], nums[nums[4]], nums[nums[5]]]
        = [nums[5], nums[0], nums[1], nums[2], nums[3], nums[4]]
        = [4,5,0,1,2,3]


    *** Constraints ***
    1 <= nums.length <= 1000
    0 <= nums[i] < nums.length
    The elements in nums are distinct.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Simulation problem.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  18.10% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */ // return value is usually not considered "extra"
class Solution {
public:
    vector<int> buildArray(vector<int>& nums)
    {
        const int N = nums.size();

        for (int i = 0; i < N; i++)
            swap(nums[i], nums[nums[i]]);

        return nums;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    We can also directly modify the original array nums. This should NOT be
    allowed in general case, especially because the array is passed by
    reference(i.e. '&').

    However, since the "Follow Up" asks us to NOT have "extra" space, that
    means the only way to achieve that is to modify the original "nums".

    But how are we going to both modify the original "nums" and take
    nums[nums[i]]?

    Well, that's exactly where the difficulty lays.
    It seems impossible, but it's actually not.

    The Solution is to enable each element, i.e. nums[i], to store BOTH the
    "original value"(i.e what is there at the beginning) and to store the
    "final value"(i.e., nums[nums[i]]).

    "But that's impossible!", is what you're thinking right now.
    But it's actually not.

    Notice that the range of values of the elements in nums is [0, 999] as it
    is given in Constraints.

    Which means that both the "original value" and the "final value" of each
    element in nums are within [0, 999].

    Therefore, in order to achieve storing BOTH the "original value" and the
    "final value" in nums, we need to use 1000-based system.

    For each element we'll the last three digits will always represents the
    "original value", where as the first(leftmost) three digits will represent
    the "final value".


    Let's look at the example:

        [4,2,0,1,3]
         0 1 2 3 4

    The final output should be:

        [3,0,4,2,1]
         0 1 2 3 4



    Therefore, we're going to first transform this original "nums" to this:

        [4,2,0,1,3]    --->   [3004, 2, 4000, 2001, 1003]
         0 1 2 3 4              0    1    2     3     4


    And then to obtain the desired final result, we just divide each element
    with 1000.

*/

/* Time  Beats: % */
/* Space Beats: `% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Without_Extra_Space {
public:
    vector<int> buildArray(vector<int>& nums)
    {
        const int N = nums.size();

        // Store final values alongside the "original value" in the same index
        for (int i = 0; i < N; i++)
            nums[i] += 1000 * (nums[nums[i]] % 1000);

        // Take off the "original value" from it.
        for (int i = 0; i < N; i++)
            nums[i] /= 1000;

        return nums;
    }
};
