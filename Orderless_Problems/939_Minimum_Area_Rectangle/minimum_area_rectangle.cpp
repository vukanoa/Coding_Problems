/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    939) Minimum Area Recangle
    ===========================

    ============
    Description:
    ============

    You are given an array of points in the X-Y plane points where points[i] =
    [xi, yi].

    Return the minimum area of a rectangle formed from these points, with sides
    parallel to the X and Y axes. If there is not any such rectangle, return 0.

    =======================================================
    FUNCTION: int minAreaRect(vector<vector<int>>& points);
    =======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: points = [[1,1],[1,3],[3,1],[3,3],[2,2]]
    Output: 4

    --- Example 2 ---
    Input: points = [[1,1],[1,3],[3,1],[3,3],[4,1],[4,3]]
    Output: 2


    *** Constraints ***
    1 <= points.length <= 500
    points[i].length == 2
    0 <= xi, yi <= 4 * 10^4
    All the given points are unique.

*/

#include <climits>
#include <cstdlib>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 67.62% */
/* Space Beats: 32.25% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(N)   */
class Solution {
public:
    int minAreaRect(vector<vector<int>>& points)
    {
        const int N = points.size();

        unordered_map<int, unordered_set<int>> umap;
        
        for (const auto& point: points)
        {
            const int& x = point[0];
            const int& y = point[1];

            umap[x].insert(y);
        }

        int minimum_area = INT_MAX;
        
        for (int i = 0; i < N; i++)
        {
            for (int j = i+1; j < N; j++)
            {
                int x1 = points[i][0];
                int y1 = points[i][1];

                int x2 = points[j][0];
                int y2 = points[j][1];
                
                if (x1 != x2 && y1 != y2)
                {
                    if (umap[x1].find(y2) != umap[x1].end()
                        && 
                        umap[x2].find(y1) != umap[x2].end())
                    {
                        minimum_area = min(minimum_area, abs(x1 - x2) *
                                                         abs(y1 - y2));
                    }
                }
            }
        }

        return minimum_area != INT_MAX ? minimum_area : 0;
    }
};
