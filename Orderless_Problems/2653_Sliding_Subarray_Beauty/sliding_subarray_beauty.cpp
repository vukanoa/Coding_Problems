/*
    ==============
    === MEDIUM ===
    ==============

    ==============================
    2653) Find the Subarray Beauty
    ==============================

    ============
    Description:
    ============


    Given an integer array nums containing n integers, find the beauty of each
    subarray of size k.

    The beauty of a subarray is the xth smallest integer in the subarray if it
    is negative, or 0 if there are fewer than x negative integers.

    Return an integer array containing n - k + 1 integers, which denote the
    beauty of the subarrays in order from the first index in the array.

        A subarray is a contiguous non-empty sequence of elements within an
        array.

    =========================================================================
    FUNCTION: vector<int> getSubarrayBeauty(vector<int>& nums, int k, int x);
    =========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,-1,-3,-2,3], k = 3, x = 2
    Output: [-1,-2,-2]
    Explanation: There are 3 subarrays with size k = 3. 
    The first subarray is [1, -1, -3] and the 2nd smallest negative integer is -1. 
    The second subarray is [-1, -3, -2] and the 2nd smallest negative integer is -2. 
    The third subarray is [-3, -2, 3] and the 2nd smallest negative integer is -2.

    --- Example 2 ---
    Input: nums = [-1,-2,-3,-4,-5], k = 2, x = 2
    Output: [-1,-2,-3,-4]
    Explanation: There are 4 subarrays with size k = 2.
    For [-1, -2], the 2nd smallest negative integer is -1.
    For [-2, -3], the 2nd smallest negative integer is -2.
    For [-3, -4], the 2nd smallest negative integer is -3.
    For [-4, -5], the 2nd smallest negative integer is -4. 

    --- Example 3 ---
    Input: nums = [-3,1,2,-3,0,-3], k = 2, x = 1
    Output: [-3,0,-3,-3,-3]
    Explanation: There are 5 subarrays with size k = 2.
    For [-3, 1], the 1st smallest negative integer is -3.
    For [1, 2], there is no negative integer so the beauty is 0.
    For [2, -3], the 1st smallest negative integer is -3.
    For [-3, 0], the 1st smallest negative integer is -3.
    For [0, -3], the 1st smallest negative integer is -3.


    *** Constraints ***
    n == nums.length 
    1 <= n <= 10^5
    1 <= k <= n
    1 <= x <= k 
    -50 <= nums[i] <= 50 

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Just READ the Constraints!!!

        -50 <= nums[i] <= 50 

    It's a HUGE hint. It basically solves the entire problem.
    It becomes one of the easier types of "Sliding Window" Problems.

*/

/* Time  Beats: 89.40% */
/* Space Beats: 90.13% */

/* Time  Complexity: O((N - k + 1) * 101)  -->  (N - k) */
/* Space Complexity: O(101)                -->  (1)     */
class Solution {
public:
    vector<int> getSubarrayBeauty(vector<int>& nums, int k, int x)
    {
        const int N = nums.size();
        vector<int> result(N - k + 1, 0);

        vector<int> count(101, 0);

        int window_size = 0;

        int L = 0;
        for (int R = 0; R < N; R++)
        {
            count[nums[R] + 50]++;
            window_size++;

            if (window_size < k)
                continue;

            int taken = 0;
            for (int i = 0; i < 101; i++)
            {
                if (taken + count[i] >= x)
                {
                    if (i - 50 >= 0)
                        result[L] = 0;
                    else
                        result[L] = i - 50;

                    break;
                }

                taken += count[i];
            }

            window_size--;
            count[nums[L] + 50]--;
            L++;
        }

        return result;
    }
};
