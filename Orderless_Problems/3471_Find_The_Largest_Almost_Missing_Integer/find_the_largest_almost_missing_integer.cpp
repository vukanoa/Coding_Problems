/*
    ============
    === EASY ===
    ============

    =============================================
    3471) Find the Largest Almost Missing Integer
    =============================================

    ============
    Description:
    ============

    You are given an integer array nums and an integer k.

    An integer x is almost missing from nums if x appears in exactly one
    subarray of size k within nums.

    Return the largest almost missing integer from nums. If no such integer
    exists, return -1.
    A subarray is a contiguous sequence of elements within an array.

    =======================================================
    FUNCTION: int largestInteger(vector<int>& nums, int k);
    =======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [3,9,2,1,7], k = 3
    Output: 7
    Explanation:
        1 appears in 2 subarrays of size 3: [9, 2, 1] and [2, 1, 7].
        2 appears in 3 subarrays of size 3: [3, 9, 2], [9, 2, 1], [2, 1, 7].
        3 appears in 1 subarray of size 3: [3, 9, 2].
        7 appears in 1 subarray of size 3: [2, 1, 7].
        9 appears in 2 subarrays of size 3: [3, 9, 2], and [9, 2, 1].

    We return 7 since it is the largest integer that appears in exactly one
    subarray of size k.

    --- Example 2 ---
    Input: nums = [3,9,7,2,1,7], k = 4
    Output: 3
    Explanation:
        1 appears in 2 subarrays of size 4: [9, 7, 2, 1], [7, 2, 1, 7].
        2 appears in 3 subarrays of size 4: [3, 9, 7, 2], [9, 7, 2, 1], [7, 2, 1, 7].
        3 appears in 1 subarray of size 4: [3, 9, 7, 2].
        7 appears in 3 subarrays of size 4: [3, 9, 7, 2], [9, 7, 2, 1], [7, 2, 1, 7].
        9 appears in 2 subarrays of size 4: [3, 9, 7, 2], [9, 7, 2, 1].

    We return 3 since it is the largest and only integer that appears in
    exactly one subarray of size k.

    --- Example 3 ---
    Input: nums = [0,0], k = 1
    Output: -1
    Explanation:
    There is no integer that appears in only one subarray of size 1.


    *** Constraints ***
    1 <= nums.length <= 50
    0 <= nums[i] <= 50
    1 <= k <= nums.length

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    There are SO MANY edge cases. Even though it's easy, it's tricky to
    actually cover every edge case.

    First, it's important to notice that only nums[0] or nums[N-1] can be
    found in EXACTLY one subarray of k, except when k is 1.

    If k is 1, then it can be any number from "nums" that appears only once in
    the entire vector.

    Also, a special case is when N == k. In that case nums[0] and nums[N-1] can
    be the same but we can still return it if it's indeed the largest element
    because in that case there is a total of one subarray in the entire vector.

    If none of the above cases is true, then it's probably that either nums[0]
    or nums[N-1] is the result, or -1.

*/

/* Time  Beats: 100.00% */
/* Space Beats: 100.00% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int largestInteger(vector<int>& nums, int k)
    {
        const int N = nums.size();

        vector<int> counter(51, 0);
        for (const int& num : nums)
            counter[num]++;

        if (k == 1)
        {
            int result = -1;
            for (int num = 50; num >= 0; num--)
            {
                if (counter[num] == 1)
                {
                    result = num;
                    break;
                }
            }

            return result;
        }
        else if (N == k)
        {
            return *max_element(nums.begin(), nums.end());
        }

        if (nums[0] == nums[N-1] || (counter[nums[0]] != 1 && counter[nums[N-1]] != 1))
            return -1;

        if (counter[nums[0]] == 1 && counter[nums[N-1]] == 1)
            return max(nums[0], nums[N-1]);

        return counter[nums[0]] == 1 ? nums[0] : nums[N-1];
    }
};
