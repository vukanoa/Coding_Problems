/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    3206) Alternating Groups I
    ===========================

    ============
    Description:
    ============

    There is a circle of red and blue tiles. You are given an array of integers
    colors. The color of tile i is represented by colors[i]:

        colors[i] == 0 means that tile i is red.
        colors[i] == 1 means that tile i is blue.

    Every 3 contiguous tiles in the circle with alternating colors (the middle
    tile has a different color from its left and right tiles) is called an
    alternating group.

    Return the number of alternating groups.

    =====
    Note: that since colors represents a circle, the first and the last tiles
          are considered to be next to each other.
    =====

    =============================================================
    FUNCTION: int numberOfAlternatingGroups(vector<int>& colors);
    =============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: colors = [1,1,1]
    Output: 0

    --- Example 2 ---
    Input: colors = [0,1,0,0,1]
    Output: 3


    *** Constraints ***
    3 <= colors.length <= 100
    0 <= colors[i] <= 1

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This can be done using Brute-Force because of the given Constraints, but
    this is more efficient.

*/

/* Time  Beats: 37.47% */
/* Space Beats: 52.29% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int numberOfAlternatingGroups(vector<int>& colors)
    {
        const int N = colors.size();
        int result = 0;

        int L = 0;
        int R = 2;

        while (R < N+2)
        {
            if (colors[L] == colors[R % N] && colors[L] != colors[(L + 1) % N])
                result++;

            L++;
            R++;
        }

        return result;
    }
};
