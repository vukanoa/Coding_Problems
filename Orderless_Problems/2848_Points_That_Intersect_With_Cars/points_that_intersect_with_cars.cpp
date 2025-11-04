/*
    ============
    === EASY ===
    ============

    =====================================
    2848) Points that Intersect with Cars
    =====================================

    ============
    Description:
    ============

    You are given a 0-indexed 2D integer array nums representing the
    coordinates of the cars parking on a number line. For any index i,
    nums[i] = [starti, endi] where starti is the starting point of the ith car
    and endi is the ending point of the ith car.

    Return the number of integer points on the line that are covered with any
    part of a car.

    ========================================================
    FUNCTION: int numberOfPoints(vector<vector<int>>& nums);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [[3,6],[1,5],[4,7]]
    Output: 7
    Explanation: All the points from 1 to 7 intersect at least one car,
                 therefore the answer would be 7.

    --- Example 2 ---
    Input: nums = [[1,3],[5,8]]
    Output: 7
    Explanation: Points intersecting at least one car are 1, 2, 3, 5, 6, 7, 8.
                 There are a total of 7 points, therefore the answer would be 7


    *** Constraints ***
    1 <= nums.length <= 100
    nums[i].length == 2
    1 <= starti <= endi <= 100

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO
    (Sweep Line)

*/

/* Time  Beats: 100.00% */
/* Space Beats:  65.59% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int numberOfPoints(vector<vector<int>>& nums)
    {
        const int N = nums.size();

        vector<int> sweepline(102, 0);
        int start = 102;

        for (int i = 0; i < N; i++)
        {
            sweepline[nums[i][0]]++;
            sweepline[nums[i][1] + 1]--;

            start = min(start, nums[i][0]);
        }

        int result = 0;
        int cars = 0;

        for (int i = start; i <= 100; i++)
        {
            cars += sweepline[i];
            if (cars > 0)
                result++;
        }

        return result;
    }
};
