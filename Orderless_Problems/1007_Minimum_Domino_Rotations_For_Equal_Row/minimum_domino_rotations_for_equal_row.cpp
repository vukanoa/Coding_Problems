/*
    ==============
    === MEDIUM ===
    ==============

    ============================================
    1007) Minimum Domino Rotations For Equal Row
    ============================================

    ============
    Description:
    ============

    In a row of dominoes, tops[i] and bottoms[i] represent the top and bottom
    halves of the ith domino. (A domino is a tile with two numbers from 1 to 6
    - one on each half of the tile.)

    We may rotate the ith domino, so that tops[i] and bottoms[i] swap values.

    Return the minimum number of rotations so that all the values in tops are
    the same, or all the values in bottoms are the same.

    If it cannot be done, return -1.

    ==========================================================================
    FUNCTION: int minDominoRotations(vector<int>& tops, vector<int>& bottoms);
    ==========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: tops = [2,1,2,4,2,2], bottoms = [5,2,6,2,3,2]
    Output: 2
    Explanation: The first figure represents the dominoes as given by tops and
    bottoms: before we do any rotations.  If we rotate the second and fourth
    dominoes, we can make every value in the top row equal to 2, as indicated
    by the second figure.


    --- Example 2 ---
    Input: tops = [3,5,1,2,3], bottoms = [3,6,3,3,4]
    Output: -1
    Explanation:
    In this case, it is not possible to rotate the dominoes to make one row of values equal.


    *** Constraints ***
    2 <= tops.length <= 2 * 10^4
    bottoms.length == tops.length
    1 <= tops[i], bottoms[i] <= 6

*/

#include <climits>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 34.91% */
/* Space Beats: 48.71% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution1 {
public:
    int minDominoRotations(vector<int>& tops, vector<int>& bottoms)
    {
        const int N = tops.size();
        const int MIN_DOMINO_VALUE = 1;
        const int MAX_DOMINO_VALUE = 6;

        int result = INT_MAX;

        for (int val = MIN_DOMINO_VALUE; val <= MAX_DOMINO_VALUE; val++)
        {
            bool possible = true;

            int swaps_in_top = 0;
            int swaps_in_bot = 0;

            for (int j = 0; j < N; j++)
            {
                if (tops[j] != val && bottoms[j] != val)
                {
                    possible = false;
                    break;
                }
                else if (tops[j] != val)
                {
                    swaps_in_top++;
                }
                else if (bottoms[j] != val)
                {
                    swaps_in_bot++;
                }
            }

            if (possible)
            {
                result = min(result, swaps_in_top);
                result = min(result, swaps_in_bot);
            }
        }

        return result == INT_MAX ? -1 : result;
    }
};
