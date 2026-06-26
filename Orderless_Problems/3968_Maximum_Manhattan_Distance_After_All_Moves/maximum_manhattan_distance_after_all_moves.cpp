/*
    ==============
    === MEDIUM ===
    ==============

    ================================================
    3968) Maximum Manhattan Distance After All Moves
    ================================================

    ============
    Description:
    ============

    You are given a string moves consisting of the characters 'U', 'D', 'L',
    'R', and '_'.

    Starting from the origin (0, 0), each character represents one move on a 2D
plane:

        'U': Move up by 1 unit.
        'D': Move down by 1 unit.
        'L': Move left by 1 unit.
        'R': Move right by 1 unit.
        '_': Can be independently replaced with any one of:
                 + 'U',
                 + 'D',
                 + 'L',
                 + 'R'

    Return the maximum from the origin that can be achieved after all moves
    have been performed.

    ========================================
    FUNCTION: int maxDistance(string moves);
    ========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: moves = "L_D_"
    Output: 4
    Explanation:
    One optimal choice is:
        'L': (0, 0) -> (-1, 0)
        '_' treated as 'D': (-1, 0) -> (-1, -1)
        'D': (-1, -1) -> (-1, -2)
        '_' treated as 'L': (-1, -2) -> (-2, -2)
    The final Manhattan distance from the origin is |0 - (-2)| + |0 - (-2)| = 4.


    --- Example 2 ---
    Input: moves = "U_R"
    Output: 3
    Explanation:
    One optimal choice is:
        'U': (0, 0) -> (0, 1)
        '_' treated as 'U': (0, 1) -> (0, 2)
        'R': (0, 2) -> (1, 2)
    The final Manhattan distance from the origin is |0 - 1| + |0 - 2| = 3.


    *** Constraints ***
    1 <= moves.length <= 10^5
    moves consists of only 'U', 'D', 'L', 'R', and '_'.

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 73.16% */
/* Space Beats:  7.52% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int maxDistance(string moves)
    {
        const int N = moves.size();

        int underscores = 0;
        int x = 0;
        int y = 0;

        for (const char& chr : moves)
        {
            if (chr == '_')
            {
                underscores++;
                continue;
            }

            if (chr == 'L' || chr == 'R')
            {
                x += (chr == 'L') ? 1 : -1;
            }
            else // if (chr == 'U' || chr == 'D') 
            {
                y += (chr == 'U') ? 1 : -1;
            }
        }

        return abs(x) + abs(y) + underscores;
    }
};
