/*
    ==============
    === MEDIUM ===
    ==============

    =================================================
    1828) Queries on Number of Points Inside a Circle
    =================================================

    ============
    Description:
    ============

    You are given an array points where points[i] = [xi, yi] is the coordinates
    of the ith point on a 2D plane. Multiple points can have the same coordinates.

    You are also given an array queries where queries[j] = [xj, yj, rj]
    describes a circle centered at (xj, yj) with a radius of rj.

    For each query queries[j], compute the number of points inside the jth
    circle. Points on the border of the circle are considered inside.

    Return an array answer, where answer[j] is the answer to the jth query.

    =============================================================================================
    FUNCTION: vector<int> countPoints(vector<vector<int>>& points, vector<vector<int>>& queries);
    =============================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: points = [[1,3],[3,3],[5,3],[2,2]], queries = [[2,3,1],[4,3,1],[1,1,2]]
    Output: [3,2,2]
    Explanation: The points and circles are shown above.
    queries[0] is the green circle, queries[1] is the red circle, and queries[2] is the blue circle.

    --- Example 2 ---
    Input: points = [[1,1],[2,2],[3,3],[4,4],[5,5]], queries = [[1,2,2],[2,2,2],[4,3,2],[4,3,3]]
    Output: [2,3,2,4]
    Explanation: The points and circles are shown above.
    queries[0] is green, queries[1] is red, queries[2] is blue, and queries[3] is purple.


    *** Constraints ***
    1 <= points.length <= 500
    points[i].length == 2
    0 <= xi, yi <= 500
    1 <= queries.length <= 500
    queries[j].length == 3
    0 <= xj, yj <= 500
    1 <= rj <= 500
    All coordinates are integers.

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Brute-Force.

*/

/* Time  Beats: 95.02% */
/* Space Beats: 45.02% */

/* Time  Complexity: O(Q * P) */
/* Space Complexity: O(Q)     */
class Solution {
public:
    vector<int> countPoints(vector<vector<int>>& points, vector<vector<int>>& queries)
    {
        vector<int> result;
        for (const auto& query : queries)
        {
            int count = 0;
            int rr = query[2] * query[2];

            for (const auto& point : points)
                count += (query[0] - point[0]) * (query[0] - point[0]) + (query[1] - point[1]) * (query[1] - point[1]) <= rr;

            result.push_back(count);
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Even if this Solutions runs slower on LeetCode, in practice the bigger the
    numbers the faster it will be, meaning the difference will be more
    noticeable.

*/

/* Time  Beats: 81.42% */
/* Space Beats: 20.69% */

/* Time  Complexity: O(P * logP + Q * logP + Q * K) */
/* Space Complexity: O(P + Q)                       */
class Solution_Optimized {
public:
    vector<int> countPoints(vector<vector<int>>& points, vector<vector<int>>& queries)
    {
        vector<int> result;
        vector<vector<int>> sorted_points;

        for (const auto& point : points)
            sorted_points.push_back({point[0], point[1]});

        /* Sort */
        sort(sorted_points.begin(), sorted_points.end());

        for (const auto& q : queries)
        {
            int count = 0;
            int rr = q[2] * q[2];

            auto it = lower_bound(begin(sorted_points), end(sorted_points), vector<int>{q[0] - q[2], 0});

            for (; it != sorted_points.end() && (*it)[0] <= q[0] + q[2]; it++)
                count += (q[0] - (*it)[0]) * (q[0] - (*it)[0]) + (q[1] - (*it)[1]) * (q[1] - (*it)[1]) <= rr;

            result.push_back(count);
        }

        return result;
    }
};
