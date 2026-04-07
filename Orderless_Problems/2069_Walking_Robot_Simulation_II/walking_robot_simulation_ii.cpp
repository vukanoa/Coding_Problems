/*
    ==============
    === MEDIUM ===
    ==============

    =================================
    2069) Walking Robot Simulation II
    =================================

    ============
    Description:
    ============


    A width x height grid is on an XY-plane with the bottom-left cell at (0, 0)
    and the top-right cell at (width - 1, height - 1). The grid is aligned with
    the four cardinal directions ("North", "East", "South", and "West"). A
    robot is initially at cell (0, 0) facing direction "East".

    The robot can be instructed to move for a specific number of steps. For
    each step, it does the following.

        + Attempts to move forward one cell in the direction it is facing.

        + If the cell the robot is moving to is out of bounds, the robot
          instead turns 90 degrees counterclockwise and retries the step.

    After the robot finishes moving the number of steps required, it stops and
    awaits the next instruction.

    Implement the Robot class:

    Robot(int width, int height) Initializes the width x height grid with the
    robot at (0, 0) facing "East".

    + void step(int num) Instructs the robot to move forward num steps.

    + int[] getPos()     Returns the current cell the robot is at, as an array
                         of length 2, [x, y].

    + String getDir()    Returns the current direction of the robot, "North",
                         "East", "South", or "West".

    ===============================
    CLASS:
    class Robot {
    public:
        Robot(int width, int height)
        {
        }

        void step(int num)
        {
        }

        vector<int> getPos()
        {
        }
        
        string getDir()
        {
        }
    };
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input
    ["Robot", "step", "step", "getPos", "getDir", "step", "step", "step", "getPos", "getDir"]
    [[6, 3], [2], [2], [], [], [2], [1], [4], [], []]
    Output
    [null, null, null, [4, 0], "East", null, null, null, [1, 2], "West"]

    Explanation
    Robot robot = new Robot(6, 3); // Initialize the grid and the robot at (0, 0) facing East.
    robot.step(2);  // It moves two steps East to (2, 0), and faces East.
    robot.step(2);  // It moves two steps East to (4, 0), and faces East.
    robot.getPos(); // return [4, 0]
    robot.getDir(); // return "East"
    robot.step(2);  // It moves one step East to (5, 0), and faces East.
                    // Moving the next step East would be out of bounds, so it turns and faces North.
                    // Then, it moves one step North to (5, 1), and faces North.
    robot.step(1);  // It moves one step North to (5, 2), and faces North (not West).
    robot.step(4);  // Moving the next step North would be out of bounds, so it turns and faces West.
                    // Then, it moves four steps West to (1, 2), and faces West.
    robot.getPos(); // return [1, 2]
    robot.getDir(); // return "West"



    *** Constraints ***
    2 <= width, height <= 100
    1 <= num <= 10^5
    At most 10^4 calls in total will be made to step, getPos, and getDir.

*/

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 62.07% */
/* Space Beats: 76.72% */

/* Time  Complexity: O(ROWS + COLS) */
/* Space Complexity: O(1)           */
class Robot {
public:
    Robot(int width, int height)
        : COLS(width), ROWS(height), x(0), y(0), direction(0)
    {
        perimeter = 2 * COLS + 2 * (ROWS - 2);
    }

    void step(int num)
    {
        if (num % perimeter == 0 && x == 0 && y == 0)
            direction = 3; // South

        num %= perimeter;

        while (num > 0)
        {
            int steps;
            switch (direction)
            {
                /********/
                /* East */
                /********/
                case 0:
                    steps = min(num, COLS-1 - x);

                    x   += steps;
                    num -= steps;
                    break;

                /*********/
                /* North */
                /*********/
                case 1:
                    steps = min(num, ROWS-1 - y);

                    y   += steps;
                    num -= steps;
                    break;


                /********/
                /* West */
                /********/
                case 2:
                    steps = min(num, x);

                    x   -= steps;
                    num -= steps;
                    break;

                /*********/
                /* South */
                /*********/
                case 3:
                    steps = min(num, y);

                    y   -= steps;
                    num -= steps;
                    break;
            }

            if (num > 0)
                direction = (direction + 1) % 4;
        }
    }

    vector<int> getPos()
    {
        return {x, y};
    }
    
    string getDir()
    {
        if (direction == 0) return "East";
        if (direction == 1) return "North";
        if (direction == 2) return "West";

        return "South";
    }

private:
    int x;
    int y;

    int ROWS;
    int COLS;

    int perimeter;
    int direction;
};
