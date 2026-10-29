/*
    ==============
    === MEDIUM ===
    ==============

    =======================================
    4089) Count Subarrays With Loose Bounds
    =======================================

    ============
    Description:
    ============

    You are given an integer array nums and two integers minK and maxK.

    A loose-bound subarray is a subarray in which every element is greater than
    or equal to minK and less than or equal to maxK.

    Return the number of loose-bound subarrays in nums.

    A subarray is a contiguous non-empty sequence of elements within an array.

    ==========================================================================
    FUNCTION: long long countSubarrays(vector<int>& nums, int minK, int maxK);
    ==========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,4,7,3], minK = 1, maxK = 5
    Output: 4
    Explanation:
    The loose-bound subarrays are [1], [4], [3], and [1, 4]. The minimum value
    in these subarrays is at least minK = 1 and the maximum value is at most
    maxK = 5.


    --- Example 2 ---
    Input: nums = [1,1], minK = 1, maxK = 1
    Output: 3
    Explanation:
    The loose-bound subarrays are [1], [1], and [1, 1]. The minimum value in
    these subarrays is at least minK = 1 and the maximum value is at most maxK
    = 1.


    *** Constraints ***
    2 <= nums.length <= 10^5
    1 <= nums[i], minK, maxK <= 10^6

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 55.06% */
/* Space Beats: 24.51% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    long long countSubarrays(vector<int>& nums, int minK, int maxK)
    {
        const int N = nums.size();
        long long result = 0LL;

        int len = 0;
        int i = 0;
        while (i < N)
        {
            // If nums[i] is a NON "loose-bound" element
            if (nums[i] < minK || maxK < nums[i])
            {
                result += 1LL * len * (len+1) / 2;
                len = 0; // Reset


                // While nums[i] a NON "loose-bound" element
                while (i < N && (nums[i] < minK || maxK < nums[i]))
                    ++i;
            }
            else
            {
                ++len; // Increment LENGTH of "loose-bound" subarray
                ++i;
            }
        }
        result += 1LL * len * (len+1) / 2;

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Simpler way of doing the same problem.

*/

/* Time  Beats: 67.62% */
/* Space Beats: 96.72% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Simpler {
public:
    long long countSubarrays(vector<int>& nums, int minK, int maxK)
    {
        const int N = nums.size();
        long long result = 0LL;

        int L = 0;
        int R = 0;

        while (R < N)
        {
            if (minK <= nums[R] && nums[R] <= maxK)
                result += (R - L + 1);
            else
                L = R+1;

            // Increment
            ++R;
        }

        return result;
    }
};
