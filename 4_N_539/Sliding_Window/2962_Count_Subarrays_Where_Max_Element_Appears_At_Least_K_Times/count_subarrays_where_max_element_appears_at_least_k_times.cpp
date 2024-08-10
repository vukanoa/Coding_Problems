#include <iostream>
#include <vector>
#include <algorithm>

/*
    ==============
    === MEDIUM ===
    ==============

    ================================================================
    2962) Count Subarrays Where Max Element Appears at Least K Times
    ================================================================

    ============
    Description:
    ============

    You are given an integer array nums and a positive integer k.

    Return the number of subarrays where the maximum element of nums appears at
    least k times in that subarray.

    A subarray is a contiguous sequence of elements within an array.

    =============================================================
    FUNCTION: long long countSubarrays(vector<int>& nums, int k);
    =============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,3,2,3,3], k = 2
    Output: 6
    Explanation: The subarrays that contain the element 3 at least 2 times are:
                 [1,3,2,3], [1,3,2,3,3], [3,2,3], [3,2,3,3], [2,3,3] and [3,3].


    --- Example 2 ---
    Input: nums = [1,4,2,1], k = 3
    Output: 0
    Explanation: No subarray contains the element 4 at least 3 times.


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^6
    1 <= k <= 10^5

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 98.57% */
/* Space Beats: 32.34% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    long long countSubarrays(vector<int>& nums, int k)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        const int n = nums.size();
        int max_elem = *std::max_element(nums.begin(), nums.end());
        int max_cnt  = 0;

        long long result = 0;

        int left  = 0;
        int right = 0;

        while (right < n)
        {
            if (nums[right] == max_elem)
                max_cnt++;

            while (max_cnt > k || (left <= right && max_cnt == k && nums[left] != max_elem))
            {
                if (nums[left] == max_elem)
                    max_cnt--;

                left++;
            }

            if (max_cnt == k)
                result += left + 1;

            right++;
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

/* Time  Beats: 99.63% */
/* Space Beats: 32.77% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Concise {
public:
    long long countSubarrays(vector<int>& nums, int k)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        const int n = nums.size();
        int max_elem = *std::max_element(nums.begin(), nums.end());
        int max_cnt  = 0;

        long long result = 0;

        int left  = 0;
        int right = 0;

        while (right < n)
        {
            if (nums[right] == max_elem)
                max_cnt++;

            while (max_cnt == k)
            {
                if (nums[left] == max_elem)
                    max_cnt--;

                left++;
            }

            result += left;

            right++;
        }

        return result;
    }
};
