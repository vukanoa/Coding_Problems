/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    3208) Alternating Groups II
    ===========================

    ============
    Description:
    ============

    There is a circle of red and blue tiles. You are given an array of integers
    colors and an integer k. The color of tile i is represented by colors[i]:

        colors[i] == 0 means that tile i is red.
        colors[i] == 1 means that tile i is blue.

    An alternating group is every k contiguous tiles in the circle with
    alternating colors (each tile in the group except the first and last one
    has a different color from its left and right tiles).

    Return the number of alternating groups.

    Note that since colors represents a circle, the first and the last tiles
    are considered to be next to each other.

    ====================================================================
    FUNCTION: int numberOfAlternatingGroups(vector<int>& colors, int k);
    ====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: colors = [0,1,0,1,0], k = 3
    Output: 3

    --- Example 2 ---
    Input: colors = [0,1,0,0,1,0,1], k = 6
    Output: 2

    --- Example 3 ---
    Input: colors = [1,1,0,1], k = 4
    Output: 0


    *** Constraints ***
    3 <= colors.length <= 10^5
    0 <= colors[i] <= 1
    3 <= k <= colors.length

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Basic "Fixed Sliding Window Technique". The only "trick" we've used here is
    to extend the original array so that we don't have to worry about its
    circular property.

*/

/* Time  Beats: 60.04% */
/* Space Beats: 13.39% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int numberOfAlternatingGroups(vector<int>& colors, int k)
    {
        vector<int> extended_colors = colors;
        extended_colors.insert(extended_colors.end(), colors.begin(), colors.begin() + k - 1);

        const int N = extended_colors.size();
        int result = 0;

        int L = 0;
        int R = 1;
        while (R < N)
        {
            if (extended_colors[R-1] == extended_colors[R])
                L = R;

            if (R - L + 1 == k)
            {
                result++;
                L++;
            }

            // Increment
            R++;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This one doesn't extend "colors", instead it uses a MOD logic to access
    circular elements.


    It's important to know this about Modulo:
    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    @@@@@@@@@@@@@@@  Mathematical modulo vs "operator %" @@@@@@@@@@@@@@@@@@
    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


    Mathematical modulo works a bit differently than operator '%'.

    In mathematics: (-25) modulo 26 is 1
    In C++:         (-25) modulo 26 is -25

    Since we need the mathematical verison of modulo, we need to use the
    function below.

     int mathematical_mod(int num)
     {
         const int ALPHABET_LENGTH = 26;
         return (num % ALPHABET_LENGTH + ALPHABET_LENGTH) % ALPHABET_LENGTH;
     }

    In our case we DO NOT need to worry about this since we're going to MOD
    only in case R > 0, but its good to be aware of this stuff.

*/

/* Time  Beats: 33.47% */
/* Space Beats: 43.10% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Space_Efficient {
public:
    int numberOfAlternatingGroups(vector<int>& colors, int k)
    {
        const int N = colors.size();

        int result = 0;

        int L = 0;
        int R = 0;

        while (R < N + k - 1)
        {
            if (R > 0 && colors[(R - 1) % N] == colors[R % N])
                L = R;

            if (R - L + 1 >= k)
                result++;

            // Increment
            R++;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Another way of implementing it. This one is the most intuitive way of
    thinking about this problem.

*/

/* Time  Beats:  9.51% */
/* Space Beats: 61.38% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Another_Implementation { // 56min
public:
    int numberOfAlternatingGroups(vector<int>& colors, int k)
    {
        const int N = colors.size();
        int result = 0;

        int L = 0;
        int R = 1;

        while (R < N + k && L < N)
        {
            if (colors[(R - 1) % N] == colors[R % N])
            {
                L = R;
            }
            else
            {
                if (R - L + 1 == k)
                {
                    result++;
                    L++;
                }
            }

            // Increment
            R++;
        }

        return result;
    }
};
