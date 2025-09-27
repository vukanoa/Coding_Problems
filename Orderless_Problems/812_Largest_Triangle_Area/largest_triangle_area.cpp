/*
    ============
    === EASY ===
    ============

    ===========================
    812) Largest Triangle Area
    ===========================

    ============
    Description:
    ============

    Given an array of points on the X-Y plane points where points[i] = [xi, yi]
    return the area of the largest triangle that can be formed by any three
    different points. Answers within 10-5 of the actual answer will be accepted

    ==================================================================
    FUNCTION: double largestTriangleArea(vector<vector<int>>& points);
    ==================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: points = [[0,0],[0,1],[1,0],[0,2],[2,0]]
    Output: 2.00000
    Explanation: The five points are shown in the above figure. The red
                 triangle is the largest.

    --- Example 2 ---
    Input: points = [[1,0],[0,0],[0,1]]
    Output: 0.50000


    *** Constraints ***
    3 <= points.length <= 50
    -50 <= xi, yi <= 50
    All the given points are unique.

*/

#include <cstdlib>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    If you know how to calculate the area of a triangle given the points, then
    you're done -- You can just Brute Force through all the combinations and
    return the maximum area.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  9.16% */

/* Time  Complexity: O(N^3) */
/* Space Complexity: O(1)   */
class Solution {
public:
    double largestTriangleArea(vector<vector<int>>& points)
    {
        const int N = points.size();
        double result = 0.0;

        for (int i = 0; i < N-2; i++)
        {
            for (int j = i+1; j < N-1; j++)
            {
                for (int k = j+1; k < N; k++)
                {
                    result = max(result, area_of_triangle(points[i], points[j], points[k]));
                }
            }
        }

        return result;
    }

private:
    double area_of_triangle(vector<int>& A, vector<int>& B, vector<int>& C)
    {
        double area = 0.5 * abs(A[0] * (B[1] - C[1]) +
                                B[0] * (C[1] - A[1]) +
                                C[0] * (A[1] - B[1]));

        return area;
    }
};
