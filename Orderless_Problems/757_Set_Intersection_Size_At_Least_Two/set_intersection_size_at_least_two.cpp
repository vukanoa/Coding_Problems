/*
    ============
    === HARD ===
    ============

    =======================================
    757) Set Intersection Size At Least Two
    =======================================

    ============
    Description:
    ============

    You are given a 2D integer array intervals where
    intervals[i] = [starti, endi] represents all the integers from starti to
    endi inclusively.

    A containing set is an array nums where each interval from intervals has at
    least two integers in nums.

        + For example, if intervals = [[1,3], [3,7], [8,9]], then
          [1,2,4,7,8,9] and [2,3,4,8,9] are containing sets.

    Return the minimum possible size of a containing set.

    ==================================================================
    FUNCTION: int intersectionSizeTwo(vector<vector<int>>& intervals);
    ==================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: intervals = [[1,3],[3,7],[8,9]]
    Output: 5
    Explanation: let nums = [2, 3, 4, 8, 9].
    It can be shown that there cannot be any containing array of size 4.

    --- Example 2 ---
    Input: intervals = [[1,3],[1,4],[2,5],[3,5]]
    Output: 3
    Explanation: let nums = [2, 3, 4].
    It can be shown that there cannot be any containing array of size 2.

    --- Example 3 ---
    Input: intervals = [[1,2],[2,3],[2,4],[4,5]]
    Output: 5
    Explanation: let nums = [1, 2, 3, 4, 5].
    It can be shown that there cannot be any containing array of size 4.


    *** Constraints ***
    1 <= intervals.length <= 3000
    intervals[i].length == 2
    0 <= starti < endi <= 10^8

*/

#include <vector>
#include <algorithm>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  76.13% */

/* Time  Complexity: O(N log N) */
/* Space Complexity: O(1)       */
class Solution {
public:
    int intersectionSizeTwo(vector<vector<int>>& intervals)
    {
        sort(intervals.begin(), intervals.end(), [] (vector<int>& left, vector<int>& right) {
            const int left_start  = left[0];
            const int left_end    = left[1];

            const int right_start = right[0];
            const int right_end   = right[1];

            if (left_end == right_end)
                return left_start > right_start;

            return left_end < right_end;
        });

        const int N = intervals.size();
        int result = 2;

        int largest_point   = intervals[0][1];
        int second_largest  = largest_point - 1;

        for (int i = 1; i < N; i++)
        {
            const int L = intervals[i][0];
            const int R = intervals[i][1];

            if (second_largest >= L)
                continue;

            bool need_two_elements = (L > largest_point);

            result += 1 + (need_two_elements ? 1 : 0);

            if (need_two_elements)
            {
                second_largest = R - 1;
                largest_point  = R;
            }
            else
            {
                second_largest = largest_point;
                largest_point  = R;
            }
        }

        return result;
    }
};
