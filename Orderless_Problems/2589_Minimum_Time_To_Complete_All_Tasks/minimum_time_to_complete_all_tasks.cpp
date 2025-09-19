/*
    ============
    === HARD ===
    ============

    ========================================
    2589) Minimum Time to Complete All Tasks
    ========================================

    ============
    Description:
    ============

    There is a computer that can run an unlimited number of tasks at the same
    time. You are given a 2D integer array tasks where:

        tasks[i] = [starti, endi, durationi]

        indicates that the ith task should run for a total of durationi seconds
        (not necessarily continuous) within the inclusive time range:

            [starti, endi].

    You may turn on the computer only when it needs to run a task. You can also
    turn it off if it is idle.

    Return the minimum time during which the computer should be turned on to
    complete all tasks.

    ==========================================================
    FUNCTION: int findMinimumTime(vector<vector<int>>& tasks);
    ==========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: tasks = [[2,3,1],[4,5,1],[1,5,2]]
    Output: 2
    Explanation:
    - The first task can be run in the inclusive time range [2, 2].
    - The second task can be run in the inclusive time range [5, 5].
    - The third task can be run in the two inclusive time ranges [2, 2] and [5, 5].
    The computer will be on for a total of 2 seconds.

    --- Example 2 ---
    Input: tasks = [[1,3,2],[2,5,3],[5,6,2]]
    Output: 4
    Explanation:
    - The first task can be run in the inclusive time range [2, 3].
    - The second task can be run in the inclusive time ranges [2, 3] and [5, 5].
    - The third task can be run in the two inclusive time range [5, 6].
    The computer will be on for a total of 4 seconds.


    *** Constraints ***
    1 <= tasks.length <= 2000
    tasks[i].length == 3
    1 <= starti, endi <= 2000
    1 <= durationi <= endi - starti + 1

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 91.33% */
/* Space Beats: 66.67% */

/* Time  Complexity: O(N * M) */ // Where 'M' is the maximum duration
/* Space Complexity: O(M)     */
class Solution {
public:
    int findMinimumTime(vector<vector<int>>& tasks)
    {
        int result = 0;

        // Determines whether work has been done before at each point
        int range[2001] = {0};

        // Sort interval by "end" time
        sort(tasks.begin(), tasks.end(), [](auto& a, auto& b) { return a[1] < b[1]; });

        for (const auto& curr_task : tasks)
        {
            int start    = curr_task[0];
            int end      = curr_task[1];
            int duration = curr_task[2];

            // Work has INDEED been done before
            for (int i = start; i <= end; i++)
            {
                if (range[i] > 0)
                    duration--;

                if (duration == 0)
                    break;
            }

            // Work that has NOT been done before
            while (duration)
            {
                // The duration is LESS THAN OR EQUAL TO interval size, so we
                // do NOT have to worry about going out of bound
                if (range[end] == 0)
                {
                    range[end]++;
                    duration--;
                    result++;
                }

                end--;
            }
        }

        return result;
    }
};
