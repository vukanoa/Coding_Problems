/*
    ==============
    === MEDIUM ===
    ==============

    =====================================================
    3914) Minimum Operations to Make Array Non Decreasing
    =====================================================

    ============
    Description:
    ============

    You are given an integer array nums of length n.

    In one operation, you may choose any subarray nums[l..r] and increase each
    element in that subarray by x, where x is any positive integer.

    Return the minimum possible sum of the values of x across all operations
    required to make the array non-decreasing.

    An array is non-decreasing if nums[i] <= nums[i + 1] for all 0 <= i < n-1

    =====================================================
    FUNCTION: long long minOperations(vector<int>& nums);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [3,3,2,1]
    Output: 2
    Explanation:
    One optimal set of operations:
        Choose subarray [2..3] and add x = 1 resulting in [3, 3, 3, 2]
        Choose subarray [3..3] and add x = 1 resulting in [3, 3, 3, 3]
    The array becomes non-decreasing, and the total sum of chosen x values is 1
    + 1 = 2.

    --- Example 2 ---
    Input: nums = [5,1,2,3]
    Output: 4
    Explanation:
    One optimal set of operations:
        Choose subarray [1..3] and add x = 4 resulting in [5, 5, 6, 7]
    The array becomes non-decreasing, and the total sum of chosen x values is 4.


    *** Constraints ***
    1 <= n == nums.length <= 10^5
    1 <= nums[i] <= 10^9

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 55.85% */
/* Space Beats: 58.53% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    long long minOperations(vector<int>& nums)
    {
        const int N = nums.size();
        long long result = 0LL;

        long long top = nums[0];
        
        for (int i = 1; i < N; i++)
        {
            if (top >= nums[i])
                result += top - nums[i];

            top = nums[i];
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 38.13% */
/* Space Beats: 26.87% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Elegant {
public:
    long long minOperations(vector<int>& nums)
    {
        const int N = nums.size();
        long long result = 0LL;

        for (int i = 0; i+1 < N; i++)
            result += max(0, nums[i] - nums[i+1]);

        return result;
    }
};
