/*
    ============
    === HARD ===
    ============

    ===================================
    4114) Count Consistent Subarrays II
    ===================================

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
    1 <= nums.length <= 2 * 10^5
    0 <= nums[i] <= 10^6

*/

#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 87.23% */
/* Space Beats: 53.46% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    long long countConsistent(vector<int>& nums)
    {
        const int N = nums.size();

        vector<int> left (N, 0);
        vector<int> right(N, N-1);

        vector<int> indices;

        /* Find the nearest index to the left that is NOT a submask */
        for (int i = 0; i < N; i++)
        {
            while ( ! indices.empty() && (nums[i] & nums[indices.back()]) == nums[i])
                indices.pop_back();

            left[i] = indices.empty() ? 0 : indices.back() + 1;
            indices.push_back(i);
        }

        indices.clear();

        /* Find the nearest index to the right that is NOT a submask */
        for (int i = N-1; i >= 0; i--)
        {
            while ( ! indices.empty() && (nums[i] & nums[indices.back()]) == nums[i])
                indices.pop_back();

            right[i] = indices.empty() ? N-1 : indices.back() - 1;
            indices.push_back(i);
        }

        long long result = 0LL;
        unordered_map<int, int> last;

        /* Count valid subarrays while avoiding duplicate overcounting */
        for (int i = 0; i < N; i++)
        {
            const int L = max(left[i], last.count(nums[i]) ? last[nums[i]] + 1 : 0);
            const int R = right[i];

            result += 1LL * (i - L + 1) * (R - i + 1);
            last[nums[i]] = i;
        }

        return result;
    }
};
