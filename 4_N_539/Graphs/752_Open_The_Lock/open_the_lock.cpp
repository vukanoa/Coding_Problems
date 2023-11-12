#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    752) Open The Lock
    ===========================

    ============
    Description:
    ============

    You have a lock in front of you with 4 circular wheels. Each wheel has 10
    slots: '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'. The wheels can
    rotate freely and wrap around: for example we can turn '9' to be '0', or
    '0' to be '9'. Each move consists of turning one wheel one slot.

    The lock initially starts at '0000', a string representing the state of the
    4 wheels.

    You are given a list of deadends dead ends, meaning if the lock displays
    any of these codes, the wheels of the lock will stop turning and you will
    be unable to open it.

    Given a target representing the value of the wheels that will unlock the
    lock, return the minimum total number of turns required to open the lock,
    or -1 if it is impossible.

    ================================================================
    FUNCTION: int openLock(vector<string>& deadends, string target);
    ================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: deadends = ["0201","0101","0102","1212","2002"], target = "0202"
    Output: 6
    Explanation:
    A sequence of valid moves would be "0000" -> "1000" -> "1100" -> "1200" ->
    "1201" -> "1202" -> "0202".  Note that a sequence like "0000" -> "0001" ->
    "0002" -> "0102" -> "0202" would be invalid, because the wheels of the lock
    become stuck after the display becomes the dead end "0102".


    --- Example 2 ---
    Input: deadends = ["8888"], target = "0009"
    Output: 1
    Explanation: We can turn the last wheel in reverse to move from "0000" ->
    "0009"


    --- Example 3 ---
    Input: deadends =
    ["8887","8889","8878","8898","8788","8988","7888","9888"], target = "8888"
    Output: -1
    Explanation: We cannot reach the target without getting stuck.



    *** Constraints ***
    1 <= deadends.length <= 500
    deadends[i].length == 4
    target.length == 4
    target will not be in the list deadends.
    target and deadends[i] consist of digits only.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 85.85% */
/* Space Beats: 69.83% */

/* Time  Complexity: O(n * 10) */ // n == 4 --> 10 * 10 * 10 * 10 = 10000
/* Space Complexity: O(n * 10) */ // n == 4 --> 10 * 10 * 10 * 10 = 10000
class Solution {
public:
    int openLock(vector<string> &deadends, string target)
    {
        std::unordered_set<std::string> visited(deadends.begin(), deadends.end());

        if (visited.find("0000") != visited.end())
            return -1;
        visited.insert("0000");

        std::queue<std::string> wheel_queue;
        wheel_queue.push("0000");

        /* BFS */
        int result = 0;
        while (!wheel_queue.empty())
        {
            int level_size = wheel_queue.size();
            while (level_size--)
            {
                std::string current_wheel = wheel_queue.front();
                wheel_queue.pop();

                if (current_wheel == target)
                    return result;

                std::string up;
                std::string down;
                for (int i = 0; i < 4; i++)
                {
                    down = up = current_wheel;

                    up[i]   = (up[i]   == '9' ? '0' : up[i]   + 1);
                    down[i] = (down[i] == '0' ? '9' : down[i] - 1);

                    if (visited.find(up) == visited.end())
                    {
                        wheel_queue.push(up);
                        visited.insert(up);
                    }

                    if (visited.find(down) == visited.end())
                    {
                        wheel_queue.push(down);
                        visited.insert(down);
                    }
                }
            }

            result++;
        }

        return -1;
    }
};
