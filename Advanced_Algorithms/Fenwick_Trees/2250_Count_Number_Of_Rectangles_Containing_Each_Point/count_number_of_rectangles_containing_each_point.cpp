/*
    ==============
    === MEDIUM ===
    ==============

    ======================================================
    2250) Count Number of Rectangles Containing Each Point
    ======================================================

    ============
    Description:
    ============

    You are given a 2D integer array rectangles where rectangles[i] = [li, hi]
    indicates that ith rectangle has a length of li and a height of hi. You are
    also given a 2D integer array points where points[j] = [xj, yj] is a point
    with coordinates (xj, yj).

    The ith rectangle has its bottom-left corner point at the coordinates (0,
    0) and its top-right corner point at (li, hi).

    Return an integer array count of length points.length where count[j] is the
    number of rectangles that contain the jth point.

    The ith rectangle contains the jth point if 0 <= xj <= li and 0 <= yj <=
    hi. Note that points that lie on the edges of a rectangle are also
    considered to be contained by that rectangle.

    ====================================================================================================
    FUNCTION: vector<int> countRectangles(vector<vector<int>>& rectangles, vector<vector<int>>& points);
    ====================================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: rectangles = [[1,2],[2,3],[2,5]], points = [[2,1],[1,4]]
    Output: [2,1]
    Explanation: 
    The first rectangle contains no points.
    The second rectangle contains only the point (2, 1).
    The third rectangle contains the points (2, 1) and (1, 4).
    The number of rectangles that contain the point (2, 1) is 2.
    The number of rectangles that contain the point (1, 4) is 1.
    Therefore, we return [2, 1].

    --- Example 2 ---
    Input: rectangles = [[1,1],[2,2],[3,3]], points = [[1,3],[1,1]]
    Output: [1,3]
    Explanation:
    The first rectangle contains only the point (1, 1).
    The second rectangle contains only the point (1, 1).
    The third rectangle contains the points (1, 3) and (1, 1).
    The number of rectangles that contain the point (1, 3) is 1.
    The number of rectangles that contain the point (1, 1) is 3.
    Therefore, we return [1, 3].


    *** Constraints ***
    1 <= rectangles.length, points.length <= 5 * 10^4
    rectangles[i].length == points[j].length == 2
    1 <= li, xj <= 10^9
    1 <= hi, yj <= 100
    All the rectangles are unique.
    All the points are unique.

*/

#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats:  97.60% */
/* Space Beats: 100.00% */

/* Time  Complexity: O((N + M) * log(MAX_HEIGHT)) */
/* Space Complexity: O(M + MAX_HEIGHT)            */
class Sum_Fenwick { // 1-based
private:
    vector<long long> sum_fenwick;
    int n;

public:
    Sum_Fenwick(int n)
        : n(n), sum_fenwick(n + 1, 0)
    {}

    long long sum(int L, int R)
    {
        return sum(R) - sum(L - 1);
    }

    long long sum(int i)
    {
        long long sum = 0;

        while (i > 0)
        {
            sum += sum_fenwick[i];

            // Clear Last SET-bit
            i -= i & -i;
        }

        return sum;
    }


    void update(int idx, long long delta)
    {
        int i = idx;
        while (i <= n)
        {
            sum_fenwick[i] += delta;

            // Add Last SET-bit
            i += i & -i;
        }
    }
};

class Solution {
public:
    vector<int> countRectangles(vector<vector<int>>& rectangles, vector<vector<int>>& points)
    {
        const int N = rectangles.size();
        const int M = points.size();

        const int MAX_HEIGHT = 101;
        vector<int> result(M);
        
        Sum_Fenwick fenwick_tree(MAX_HEIGHT);
        
        // Create indices for points
        vector<int> point_indices(M);
        iota(point_indices.begin(), point_indices.end(), 0);
        
        // Sort point indices by x-coordinate in descending order
        sort(point_indices.begin(), point_indices.end(), [&](int a, int b) { 
             return points[a][0] > points[b][0]; 
         });
        
        // Sort rectangles by x-coordinate in descending order
        sort(rectangles.begin(), rectangles.end(), [](const auto& r1, const auto& r2) { 
             return r1[0] > r2[0]; 
         });
        

        int rectangle_idx = 0;
        for (int i = 0; i < M; i++)
        {
            int point_idx = point_indices[i];
            
            // Add ALL rectangles with x >= current point's x
            while (rectangle_idx < rectangles.size() && rectangles[rectangle_idx][0] >= points[point_idx][0])
            {
                fenwick_tree.update(rectangles[rectangle_idx][1] + 1, 1);
                ++rectangle_idx;
            }
            
            // Count rectangles with y >= point's y (and NOT just height > point's y)
            int total_added = rectangle_idx;
            int rectangles_with_height_less_than_point = fenwick_tree.sum(points[point_idx][1]);
            
            result[point_idx] = total_added - rectangles_with_height_less_than_point;
        }
        
        return result;
    }
};
