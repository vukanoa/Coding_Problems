/*
    ============
    === EASY ===
    ============

    =========================================
    4061) Minimum Queen Moves to Reach Target
    =========================================

    ============
    Description:
    ============

    There is an 8 x 8 empty chessboard with 1-indexed rows and columns.

    You are given an array source = [sr, sc] representing the starting position
    of a queen, and an array target = [tr, tc] representing the target
    position.

    In one move, the queen travels one or more squares along a single row,
    column, or diagonal, staying within the board.

    Return the minimum number of moves for the queen to land exactly on target.

    ======================================================================
    FUNCTION: int minQueenMoves(vector<int>& source, vector<int>& target);
    ======================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: source = [8,1], target = [1,8]
    Output: 1

    --- Example 2 ---
    Input: source = [4,2], target = [1,3]
    Output: 2

    --- Example 3 ---
    Input: source = [1,1], target = [1,1]
    Output: 0


    *** Constraints ***
    source == [sr, sc]
    target == [tr, tc]
    1 <= sr, sc, tr, tc <= 8

*/

#include <cstdlib>
#include <vector>
using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    If they are on the came cell, we don't need to move, therefore return 0.

    If they are on the same row but not the same column, or vice verca, then
    we need only 1 move.

    If the ABSOLUTE difference between source[0] and target[0] is EQUAL to the
    ABSOLUTE difference between source[1] and target[1], then that means two
    positions are on the diagonal, i.e. only 1 move is required.


    In ALL of the other cases, we need 2 moves. There isn't a case where we
    need more than 2. Think about it. Try to come up with such example and
    you'll fail.

*/

/* Time  Beats:  7.07% */
/* Space Beats: 51.99% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution {
public:
    int minQueenMoves(vector<int>& source, vector<int>& target)
    {
        if (source[0] == target[0] && source[1] == target[1])
            return 0;

        if (source[0] == target[0] || source[1] == target[1])
            return 1;

        if (abs(source[0] - target[0]) == abs(source[1] - target[1]))
            return 1;

        return 2;
    }
};
