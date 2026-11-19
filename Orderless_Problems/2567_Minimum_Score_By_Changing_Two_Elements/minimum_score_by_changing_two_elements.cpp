/*
    ==============
    === MEDIUM ===
    ==============

    ============================================
    2567) Minimum Score by Changing Two Elements
    ============================================

    ============
    Description:
    ============

    You are given an integer array nums.

        + The low score of nums is the minimum absolute difference between any
          two integers.

        + The high score of nums is the maximum absolute difference between any
          two integers.

        + The score of nums is the sum of the high and low scores.

    Return the minimum score after changing two elements of nums.

    =============================================
    FUNCTION: int minimizeSum(vector<int>& nums);
    =============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,4,7,8,5]
    Output: 3
    Explanation:
        Change nums[0] and nums[1] to be 6 so that nums becomes [6,6,7,8,5].
        The low score is the minimum absolute difference: |6 - 6| = 0.
        The high score is the maximum absolute difference: |8 - 5| = 3.
        The sum of high and low score is 3.

    --- Example 2 ---
    Input: nums = [1,4,3]
    Output: 0
    Explanation:
        Change nums[1] and nums[2] to 1 so that nums becomes [1,1,1].
        The sum of maximum absolute difference and minimum absolute difference
        is 0.


    *** Constraints ***
    3 <= nums.length <= 10^5
    1 <= nums[i] <= 10^9

*/

#include <algorithm>
#include <climits>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 77.72% */
/* Space Beats: 88.60% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(logN)     */ // SC of C++'s Intro Sort
class Solution {
public:
    int minimizeSum(vector<int>& nums)
    {
        const int N = nums.size();
        if (N == 3)
            return 0;

        /* Sort in ASCENDING order */
        sort(nums.begin(), nums.end());

        return min( {abs(nums[0] - nums[N-3]),
                     abs(nums[2] - nums[N-1]),
                     abs(nums[1] - nums[N-2])} );
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  41.45% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Single_Pass {
public:
    int minimizeSum(vector<int>& nums)
    {
        const int N = nums.size();
        if (N == 3)
            return 0;

        int first_smallest  = INT_MAX;
        int second_smallest = INT_MAX;
        int third_smallest  = INT_MAX;

        int first_largest  = INT_MIN;
        int second_largest = INT_MIN;
        int third_largest  = INT_MIN;

        for (const int& num : nums)
        {
            /* Smallest */
            if (num < first_smallest)
            {
                third_smallest  = second_smallest;
                second_smallest = first_smallest;
                first_smallest  = num;
            }
            else if (num < second_smallest)
            {
                third_smallest  = second_smallest;
                second_smallest = num;
            }
            else if (num < third_smallest)
            {
                third_smallest = num;
            }

            /* Largest */
            if (num > first_largest)
            {
                third_largest  = second_largest;
                second_largest = first_largest;
                first_largest  = num;
            }
            else if (num > second_largest)
            {
                third_largest  = second_largest;
                second_largest = num;
            }
            else if (num > third_largest)
            {
                third_largest = num;
            }
        }

        return min( {abs(first_smallest  - third_largest ),
                     abs(third_smallest  - first_largest ),
                     abs(second_smallest - second_largest)} );
    }
};
