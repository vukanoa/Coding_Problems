/*
    ============
    === HARD ===
    ============

    ==================================
    3102) Minimize Manhattan Distances
    ==================================

    ============
    Description:
    ============

    You are given an array points representing integer coordinates of some
    points on a 2D plane, where points[i] = [xi, yi].

    The distance between two points is defined as their Manhattan distance.

    Return the minimum possible value for maximum distance between any two
    points by removing exactly one point.

    ===========================================================
    FUNCTION: int minimumDistance(vector<vector<int>>& points);
    ===========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: points = [[3,10],[5,15],[10,2],[4,4]]
    Output: 12
    Explanation:
    The maximum distance after removing each point is the following:
        After removing the 0th point the maximum distance is between points (5, 15) and (10, 2), which is |5 - 10| + |15 - 2| = 18.
        After removing the 1st point the maximum distance is between points (3, 10) and (10, 2), which is |3 - 10| + |10 - 2| = 15.
        After removing the 2nd point the maximum distance is between points (5, 15) and (4, 4), which is |5 - 4| + |15 - 4| = 12.
        After removing the 3rd point the maximum distance is between points (5, 15) and (10, 2), which is |5 - 10| + |15 - 2| = 18.
    12 is the minimum possible maximum distance between any two points after removing exactly one point.

    --- Example 2 ---
    Input: points = [[1,1],[1,1],[1,1]]
    Output: 0
    Explanation:
    Removing any of the points results in the maximum distance between any two points of 0.


    *** Constraints ***
    3 <= points.length <= 10^5
    points[i].length == 2
    1 <= points[i][0], points[i][1] <= 10^8

*/

#include <algorithm>
#include <climits>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Calculating "sum" and "diff" for every point is a standard "trick" ONLY
    when we're asked to calculate "Manhattan Distances"!

    Once we calculate all sums and diffs for each point, try leave THAT point
    and seeing what is the maximum difference.

    That's the crux of this Solution.

*/

/* Time  Beats: 51.94% */
/* Space Beats: 58.91% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(logN)     */ // C+='s sort worst SC is O(logN)
class Solution {
public:
    int minimumDistance(vector<vector<int>>& points)
    {
        const int N = points.size();

        vector<pair<int,int>> sum(N);
        vector<pair<int,int>> diff(N);

        // Calculate sum and diff between x and y values of given points
        // and store it along with the index of the point
        for(int i = 0 ; i < points.size() ; i++)
        {
            sum[i]  = {points[i][0] + points[i][1], i};
            diff[i] = {points[i][0] - points[i][1], i};
        }

        sort(sum.begin(), sum.end());
        sort(diff.begin(), diff.end());

        int result = INT_MAX;

        // Try excluding point i
        for(int i = 0 ; i < N ; i++)
        {
            int left = 0;
            int right = N - 1;

            /*
                We're trying to LEAVE OUT current 'i-th' point.

                If that is the point with the LOWEST SUM, then try NEXT
                LOWEST, i.e. "move left to the right by one", i.e. left++


                If that is the point with the HIGHEST SUM, then try PREV
                HIGHEST, i.e. "move right to the left by one", i.e. right--

            */
            if (sum[left].second  == i) left++;
            if (sum[right].second == i) right--;


            int sum_val = sum[right].first - sum[left].first;



            // ------------------------------------------------------------
            left  = 0;
            right = N-1;

            /*
                We're trying to LEAVE OUT current 'i-th' point.

                If that is the point with the LOWEST DIFF, then try NEXT
                LOWEST, i.e. "move left to the right by one", i.e. left++

                If that is the point with the HIGHEST DIFF, then try PREV
                HIGHEST, i.e. "move right to the left by one", i.e. right--

            */
            if (diff[left].second  == i) left++;
            if (diff[right].second == i) right--;


            int diff_val = diff[right].first - diff[left].first;

            // update ans accordingly
            result = min(result, max(sum_val, diff_val));
        }

        return result;
    }
};
