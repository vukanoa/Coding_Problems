/*
    ==============
    === MEDIUM ===
    ==============

    ============================================
    1039) Minimum Score Triangulation of Polygon
    ============================================

    ============
    Description:
    ============

    You have a convex n-sided polygon where each vertex has an integer value.
    You are given an integer array values where values[i] is the value of the
    ith vertex in clockwise order.

    Polygon triangulation is a process where you divide a polygon into a set of
    triangles and the vertices of each triangle must also be vertices of the
    original polygon. Note that no other shapes other than triangles are
    allowed in the division. This process will result in n - 2 triangles.

    You will triangulate the polygon. For each triangle, the weight of that
    triangle is the product of the values at its vertices. The total score of
    the triangulation is the sum of these weights over all n - 2 triangles.

    Return the minimum possible score that you can achieve with some
    triangulation of the polygon.

    =========================================================
    FUNCTION: int minScoreTriangulation(vector<int>& values);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: values = [1,2,3]
    Output: 6
    Explanation: The polygon is already triangulated, and the score of the only
                 triangle is 6.

    --- Example 2 ---
    Input: values = [3,7,4,5]
    Output: 144
    Explanation: There are two triangulations, with possible scores:
                 3*7*5 + 4*5*7 = 245, or 3*4*5 + 3*4*7 = 144.
                 The minimum score is 144.

    --- Example 3 ---
    Input: values = [1,3,1,4,1,5]
    Output: 13
    Explanation: The minimum score triangulation is:
                 1*1*3 + 1*1*4 + 1*1*5 + 1*1*1 = 13.


    *** Constraints ***
    n == values.length
    3 <= n <= 50
    1 <= values[i] <= 100

*/

#include <algorithm>
#include <climits>
#include <cstring>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO
    (Memoization)

*/

/* Time  Beats: 100.00% */
/* Space Beats:  98.27% */

/* Time  Complexity: O(N^3) */
/* Space Complexity: O(N^2) */
class Solution_Memoization {
public:
    int memo[50][50] = {};

    int minScoreTriangulation(vector<int>& values)
    {
        memset(memo, -1, sizeof(memo));
        return solve(values, 0, 0, 0);
    }

    int solve(vector<int>& values, int i, int j, int result)
    {
        const int N = values.size();

        if (j == 0)
            j = N - 1;

        if (memo[i][j] != -1)
            return memo[i][j];

        for (int k = i+1; k < j; k++)
        {
            int left_subpolygon_score  = solve(values, i, k, 0);
            int right_subpolygon_score = solve(values, k, j, 0);
            int triangle_score         = values[i] * values[k] * values[j];

            int total_score = left_subpolygon_score + triangle_score + right_subpolygon_score;

            if (result == 0)
                result = INT_MAX;

            result = min(result, total_score);
        }

        return memo[i][j] = result;
    }
};


/*
    ------------
    --- IDEA ---
    ------------

    TODO
    (Tabulation)

*/

/* Time  Beats: 100.00% */
/* Space Beats:  70.70% */

/* Time  Complexity: O(N^3) */
/* Space Complexity: O(N^2) */
class Solution_Bottom_Up_Tabulation {
public:
    int minScoreTriangulation(vector<int>& values)
    {
        const int N = values.size();
        vector<vector<int>> dp(N, vector<int>(N, 0));

        for (int i = N-1; i >= 0; i--)
        {
            for (int j = i+1; j < N; j++)
            {
                int best_score = INT_MAX;

                for (int k = i+1; k < j; k++)
                {
                    long long left_subpolygon_score  = dp[i][k];
                    long long right_subpolygon_score = dp[k][j];
                    long long triangle_score         = 1LL * values[i] * values[k] * values[j];

                    long long total_score = left_subpolygon_score + triangle_score + right_subpolygon_score;

                    best_score = min(best_score, static_cast<int>(total_score));
                }

                if (best_score != INT_MAX)
                    dp[i][j] = best_score;
            }
        }

        return dp[0][N - 1];
    }
};
