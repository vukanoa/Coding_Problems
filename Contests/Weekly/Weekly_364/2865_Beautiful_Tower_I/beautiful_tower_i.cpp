/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    2865) Beautiful Towers I
    ===========================

    ============
    Description:
    ============

    You are given an array heights of n integers representing the number of
    bricks in n consecutive towers. Your task is to remove some bricks to form
    a mountain-shaped tower arrangement. In this arrangement, the tower heights
    are non-decreasing, reaching a maximum peak value with one or multiple
    consecutive towers and then non-increasing.

    Return the maximum possible sum of heights of a mountain-shaped tower
    arrangement.

    ==============================================================
    FUNCTION: long long maximumSumOfHeights(vector<int>& heights);
    ==============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: heights = [5,3,4,1,1]
    Output: 13
    Explanation:
    We remove some bricks to make heights = [5,3,3,1,1], the peak is at index 0

    --- Example 2 ---
    Input: heights = [6,5,3,9,2,7]
    Output: 22
    Explanation:
    We remove some bricks to make heights = [3,3,3,9,2,2], the peak is at index
    3.

    --- Example 3 ---
    Input: heights = [3,2,5,5,2,3]
    Output: 18
    Explanation:
    We remove some bricks to make heights = [2,2,5,5,2,2], the peak is at index
    2 or 3.


    *** Constraints ***
    1 <= n == heights.length <= 10^3
    1 <= heights[i] <= 10^9

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Brute Force.

*/

/* Time  Beats:  5.91% */
/* Space Beats: 11.42% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(1)   */
class Solution {
public:
    long long maximumSumOfHeights(vector<int>& heights)
    {
        const int N = heights.size();
        long long result = 0;

        for (int start = 0; start < N; start++) // try each peak
        {
            vector<int> copy = heights;
            long long L_sum = 0;
            long long R_sum = 0;

            // Non-decreasing (i.e. increasing with duplicates)
            int i = start-1;
            while (i >= 0)
            {
                if (copy[i] > copy[i+1])
                    copy[i] = copy[i+1];
                
                L_sum += copy[i];
                
                --i;
            }

            // Non-increasing(i.e. decreasing  with duplicates)
            int j = start + 1;
            while (j < N)
            {
                if (copy[j-1] < copy[j])
                    copy[j] = copy[j-1];

                R_sum += copy[j];
                ++j;
            }

            result = max(result, L_sum + copy[start] + R_sum);
        }


        return result;
    }
};
