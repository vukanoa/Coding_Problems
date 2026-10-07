/*
    ==============
    === MEDIUM ===
    ==============

    ==========================================================
    3798) Minimum Subarray Length With Distinct Sum At Least K
    ==========================================================

    ============
    Description:
    ============

    You are given an integer array nums and an integer k.

    Return the minimum length of a subarray whose sum of the distinct values
    present in that subarray (each value counted once) is at least k. If no
    such subarray exists, return -1.

    ==================================================
    FUNCTION: int minLength(vector<int>& nums, int k);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [2,2,3,1], k = 4
    Output: 2
    Explanation:
    The subarray [2, 3] has distinct elements {2, 3} whose sum is 2 + 3 = 5,
    which is at least k = 4. Thus, the answer is 2.

    --- Example 2 ---
    Input: nums = [3,2,3,4], k = 5
    Output: 2
    Explanation:
    The subarray [3, 2] has distinct elements {3, 2} whose sum is 3 + 2 = 5,
    which is at least k = 5. Thus, the answer is 2.

    --- Example 3 ---
    Input: nums = [5,5,4], k = 5
    Output: 1
    Explanation:
    The subarray [5] has distinct elements {5} whose sum is 5, which is at
    least k = 5. Thus, the answer is 1.


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^5
    1 <= k <= 10^9

*/

#include <climits>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 84.61% */
/* Space Beats: 77.80% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int minLength(vector<int>& nums, int k)
    {
        const int N = nums.size();
        int result = INT_MAX;

        unordered_map<int,int> freq;
        int left  = 0;
        int right = 0;

        int sum = 0;
        while (right < N)
        {
            ++freq[nums[right]];

            if (freq[nums[right]] == 1) // New DISTINCT value in subarray
                sum += nums[right];

            while (left <= right && sum >= k)
            {
                result = min(result, right - left + 1);
                
                --freq[nums[left]];

                if (freq[nums[left]] == 0) // Removed this DISTINCT value
                    sum -= nums[left];

                // Increment
                ++left;
            }

            // Increment
            ++right;
        }

        return result == INT_MAX ? -1 : result;
    }
};
