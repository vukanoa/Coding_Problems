#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    =============================
    1041) Robot Bounded in Circle
    =============================

    ============
    Description:
    ============

    On an infinite plane, a robot initially stands at (0, 0) and faces north.
    Note that:

        The north direction is the positive direction of the y-axis.  The south
        direction is the negative direction of the y-axis.  The east direction
        is the positive direction of the x-axis.  The west direction is the
        negative direction of the x-axis.

    The robot can receive one of three instructions:

        "G": go straight 1 unit.  "L": turn 90 degrees to the left (i.e.,
        anti-clockwise direction).  "R": turn 90 degrees to the right (i.e.,
        clockwise direction).

    The robot performs the instructions given in order, and repeats them
    forever.

    Return true if and only if there exists a circle in the plane such that the
    robot never leaves the circle.

    ===================================================
    FUNCTION: bool isRobotBounded(string instructions);
    ===================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: instructions = "GGLLGG"
    Output: true
    Explanation: The robot is initially at (0, 0) facing the north direction.
    "G": move one step. Position: (0, 1). Direction: North.
    "G": move one step. Position: (0, 2). Direction: North.
    "L": turn 90 degrees anti-clockwise. Position: (0, 2). Direction: West.
    "L": turn 90 degrees anti-clockwise. Position: (0, 2). Direction: South.
    "G": move one step. Position: (0, 1). Direction: South.
    "G": move one step. Position: (0, 0). Direction: South.
    Repeating the instructions, the robot goes into the cycle: (0, 0) --> (0,
    1) --> (0, 2) --> (0, 1) --> (0, 0).  Based on that, we return true.


    --- Example 2 ---
    Input: instructions = "GG"
    Output: false
    Explanation: The robot is initially at (0, 0) facing the north direction.
    "G": move one step. Position: (0, 1). Direction: North.
    "G": move one step. Position: (0, 2). Direction: North.
    Repeating the instructions, keeps advancing in the north direction and does
    not go into cycles.  Based on that, we return false.


    --- Example 3 ---
    Input: instructions = "GL"
    Output: true
    Explanation: The robot is initially at (0, 0) facing the north direction.
    "G": move one step. Position: (0, 1). Direction: North.
    "L": turn 90 degrees anti-clockwise. Position: (0, 1). Direction: West.
    "G": move one step. Position: (-1, 1). Direction: West.
    "L": turn 90 degrees anti-clockwise. Position: (-1, 1). Direction: South.
    "G": move one step. Position: (-1, 0). Direction: South.
    "L": turn 90 degrees anti-clockwise. Position: (-1, 0). Direction: East.
    "G": move one step. Position: (0, 0). Direction: East.
    "L": turn 90 degrees anti-clockwise. Position: (0, 0). Direction: North.
    Repeating the instructions, the robot goes into the cycle: (0, 0) --> (0,
    1) --> (-1, 1) --> (-1, 0) --> (0, 0).  Based on that, we return true.


    *** Constraints ***
    1 <= instructions.length <= 100
    instructions[i] is 'G', 'L' or, 'R'.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 40.22% */
/* Space Beats: 76.22% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool isRobotBounded(std::string instructions)
    {
        // Compass                                      NORTH   WEST     SOUTH    EAST}
        std::vector<std::pair<int, int>> directions = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};

        int facing = 0;
        int x = 0;
        int y = 0;

        for (int i = 0; i < 4; i++)
        {
            for (char& instr : instructions)
            {
                if (instr == 'G')
                {
                    x += directions[facing].first;
                    y += directions[facing].second;
                }
                else if (instr == 'L')
                    facing = (facing + 1) % 4;
                else if (instr == 'R')
                    facing = ((facing - 1) < 0) ? 3 : facing - 1;
            }
        }

        return x == 0 && y == 0;
    }
};
