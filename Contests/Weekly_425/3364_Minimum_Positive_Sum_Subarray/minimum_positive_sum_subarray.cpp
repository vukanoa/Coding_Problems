/*
    ============
    === EASY ===
    ============

    ===================================
    3364) Minimum Positive Sum Subarray
    ===================================

    ============
    Description:
    ============

    You are given an integer array nums and two integers l and r. Your task is
    to find the minimum sum of a subarray whose size is between l and r
    (inclusive) and whose sum is greater than 0.

    Return the minimum sum of such a subarray. If no such subarray exists,
    return -1.

    A subarray is a contiguous non-empty sequence of elements within an array.

    ==================================================================
    FUNCTION: int minimumSumSubarray(vector<int>& nums, int l, int r);
    ==================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [3, -2, 1, 4], l = 2, r = 3
    Output: 1
    Explanation:
    The subarrays of length between l = 2 and r = 3 where the sum is greater than 0 are:
        [3, -2] with a sum of 1
        [1, 4] with a sum of 5
        [3, -2, 1] with a sum of 2
        [-2, 1, 4] with a sum of 3
    Out of these, the subarray [3, -2] has a sum of 1, which is the smallest
    positive sum. Hence, the answer is 1.


    --- Example 2 ---
    Input: nums = [-2, 2, -3, 1], l = 2, r = 3
    Output: -1
    Explanation:
    There is no subarray of length between l and r that has a sum greater than
    0. So, the answer is -1.


    --- Example 3 ---
    Input: nums = [1, 2, 3, 4], l = 2, r = 4
    Output: 3
    Explanation:
    The subarray [1, 2] has a length of 2 and the minimum sum greater than 0.
    So, the answer is 3.



    *** Constraints ***
    1 <= nums.length <= 100
    1 <= l <= r <= nums.length
    -1000 <= nums[i] <= 1000

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

/* Time  Beats: 10.17% */
/* Space Beats: 64.17% */

/* Time  Complexity: O(N * (R-L+1) * R) */ // Allowed since small Constraints
/* Space Complexity: O(1)               */
class Solution {
public:
    int minimumSumSubarray(vector<int>& nums, int l, int r)
    {
        const int N = nums.size();
        int result = INT_MAX;
        
        for (int curr_size = l; curr_size <= r; curr_size++)
        {
            for (int start = 0; start + curr_size <= N; start++)
            {
                int sum = 0;
                for (int i = start; i < start+curr_size; i++)
                    sum += nums[i];
                
                if (sum > 0)
                    result = min(result, sum);
            }
        }

        return result == INT_MAX ? -1 : result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  90.33% */

/* Time  Complexity: O(N * R) */
/* Space Complexity: O(1)     */
class Solution_2 {
public:
    int minimumSumSubarray(vector<int>& nums, int l, int r)
    {
        const int N = nums.size();
        int result = INT_MAX;

        for (int start = 0; start < N; start++)
        {
            int sum = 0;
            for (int j = start; j < N; j++)
            {
                sum += nums[j];
                int curr_size = j - start + 1;

                if (curr_size > r)
                    break;

                if (curr_size >= l && curr_size <= r && sum > 0)
                    result = min(result, sum);
            }
        }

        return result == INT_MAX ? -1 : result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  38.33% */

/* Time  Complexity: O(N * (R - N + 1)) */
/* Space Complexity: O(1)               */
class Solution_3 {
public:
    int minimumSumSubarray(vector<int>& nums, int l, int r)
    {
        const int N = nums.size();
        int result = INT_MAX;

        for (int curr_size = l; curr_size <= r; curr_size++)
        {
            int sum = 0;
            for (int i = 0; i < N; i++)
            {
                sum += nums[i];

                if ((i - 0 + 1) >= curr_size) // window = (start - end + 1)
                {
                    if (sum > 0)
                        result = min(result, sum);

                    int leftmost_idx_of_curr_window = i - curr_size + 1;
                    sum -= nums[leftmost_idx_of_curr_window];
                }
            }
        }

        return result == INT_MAX ? -1 : result;
    }
};
