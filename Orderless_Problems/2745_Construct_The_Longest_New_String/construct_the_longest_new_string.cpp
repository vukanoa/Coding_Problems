/*
    ==============
    === MEDIUM ===
    ==============

    ======================================
    2745) Construct the Longest New String
    ======================================

    ============
    Description:
    ============

    You are given three integers x, y, and z.

    You have x strings equal to "AA", y strings equal to "BB", and z strings
    equal to "AB". You want to choose some (possibly all or none) of these
    strings and concatenate them in some order to form a new string. This new
    string must not contain "AAA" or "BBB" as a substring.

    Return the maximum possible length of the new string.

    A substring is a contiguous non-empty sequence of characters within a
    string.

    =================================================
    FUNCTION: int longestString(int x, int y, int z);
    =================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: x = 2, y = 5, z = 1
    Output: 12
    Explanation: We can concatenate the strings "BB", "AA", "BB", "AA", "BB",
    and "AB" in that order. Then, our new string is "BBAABBAABBAB".  That
    string has length 12, and we can show that it is impossible to construct a
    string of longer length.

    --- Example 2 ---
    Input: x = 3, y = 2, z = 2
    Output: 14
    Explanation: We can concatenate the strings
    "AB", "AB", "AA", "BB", "AA", "BB", and "AA" in that order. Then, our new
    string is "ABABAABBAABBAA". That string has length 14, and we can show
    that it is impossible to construct a string of longer length.


    *** Constraints ***
    1 <= x, y, z <= 50

*/

#include <algorithm>
#include <cstring>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    More-or-less a standard Memoization problem.

*/

/* Time  Beats: 5.51% */
/* Space Beats: 6.69% */

/* Time  Complexity: O(3 * N^3) --> O(N^3) */
/* Space Complexity: O(3 * N^3) --> O(N^3) */
class Solution {
private:
    int memo[51][51][51][3];

public:
    int longestString(int x, int y, int z)
    {
        memset(memo, -1, sizeof(memo));

        int start_x = -1;
        int start_y = -1;
        int start_z = -1;

        if (x > 0) start_x = 1 + solve(x-1, y  , z  , 'x');
        if (y > 0) start_y = 1 + solve(x  , y-1, z  , 'y');
        if (z > 0) start_z = 1 + solve(x  , y  , z-1, 'z');

        return 2 * max( {start_x, start_y, start_z} );
    }

private:
    int solve(int x, int y, int z, char prev)
    {
        if (x == 0 && y == 0 && z == 0)
            return 0;

        int idx_prev = prev == 'x' ? 0 : (prev == 'y' ? 1 : 2);

        if (memo[x][y][z][idx_prev] != -1)
            return memo[x][y][z][idx_prev];

        int take_x = -1;
        int take_y = -1;
        int take_z = -1;

        if (prev == 'x')
        {
            if (y > 0)
                take_y = 1 + solve(x  , y-1, z  , 'y');
        }
        else // prev == 'y' || prev == 'z'
        {
            if (x > 0)
                take_x = 1 + solve(x-1, y  , z  , 'x');

            if (z > 0)
                take_z = 1 + solve(x  , y  , z-1, 'z');
        }

        return max(0, memo[x][y][z][idx_prev] = max( {take_x, take_y, take_z} ));
    }
};
