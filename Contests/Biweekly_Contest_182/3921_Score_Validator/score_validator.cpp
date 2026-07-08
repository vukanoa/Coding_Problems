/*
    ============
    === EASY ===
    ============

    ===========================
    3921) Score Validator
    ===========================

    ============
    Description:
    ============

    You are given a string array events.

    Initially, score = 0 and counter = 0. Each element in events is one of the
    following:

        "0", "1", "2", "3", "4", "6": Add that value to the total score.
        "W": Increase the counter by 1. No score is added.
        "WD": Add 1 to the total score.
        "NB": Add 1 to the total score.

    Process the array from left to right. Stop processing when either:

        All elements in events have been processed, or
        The counter becomes 10.

    Return an integer array [score, counter], where:

        score is the final total score.
        counter is the final counter value.

    =============================================================
    FUNCTION: vector<int> scoreValidator(vector<string>& events);
    =============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: events = ["1","4","W","6","WD"]
    Output: [12,1]

    --- Example 2 ---
    Input: events = ["WD","NB","0","4","4"]
    Output: [10,0]

    --- Example 3 ---
    Input: events = ["W","W","W","W","W","W","W","W","W","W","W"]
    Output: [0,10]
    Explanation:
    After 10 occurrences of "W", the counter reaches 10, so processing stops.
    The remaining events are ignored.


    *** Constraints ***
    1 <= events.length <= 1000
    events[i] is one of "0", "1", "2", "3", "4", "6", "W", "WD", or "NB".

*/

#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Simulation problem.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  95.93% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    vector<int> scoreValidator(vector<string>& events)
    {
        const int N = events.size();

        int score   = 0;
        int counter = 0;

        for (int i = 0; i < N && counter < 10; i++)
        {
            if (events[i] == "W")
            {
                counter++;
            }
            else
            {
                if (events[i][0] >= '0' && events[i][0] <= '9')
                    score += events[i][0] - '0';
                else
                    score++;
            }
        }

        return {score, counter};
    }
};
