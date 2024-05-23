#include <iostream>
#include <vector>

/*
    ============
    === EASY ===
    ============

    ====================================
    1232) Check If It Is a Straight Line
    ====================================

    ============
    Description:
    ============

    You are given an array coordinates, coordinates[i] = [x, y], where [x, y]
    represents the coordinate of a point. Check if these points make a straight
    line in the XY plane.

    ===================================================================
    FUNCTION: bool checkStraightLine(vector<vector<int>>& coordinates);
    ===================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: coordinates = [[1,2],[2,3],[3,4],[4,5],[5,6],[6,7]]
    Output: true

    --- Example 2 ---
    Input: coordinates = [[1,1],[2,2],[3,4],[4,5],[5,6],[7,7]]
    Output: false


    *** Constraints ***
    2 <= coordinates.length <= 1000
    coordinates[i].length == 2
    -10^4 <= coordinates[i][0], coordinates[i][1] <= 10^4
    coordinates contains no duplicate point.

*/

/* Time  Beats: 62.56% */
/* Space Beats: 19.84% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool checkStraightLine(vector<vector<int>>& coordinates)
    {
        if(coordinates.size() == 2)
            return true;

        int x0 = coordinates[0][0];
        int x1 = coordinates[1][0];
        int y0 = coordinates[0][1];
        int y1 = coordinates[1][1];
        int dx = x1 - x0 , dy = y1 - y0;

        for(int i = 2 ; i < coordinates.size() ; i++)
        {
            int x = coordinates[i][0];
            int y = coordinates[i][1];

            if(dy * (x - x0) != dx * (y - y0))
                return false;
        }

        return true;
    }
};
