/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    2017) Grid Game
    ===========================

    ============
    Description:
    ============

    You are given a 0-indexed 2D array grid of size 2 x n, where grid[r][c]
    represents the number of points at position (r, c) on the matrix. Two
    robots are playing a game on this matrix.

    Both robots initially start at (0, 0) and want to reach (1, n-1). Each
    robot may only move to the right ((r, c) to (r, c + 1)) or down ((r, c) to
    (r + 1, c)).

    At the start of the game, the first robot moves from (0, 0) to (1, n-1),
    collecting all the points from the cells on its path. For all cells (r, c)
    traversed on the path, grid[r][c] is set to 0. Then, the second robot moves
    from (0, 0) to (1, n-1), collecting the points on its path. Note that their
    paths may intersect with one another.

    The first robot wants to minimize the number of points collected by the
    second robot. In contrast, the second robot wants to maximize the number of
    points it collects. If both robots play optimally, return the number of
    points collected by the second robot.

    =======================================================
    FUNCTION: long long gridGame(vector<vector<int>>& mat);
    =======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    +-----+-----+-----+              +-----+-----+-----+
    |  2  |  5  |  4  |              |  0  |  0  |  4  |
    +-----+-----+-----+     ==>      +-----+-----+-----+
    |  1  |  5  |  1  |              |  1  |  0  |  0  |
    +-----+-----+-----+              +-----+-----+-----+

    Input: grid = [[2,5,4],[1,5,1]]
    Output: 4
    Explanation: The optimal path taken by the first robot is shown in red, and
                 the optimal path taken by the second robot is shown in blue.
                 The cells visited by the first robot are set to 0.  The second
                 robot will collect 0 + 0 + 4 + 0 = 4 points.


    --- Example 2 ---
    +-----+-----+-----+              +-----+-----+-----+
    |  3  |  3  |  1  |              |  0  |  3  |  1  |
    +-----+-----+-----+     ==>      +-----+-----+-----+
    |  8  |  5  |  2  |              |  0  |  0  |  0  |
    +-----+-----+-----+              +-----+-----+-----+

    Input: grid = [[3,3,1],[8,5,2]]
    Output: 4
    Explanation: The optimal path taken by the first robot is shown in red, and
                 the optimal path taken by the second robot is shown in blue.
                 The cells visited by the first robot are set to 0.  The second
                 robot will collect 0 + 3 + 1 + 0 = 4 points.


    --- Example 3 ---
    +-----+-----+-----+-----+              +-----+-----+-----+-----+
    |  1  |  3  |  1  | 15  |              |  0  |  0  |  0  |  0  |
    +-----+-----+-----+-----+     ==>      +-----+-----+-----+-----+
    |  1  |  3  |  3  |  1  |              |  1  |  3  |  3  |  0  |
    +-----+-----+-----+-----+              +-----+-----+-----+-----+

    Input: grid = [[1,3,1,15],[1,3,3,1]]
    Output: 7
    Explanation: The optimal path taken by the first robot is shown in red, and
                 the optimal path taken by the second robot is shown in blue.
                 The cells visited by the first robot are set to 0.  The second
                 robot will collect 0 + 1 + 3 + 3 + 0 = 7 points.


    *** Constraints ***
    grid.length == 2
    n == grid[r].length
    1 <= n <= 5 * 104
    1 <= grid[r][c] <= 105

*/

#include <climits>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Since there are only two rows and since we want to MINIMIZE the maximum
    path for the second robot, we can do that effectively in one pass, after
    we've precalculated some information.

    It is VERY important to notice the following:

        Once the first robot goes DOWN, the second robot can have EITHER the
        remaining(not taken by the first robot) top elements summed OR the
        bottom elements that were not taken.

    The easy way to precalculate such a thing is to use a prefix_sum.

    We do that, separately for both rows.

    It is also important to notice that the second robot will NEVER get to
    have elements at mat[0][0], and mat[1][n-1]. Those will ALWAYS be taken by
    robot one.


    Consider this example:
    +-----+-----+-----+-----+
    |  1  |  5  |  2  |  7  |
    +-----+-----+-----+-----+
    |  4  |  5  |  8  |  3  |
    +-----+-----+-----+-----+

    prefix_0:
        +-----+-----+-----+-----+
        |  1  |  6  |  8  | 15  |
        +-----+-----+-----+-----+

    prefix_1:
        +-----+-----+-----+-----+
        |  4  |  9  | 17  | 20  |
        +-----+-----+-----+-----+

    for each 'i', SECOND robot can only take "highlighted" cells(with '#')
    
        i = 0
            +-----+#####+-####+#####+
            |  1  #  5  #  2  #  7  #  <--- Either top '#' cells(none here),or
            +-----+#####+#####+#####+
            |  4  |  5  |  8  |  3  |  <--- bot '#' cells
            +-----+-----+-----+-----+

    
        i = 1
            +-----+-----+#####+#####+
            |  1  #  5  #  2  #  7  #   <--- Either top '#' cells, or
            +#####+-----+#####+#####+
            #  4  #  5  #  8  |  3  |   <--- bot '#' cells
            +#####+-----+-----+-----+

    
        i = 2
            +-----+-----+-----+#####+
            |  1  #  5  |  2  #  7  #   <--- Either top '#' cells, or
            +#####+#####+-----+#####+
            #  4  #  5  #  8  |  3  |   <--- bot '#' cells
            +#####+#####+-----+-----+

    
        i = 3
            +-----+-----+-----+-----+
            |  1  #  5  |  2  |  7  |   <--- Either top '#' cells(none here),or
            +#####+#####+#####+-----+
            #  4  #  5  #  8  #  3  |   <--- bot '#' cells
            +#####+#####+#####+-----+



        In other words:

            i = 0:
                max(14, 0) ----------------------------
                                                      |
            i = 1:                                    |
                max(9, 4) ----------------------------|      
                                                      |----> min of these: 9
            i = 2:                                    |
                max(7, 9) ----------------------------|
                                                      |
            i = 3:                                    |
                max(0,17) -----------------------------


    And that is the result.

*/

/* Time  Beats: 64.71% */
/* Space Beats: 47.06% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    long long gridGame(vector<vector<int>>& mat)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        const int N = mat[0].size();

        vector<long long> prefix_0(mat[0].begin(), mat[0].end());
        vector<long long> prefix_1(mat[1].begin(), mat[1].end());

        partial_sum(prefix_0.begin(), prefix_0.end(), prefix_0.begin());
        partial_sum(prefix_1.begin(), prefix_1.end(), prefix_1.begin());

        long long result = prefix_0[N-1] - mat[0][0];
        for (int i = 1; i < N; i++)
            result = min(result, max(prefix_0[N-1] - prefix_0[i], prefix_1[i-1]));

        return result;
    }
};
