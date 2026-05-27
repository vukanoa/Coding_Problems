/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    53) Maximum Subarray
    ===========================

    ============
    Description:
    ============

    Given an integer array "nums", find the subarray which has the largest sum
    and return its sum.

    =============================================
    FUNCTION: int maxSubArray(vector<int>& nums);
    =============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  nums = [-2, 1, -3, 4, -1, 2, 1, -5, 4]
    Output: 6
    Explanation: [4, -1, 2, 1] has the largest sum = 6

    --- Example 2 ---
    Input:  nums = [1]
    Output: 1

    --- Example 3 ---
    Input: nums = [5, 4, -1, 7, 8]
    Output: 23

    *** Constraints ***
    1 <= nums.length <= 10^5
    -10^4 <= nums[i] <= 10^4

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

/* Time  Beats: 86.15% */
/* Space Beats: 88.10% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Kadane_Algorithm__Dynamic_Programming {
public:
    int maxSubArray(vector<int>& nums)
    {
        const int N = nums.size();
        int result = INT_MAX;

        int curr_max_sum = nums[0];

        for (int i = 1; i < N; i++)
        {
            curr_max_sum = max(curr_max_sum + nums[i], nums[i]);

            result = max(result, curr_max_sum);
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO
    Same Kadane's Algorithm as above, however this one is conceptually
    different. It leverages "Sliding Window" technique.

    It depends on how you think about the Solution. It's always beneficial to
    see more than one way of writing effectively the same Algorithm.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  51.43% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Kadane_Algorithm__Sliding_Window {
public:
    int maxSubArray(vector<int>& nums)
    {
        const int N = nums.size();
        int result = INT_MIN;

        int curr_sum = 0;

        int L = 0;
        int R = 0;
        while (R < N)
        {
            curr_sum += nums[R];
            result = max(result, curr_sum);

            if (curr_sum < 0)
            {
                L = R+1;
                curr_sum = 0; // Reset
            }

            // Increment
            R++;
        }

        return result;
    }
};
