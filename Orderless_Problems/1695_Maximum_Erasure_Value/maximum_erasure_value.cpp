/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    1695) Maximum Erasure Value
    ===========================

    ============
    Description:
    ============

    You are given an array of positive integers nums and want to erase a
    subarray containing unique elements. The score you get by erasing the
    subarray is equal to the sum of its elements.

    Return the maximum score you can get by erasing exactly one subarray.

    An array b is called to be a subarray of a if it forms a contiguous
    subsequence of a, that is, if it is equal to a[l],a[l+1],...,a[r] for some
    (l,r).

    =======================================================
    FUNCTION: int maximumUniqueSubarray(vector<int>& nums);
    =======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [4,2,4,5,6]
    Output: 17
    Explanation: The optimal subarray here is [2,4,5,6].

    --- Example 2 ---
    Input: nums = [5,2,1,2,5,2,1,2,5]
    Output: 8
    Explanation: The optimal subarray here is [5,2,1] or [1,2,5].


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^4

*/

#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    The most fundamental Sliding-Window technique.

*/

/* Time  Beats: 32.30% */
/* Space Beats: 43.04% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int maximumUniqueSubarray(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        int sum = 0;
        unordered_set<int> uset;

        int L = 0;
        int R = 0;
        while (R < N)
        {
            while (uset.count(nums[R]))
            {
                uset.erase(nums[L]);
                sum -= nums[L];
                L++;
            }
            sum += nums[R];
            uset.insert(nums[R]);

            result = max(result, sum);

            // Increment
            R++;
        }

        return result;
    }
};
