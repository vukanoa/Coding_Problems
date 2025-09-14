/*
    ============
    === EASY ===
    ============

    ======================================
    3683) Earliest Time to Finish One Task
    ======================================

    ============
    Description:
    ============

    You are given a 2D integer array tasks where tasks[i] = [si, ti].

    Each [si, ti] in tasks represents a task with start time si that takes ti
    units of time to finish.

    Return the earliest time at which at least one task is finished.

    =======================================================
    FUNCTION: int earliestTime(vector<vector<int>>& tasks);
    =======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: tasks = [[1,6],[2,3]]
    Output: 5
    Explanation:
    The first task starts at time t = 1 and finishes at time 1 + 6 = 7. The
    second task finishes at time 2 + 3 = 5. You can finish one task at time 5.

    --- Example 2 ---
    Input: tasks = [[100,100],[100,100],[100,100]]
    Output: 200
    Explanation:
    All three tasks finish at time 100 + 100 = 200.


    *** Constraints ***
    1 <= tasks.length <= 100
    tasks[i] = [si, ti]
    1 <= si, ti <= 100

*/

#include <algorithm>
#include <climits>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 25.00% */
/* Space Beats: 75.00% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(logN)     */ // TC of C++'s Sort
class Solution {
public:
    int earliestTime(vector<vector<int>>& tasks)
    {
        const int N = tasks.size();
        int result = INT_MAX;

        /* Sort */
        sort(tasks.begin(), tasks.end());

        for (int i = 0; i < N; i++)
            result = min(result, tasks[i][0] + tasks[i][1]);

        return result;
    }
};
