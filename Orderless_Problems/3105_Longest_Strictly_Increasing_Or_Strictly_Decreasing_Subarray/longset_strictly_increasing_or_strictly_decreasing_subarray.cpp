/*
    ============
    === EASY ===
    ============

    ================================================================
    3105) Longest Strictly Incresing or Strictly Decreasing Subarray
    ================================================================

    ============
    Description:
    ============

    You are given an array of integers nums. Return the length of the longest
    subarray of nums which is either strictly increasing or strictly decreasing

    ==========================================================
    FUNCTION: int longestMonotonicSubarray(vector<int>& nums);
    ==========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,4,3,3,2]
    Output: 2
    Explanation:
    The strictly increasing subarrays of nums are [1], [2], [3], [3], [4],
                                                  and [1,4].
    The strictly decreasing subarrays of nums are [1], [2], [3], [3], [4],
                                                  [3,2], and [4,3].
    Hence, we return 2.


    --- Example 2 ---
    Input: nums = [3,3,3,3]
    Output: 1
    Explanation:
    The strictly increasing subarrays of nums are [3], [3], [3], and [3].
    The strictly decreasing subarrays of nums are [3], [3], [3], and [3].
    Hence, we return 1.


    --- Example 3 ---
    Input: nums = [3,2,1]
    Output: 3
    Explanation:
    The strictly increasing subarrays of nums are [3], [2], and [1].
    The strictly decreasing subarrays of nums are [3], [2], [1], [3,2], [2,1],
                                                  and [3,2,1].
    Hence, we return 3.


    *** Constraints ***
    1 <= nums.length <= 50
    1 <= nums[i] <= 50

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This is the first messy thought you probably have immediately upon reading
    the problem.

    Check out the 2nd Solutoin down below.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  87.49% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int longestMonotonicSubarray(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        if (N == 1)
            return 1;

        int state = 0;
        int curr = 1;

        for (int i = 1; i < N; i++)
        {
            if (nums[i-1] == nums[i])
            {
                state = 0;
                curr = 1;
            }
            else if (nums[i-1] < nums[i])
            {
                if (state == 1)
                {
                    curr++;
                }
                else
                {
                    state = 1;
                    curr = 2;
                }
            }
            else if (nums[i-1] > nums[i])
            {
                if (state == 2)
                {
                    curr++;
                }
                else
                {
                    state = 2;
                    curr = 2;
                }
            }

            result = max(result, curr);
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Instead of trying some weird if-else conditions, simply try to find longest
    increasing subarray from the front and longest increasing subarray but
    going from the back.

    When going in reverse order, what you see as strictly increasing order is
    actually strictly decreasing order going from the front.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  27.06% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Elegant {
public:
    int longestMonotonicSubarray(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 1;

        int increasing = 1;
        int decreasing = 1;
        for (int i = 1; i < N; i++)
        {
            if (nums[i-1] < nums[i])
                increasing++;
            else
                increasing = 1;

            result = max(result, increasing);

            // Looking for the longest increasing from the back, ie. decreasing
            if (nums[N-1 - i] > nums[N-1 - i+1])
                decreasing++;
            else
                decreasing = 1;

            result = max(result, decreasing);
        }

        return result;
    }
};
