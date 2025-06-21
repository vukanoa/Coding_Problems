/*
    ==============
    === MEDIUM ===
    ==============

    =====================================
    3588) Find Maximum Area of a Triangle
    =====================================

    ============
    Description:
    ============

    You are given a 2D array coords of size n x 2, representing the coordinates
    of n points in an infinite Cartesian plane.

    Find twice the maximum area of a triangle with its corners at any three
    elements from coords, such that at least one side of this triangle is
    parallel to the x-axis or y-axis. Formally, if the maximum area of such a
    triangle is A, return 2 * A.

    If no such triangle exists, return -1.

    =====
    Note: that a triangle cannot have zero area.
    =====

    =========================================================
    FUNCTION: long long maxArea(vector<vector<int>>& coords);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: coords = [[1,1],[1,2],[3,2],[3,3]]
    Output: 2
    Explanation: The triangle shown in the image has a base 1 and height 2.
                 Hence its area is 1/2 * base * height = 1.


    --- Example 2 ---
    Input: coords = [[1,1],[2,2],[3,3]]
    Output: -1
    Explanation: The only possible triangle has corners (1, 1), (2, 2), and
                 (3, 3). None of its sides are parallel to the x-axis or the
                 y-axis.


    *** Constraints ***
    1 <= n == coords.length <= 10^5
    1 <= coords[i][0], coords[i][1] <= 10^6
    All coords[i] are unique.

*/

#include <climits>
#include <cstdlib>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 64.24% */
/* Space Beats: 64.67% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    long long maxArea(vector<vector<int>>& coords)
    {
        unordered_map<long long, pair<long long, long long>> umap_x;
        unordered_map<long long, pair<long long, long long>> umap_y;

        long long x_min = INT_MAX;
        long long x_max = INT_MIN;
        long long y_min = INT_MAX;
        long long y_max = INT_MIN;

        for (auto& entry : coords)
        {
            long long x = entry[0];
            long long y = entry[1];

            if (umap_x.find(x) == umap_x.end())
                umap_x[x] = {INT_MAX, INT_MIN};

            umap_x[x].first  = min(umap_x[x].first, y);  // Lowest y
            umap_x[x].second = max(umap_x[x].second, y); // Highest y

            if (umap_y.find(y) == umap_y.end())
                umap_y[y] = {INT_MAX, INT_MIN};

            umap_y[y].first  = min(umap_y[y].first, x);  // Leftmost x
            umap_y[y].second = max(umap_y[y].second, x); // Rightmost x

            x_max = max(x_max, x);
            x_min = min(x_min, x);
            y_max = max(y_max, y);
            y_min = min(y_min, y);
        }

        long long result = 0;

        for (auto& [x, point] : umap_x)
        {
            long long base   = abs(point.first - point.second);
            long long height = max(abs(x - x_max), abs(x - x_min));

            result = max(result, base * height);
        }

        for (auto& [y, point] : umap_y)
        {
            long long base   = abs(point.first - point.second);
            long long height = max(abs(y - y_max), abs(y - y_min));

            result = max(result, base * height);
        }

        return result == 0 ? -1 : result;
    }
};
