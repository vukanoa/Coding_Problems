/*
    ==============
    === MEDIUM ===
    ==============

    =================================
    4044) Count Good Cyclic Rotations
    =================================

    ============
    Description:
    ============

    You are given an integer array nums of even length n.

    A cyclic rotation of nums is obtained by choosing a prefix of nums whose
    length is between 0 and n - 1 (inclusive), and moving it to the end of the
    array while preserving the order of all elements.

    A cyclic rotation is good if the sum of its first n / 2 elements is
    strictly greater than the sum of its last n / 2 elements.

    Return the number of cyclic rotations of nums that are good.

    ====================================================
    FUNCTION: int countGoodRotations(vector<int>& nums);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3,4,5,6]
    Output: 3

    --- Example 2 ---
    Input: nums = [1,2,1,2]
    Output: 0


    *** Constraints ***
    2 <= n == nums.length <= 10^5
    1 <= nums[i] <= 10^9
    n is even.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats:  6.80% */
/* Space Beats: 10.71% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int countGoodRotations(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;
        
        vector<long long> prefix_sum(2*N, 0);

        prefix_sum[0] = nums[0];
        for (int i = 1; i < 2*N; i++)
            prefix_sum[i] = prefix_sum[i-1] + nums[i % N];

        for (int i = N-1; i < 2*N-1; i++)
        {
            long long left_sum  = prefix_sum[i - N/2] - (i - N >= 0 ? prefix_sum[i - N] : 0);
            long long right_sum = prefix_sum[i      ] - prefix_sum[i - N/2];

            if (left_sum > right_sum)
                ++result;
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

/* Time  Beats: 55.71% */
/* Space Beats: 83.92% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Space_Efficient {
public:
    int countGoodRotations(vector<int>& nums)
    {
        const int N = nums.size();
        long long result = 0LL; 

        long long total_sum = 0LL; 
        for (const int& number : nums)
            total_sum += number; 

        long long left_half_sum = 0LL;
        for (int i = 0; i < N; i++)
        {
            if (i >= N/2)
            {
                if (left_half_sum != (total_sum - left_half_sum))
                    ++result; 

                // Remove the leftmost one in the current left_half subarray
                left_half_sum -= nums[i - N/2]; 
            }

            left_half_sum += nums[i]; // Rotate 
        }

        return result;
    }
};
