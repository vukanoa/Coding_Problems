/*
    ============
    === EASY ===
    ============

    ============================================
    1812) Determine Color of a Chessboard Square
    ============================================

    ============
    Description:
    ============

    You are given coordinates, a string that represents the coordinates of a
    square of the chessboard. Below is a chessboard for your reference.

    Return true if the square is white, and false if the square is black. The
    coordinate will always represent a valid chessboard square. The coordinate
    will always have the letter first, and the number second.

    =================================================
    FUNCTION: bool squareIsWhite(string coordinates);
    =================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: coordinates = "a1"
    Output: false
    Explanation: From the chessboard above, the square with coordinates "a1" is black, so return false.

    --- Example 2 ---
    Input: coordinates = "h3"
    Output: true
    Explanation: From the chessboard above, the square with coordinates "h3" is
                 white, so return true.

    --- Example 3 ---
    Input: coordinates = "c7"
    Output: false

    *** Constraints ***
    coordinates.length == 2
    'a' <= coordinates[0] <= 'h'
    '1' <= coordinates[1] <= '8'

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    If we represent:

        a = 0
        b = 1
        c = 2
        ...

    and we represent digits in coordinates as integers they represent, then if
    we simply add these two values we'll have either an ODD or an EVEN number.

    If it's EVEN then it's white and we must return "true".
    Otherwise, return "false".

    That's it.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  73.04% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool squareIsWhite(string coordinates)
    {
        return (static_cast<int>(coordinates[0] - 'a') + static_cast<int>(coordinates[1] - '0')) % 2 == 0;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    However, instead of converting them to string and then adding them, why
    don't we just add values of strings represented in ASCII.

        'a' = 97
        'b' = 98
        'c' = 99
        ...


        '1' = 49
        '2' = 50
        '3' = 51
        ...

    However since now 'a' doesn't begin at the EVEN value, but rather ODD one,
    we can simply check if the sum of these two is ODD.

    If it's ODD, then it's a white square.
    Otherwise it's a black square.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  73.04% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution_2 {
public:
    bool squareIsWhite(string coordinates)
    {
        return (coordinates[0] + coordinates[1]) & 1;
    }
};
