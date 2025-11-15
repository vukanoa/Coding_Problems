/*
    ============
    === EASY ===
    ============

    ==========================================================
    1886) Determine Whether Matrix Can be Obtained By Rotation
    ==========================================================

    ============
    Description:
    ============

    Given two n x n binary matrices mat and target, return true if it is
    possible to make mat equal to target by rotating mat in 90-degree
    increments, or false otherwise.

    ===================================================================================
    FUNCTION: bool findRotation(vector<vector<int>>& mat, vector<vector<int>>& target);
    ===================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: mat = [[0,1],[1,0]], target = [[1,0],[0,1]]
    Output: true
    Explanation: We can rotate mat 90 degrees clockwise to make mat equal
                 target.

    --- Example 2 ---
    Input: mat = [[0,1],[1,1]], target = [[1,0],[0,1]]
    Output: false
    Explanation: It is impossible to make mat equal to target by rotating mat.

    --- Example 3 ---
    Input: mat = [[0,0,0],[0,1,0],[1,1,1]], target = [[1,1,1],[0,1,0],[0,0,0]]
    Output: true
    Explanation: We can rotate mat 90 degrees clockwise two times to make mat
                 equal target.


    *** Constraints ***
    n == mat.length == target.length
    n == mat[i].length == target[i].length
    1 <= n <= 10
    mat[i][j] and target[i][j] are either 0 or 1.

*/

#include <cstring>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  23.79% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(1)   */
class Solution {
public:
    bool findRotation(vector<vector<int>>& mat, vector<vector<int>>& target)
    {
        bool rotation_matches[4];

        // "true" == 0x01
        memset(rotation_matches, true, sizeof(rotation_matches));

        const int N = mat.size();

        for (int row = 0; row < N; row++)
        {
            for (int col = 0; col < N; col++)
            {
                if (mat[row][col] != target[    row    ][    col    ]) rotation_matches[0] = false; // 0 degrees
                if (mat[row][col] != target[N - 1 - col][    row    ]) rotation_matches[1] = false; // 90 degrees
                if (mat[row][col] != target[N - 1 - row][N - 1 - col]) rotation_matches[2] = false; // 180 degrees
                if (mat[row][col] != target[    col    ][N - 1 - row]) rotation_matches[3] = false; // 270 degrees
            }
        }

        return rotation_matches[0]
            || rotation_matches[1]
            || rotation_matches[2]
            || rotation_matches[3];
    }
};


