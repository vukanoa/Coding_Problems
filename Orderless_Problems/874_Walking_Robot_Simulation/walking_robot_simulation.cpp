#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

/*
    ==============
    === MEDIUM ===
    ==============

    =============================
    874) Walking Robot Simulation
    =============================

    ============
    Description:
    ============

    A robot on an infinite XY-plane starts at point (0, 0) facing north. The
    robot receives an array of integers commands, which represents a sequence
    of moves that it needs to execute. There are only three possible types of
    instructions the robot can receive:

        -2: Turn left 90 degrees.
        -1: Turn right 90 degrees.
        1 <= k <= 9: Move forward k units, one unit at a time.

    Some of the grid squares are obstacles. The ith obstacle is at grid point
    obstacles[i] = (xi, yi). If the robot runs into an obstacle, it will stay
    in its current location (on the block adjacent to the obstacle) and move
    onto the next command.

    Return the maximum squared Euclidean distance that the robot reaches at any
    point in its path (i.e. if the distance is 5, return 25).

    Note:



    =====
    Note: There can be an obstacle at (0, 0). If this happens, the robot will
          ignore the obstacle until it has moved off the origin. However, it
          will be unable to return to (0, 0) due to the obstacle.

          North means +Y direction.
          East means  +X direction.
          South means -Y direction.
          West means  -X direction.
    =====

    ==============================================================================
    FUNCTION: int robotSim(vector<int>& commands, vector<vector<int>>& obstacles);
    ==============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: commands = [4,-1,3], obstacles = []
    Output: 25
    Explanation:
    The robot starts at (0, 0):
        Move north 4 units to (0, 4).
        Turn right.
        Move east 3 units to (3, 4).
    The furthest point the robot ever gets from the origin is (3, 4), which
    squared is 32 + 42 = 25 units away.


    --- Example 2 ---
    Input: commands = [4,-1,4,-2,4], obstacles = [[2,4]]
    Output: 65
    Explanation:
    The robot starts at (0, 0):
        Move north 4 units to (0, 4).
        Turn right.
        Move east 1 unit and get blocked by the obstacle at (2, 4), robot is at (1, 4).
        Turn left.
        Move north 4 units to (1, 8).
    The furthest point the robot ever gets from the origin is (1, 8), which
    squared is 12 + 82 = 65 units away.


    --- Example 3 ---
    Input: commands = [6,-1,-1,6], obstacles = [[0,0]]
    Output: 36
    Explanation:
    The robot starts at (0, 0):
        Move north 6 units to (0, 6).
        Turn right.
        Turn right.
        Move south 5 units and get blocked by the obstacle at (0,0), robot is at (0, 1).
    The furthest point the robot ever gets from the origin is (0, 6), which
    squared is 62 = 36 units away.


    *** Constraints ***
    1 <= commands.length <= 10^4
    commands[i] is either -2, -1, or an integer in the range [1, 9].
    0 <= obstacles.length <= 10^4
    -3 * 10^4 <= xi, yi <= 3 * 10^4
    The answer is guaranteed to be less than 2^31.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

// N - number of commands
// M - number of obstacles

/* Time  Beats: 51.99% */
/* Space Beats:  5.17% */

/* Time  Complexity: O(N + M*logM) */
/* Space Complexity: O(M)          */
class Solution {
public:
    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles)
    {
        unordered_map<int, set<int>> XobSet;
        unordered_map<int, set<int>> YobSet;

        XobSet.reserve(10000);
        YobSet.reserve(10000);

        for (auto& ob: obstacles)
        {
            int x = ob[0];
            int y = ob[1];

            XobSet[x].insert(y);
            YobSet[y].insert(x);
        }

        const int dir[4][2] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};

        int x = 0;
        int y = 0;

        int dx = 0;
        int dy = 1;

        int face  = 0;
        int maxD2 = 0;

        for (int c: commands)
        {
            switch(c)
            {
                case -2:
                    face = (face+1) % 4;
                    dx   = dir[face][0];
                    dy   = dir[face][1];
                    break;

                case -1:
                    face = (face+3)%4;
                    dx   = dir[face][0];
                    dy   = dir[face][1];
                    break;

                default:
                    switch(face)
                    {
                        case 0: { // Up
                            auto it = upper_bound(XobSet[x].begin(), XobSet[x].end(), y);

                            if (it != XobSet[x].end() && *it <= y+c)
                                y= *it - 1;
                            else
                                y += c;
                            break;
                        }
                        case 1: { // Left
                            auto it = upper_bound(YobSet[y].rbegin(), YobSet[y].rend(), x, greater<>());
                            if (it != YobSet[y].rend() && *it >= x-c)
                                x = *it + 1;
                            else
                                x -= c;

                            break;
                        }
                        case 2: { // Down
                            auto it = upper_bound(XobSet[x].rbegin(), XobSet[x].rend(), y, greater<>());

                            if (it != XobSet[x].rend() && *it >= y-c)
                                y = *it + 1;
                            else
                                y -= c;

                            break;
                        }
                        case 3: { // Right
                            auto it = upper_bound(YobSet[y].begin(), YobSet[y].end(), x);

                            if (it != YobSet[y].end() && *it <= x+c)
                                x = *it - 1;
                            else
                                x += c;

                            break;
                        }
                    }

                    maxD2 = max(maxD2, x*x + y*y);
                }
        }

        return maxD2;
    }
};
