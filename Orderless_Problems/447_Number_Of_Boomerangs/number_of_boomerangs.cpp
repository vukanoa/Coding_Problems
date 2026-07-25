/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    447) Number of Boomerangs
    ===========================

    ============
    Description:
    ============

    You are given n points in the plane that are all distinct, where
    points[i] = [xi, yi]. A boomerang is a tuple of points (i, j, k) such that
    the distance between i and j equals the distance between i and k (the order
    of the tuple matters).

    Return the number of boomerangs.

    ==============================================================
    FUNCTION: int numberOfBoomerangs(vector<vector<int>>& points);
    ==============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: points = [[0,0],[1,0],[2,0]]
    Output: 2
    Explanation: The two boomerangs are [[1,0],[0,0],[2,0]] and [[1,0],[2,0],[0,0]].

    --- Example 2 ---
    Input: points = [[1,1],[2,2],[3,3]]
    Output: 2

    --- Example 3 ---
    Input: points = [[1,1]]
    Output: 0


    *** Constraints ***
    n == points.length
    1 <= n <= 500
    points[i].length == 2
    -10^4 <= xi, yi <= 10^4
    All the points are unique.

*/

#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 54.33% */
/* Space Beats: 52.92% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(N)   */
class Solution {
public:
    int numberOfBoomerangs(vector<vector<int>>& points)
    {
        const int N = points.size();
        int result = 0;

        for (int i = 0; i < N; i++)
        {
            unordered_map<int, int> umap;

            for (int j = 0; j < N; j++)
            {
                if (i == j)
                    continue;

                int dx = points[i][0] - points[j][0];
                int dy = points[i][1] - points[j][1];

                int distance_squared = dx * dx + dy * dy;
                umap[distance_squared]++;
            }

            for (auto& [dist, count] : umap)
                result += count * (count - 1);
        }

        return result;
    }
};
