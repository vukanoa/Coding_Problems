#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ==========================================
    3254) Find the Power of K-Size Subarrays I
    ==========================================

    ============
    Description:
    ============

    You are given an array of integers nums of length n and a positive integer
    k.

    The power of an array is defined as:

        Its maximum element if all of its elements are consecutive and sorted
        in ascending order.

        -1 otherwise.

    You need to find the power of all subarrays of nums of size k.

    Return an integer array results of size n - k + 1, where results[i] is the
    power of nums[i..(i + k - 1)].

    =============================================================
    FUNCTION: vector<int> resultsArray(vector<int>& nums, int k);
    =============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3,4,3,2,5], k = 3
    Output: [3,4,-1,-1,-1]
    Explanation:
    There are 5 subarrays of nums of size 3:
        [1, 2, 3] with the maximum element 3.
        [2, 3, 4] with the maximum element 4.
        [3, 4, 3] whose elements are not consecutive.
        [4, 3, 2] whose elements are not sorted.
        [3, 2, 5] whose elements are not consecutive.


    --- Example 2 ---
    Input: nums = [2,2,2,2,2], k = 4
    Output: [-1,-1]


    --- Example 3 ---
    Input: nums = [3,2,3,2,3,2], k = 2
    Output: [-1,3,-1,3,-1]


    *** Constraints ***
    1 <= n == nums.length <= 500
    1 <= nums[i] <= 10^5
    1 <= k <= n

*/


/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  91.28% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    vector<int> resultsArray(vector<int>& nums, int k)
    {
        const int n = nums.size();

        int left  = 0;
        int mid   = k-1;
        int right = k-1;

        while (mid > 0)
        {
            if ((nums[mid-1] + 1) != nums[mid])
                break;

            mid--;
        }

        vector<int> result(n-k+1, -1);
        while (right < n)
        {
            if (left == mid)
                result[left] = nums[right];

            left++;
            right++;

            if (right == n)
                break;

            if ((nums[right-1] + 1) != nums[right])
                mid = right;
            else
                mid = max(left, mid); // The one that is further to the right
        }

        return result;
    }
};
