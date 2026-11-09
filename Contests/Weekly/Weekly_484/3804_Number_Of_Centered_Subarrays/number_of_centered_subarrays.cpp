/*
    ==============
    === MEDIUM ===
    ==============

    ==================================
    3804) Number of Centered Subarrays
    ==================================

    ============
    Description:
    ============

    You are given an integer array nums.

    A subarray of nums is called centered if the sum of its elements is equal
    to at least one element within that same subarray.

    Return the number of centered subarrays of nums.

    ===================================================
    FUNCTION: int centeredSubarrays(vector<int>& nums);
    ===================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [-1,1,0]
    Output: 5
    Explanation:
        All single-element subarrays ([-1], [1], [0]) are centered.
        The subarray [1, 0] has a sum of 1, which is present in the subarray.
        The subarray [-1, 1, 0] has a sum of 0, which is present in the subarray.
        Thus, the answer is 5.

    --- Example 2 ---
    Input: nums = [2,-3]
    Output: 2
    Explanation:
    Only single-element subarrays ([2], [-3]) are centered.


    *** Constraints ***
    1 <= nums.length <= 500
    -10^5 <= nums[i] <= 10^5

*/

#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Brute Force since Constraints are small.

    I'm not even sure this can be done better than O(N^2).
    I think this is already the most optimal approach in terms of time.

    In terms of space I could've used a bitset instead, but since the
    Constraints are very small, it doesn't really make much of a different.

*/

/* Time  Beats: 25.75% */
/* Space Beats: 35.08% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(N)   */
class Solution {
public:
    int centeredSubarrays(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        for (int i = 0; i < N; i++)
        {
            unordered_set<int> uset_subarray;
            int sum = 0;
            
            for (int j = i; j < N; j++)
            {
                uset_subarray.insert(nums[j]);
                sum += nums[j];

                if (uset_subarray.count(sum))
                    ++result;
            }
        }

        return result;
    }
};
