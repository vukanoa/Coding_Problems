/*
    ============
    === EASY ===
    ============

    ==================================
    4111) Count Consistent Subarrays I
    ==================================

    ============
    Description:
    ============

    You are given an integer array nums.

    A subarray is called consistent if the bitwise AND of all its elements is
    equal to the minimum value of the subarray.

    Return the number of consistent subarrays in
    nums.

    A subarray is a contiguous, non-empty sequence of elements within an array.

    =================================================
    FUNCTION: int countConsistent(vector<int>& nums);
    =================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [5,3,1,2]
    Output: 6
    Explanation:
    The following subarrays are consistent:
    Subarray     Values    Bitwise AND    Minimum Value
    nums[0..0]    [5]         5                    5
    nums[1..1]    [3]         3                    3
    nums[2..2]    [1]         1                    1
    nums[3..3]    [2]         2                    2
    nums[1..2]    [3, 1]      3 AND 1 = 1          1
    nums[0..2]    [5, 3, 1]   5 AND 3 AND 1 = 1    1


    --- Example 2 ---
    Input: nums = [1,1,1]
    Output: 6
    Explanation:
    For every subarray, both the bitwise AND and the minimum value are equal to
    1. Therefore, the answer is 6.


    --- Example 3 ---
    Input: nums = [0]
    Output: 1
    Explanation:
    The only subarray is [0], whose bitwise AND and minimum value are both 0.
    Therefore, the answer is 1.


    *** Constraints ***
    1 <= nums.length <= 100
    0 <= nums[i] <= 100

*/

#include <climits>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 26.61% */
/* Space Beats: 15.03% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(1)   */
class Solution {
public:
    int countConsistent(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        for (int i = 0; i < N; i++)
        {
            int smallest    = INT_MAX;
            int bitwise_and = 0;
            for (int j = i; j < N; j++)
            {
                if (smallest == INT_MAX)
                    bitwise_and = nums[j];
                else
                    bitwise_and &= nums[j];
                
                smallest = min(smallest, nums[j]);

                if (smallest == bitwise_and)
                    ++result;
            }
        }

        return result;
    }
};
