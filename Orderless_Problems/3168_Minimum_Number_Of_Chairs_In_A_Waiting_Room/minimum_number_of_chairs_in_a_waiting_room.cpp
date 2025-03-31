/*
    ============
    === EASY ===
    ============

    ================================================
    3168) Minimum Number of Chairs in a Waiting Room
    ================================================

    ============
    Description:
    ============

    You are given a string s. Simulate events at each second i:

        + If s[i] == 'E', a person enters the waiting room and takes one of the
          chairs in it.

        + If s[i] == 'L', a person leaves the waiting room, freeing up a chair.

    Return the minimum number of chairs needed so that a chair is available for
    every person who enters the waiting room given that it is initially empty.

    ======================================
    FUNCTION: int minimumChairs(string s);
    ======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "EEEEEEE"
    Output: 7
    Explanation: After each second, a person enters the waiting room and no
                 person leaves it. Therefore, a minimum of 7 chairs is needed

    --- Example 2 ---
    Input: s = "ELELEEL"
    Output: 2
    Explanation: Let's consider that there are 2 chairs in the waiting room.
                 The table below shows the state of the waiting room at each
                 second.

    --- Example 3 ---
    Input: s = "ELEELEELLL"
    Output: 3
    Explanation: Let's consider that there are 3 chairs in the waiting room.
                 The table below shows the state of the waiting room at each
                 second.


    *** Constraints ***
    1 <= s.length <= 50
    s consists only of the letters 'E' and 'L'.
    s represents a valid sequence of entries and exits.

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  16.23% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int minimumChairs(string s)
    {
        int result = 0;

        int chair = 0;
        for (const char& chr : s)
        {
            if (chr == 'E')
                chair++;
            else
                chair--;

            result = max(result, chair);
        }

        return result;
    }
};
