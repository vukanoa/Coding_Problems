/*
    ============
    === EASY ===
    ============

    ===========================
    1025) Divisor Game
    ===========================

    ============
    Description:
    ============

    Alice and Bob take turns playing a game, with Alice starting first.

    Initially, there is a number n on the chalkboard. On each player's turn,
    that player makes a move consisting of:

        + Choosing any x with 0 < x < n and n % x == 0.
        + Replacing the number n on the chalkboard with n - x.

    Also, if a player cannot make a move, they lose the game.

    Return true if and only if Alice wins the game, assuming both players play
    optimally.

    ==================================
    FUNCTION: bool divisorGame(int n);
    ==================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 2
    Output: true
    Explanation: Alice chooses 1, and Bob has no more moves.

    --- Example 2 ---
    Input: n = 3
    Output: false
    Explanation: Alice chooses 1, Bob chooses 1, and Alice has no more moves.


    *** Constraints ***
    1 <= n <= 1000

*/

/*
    ------------
    --- IDEA ---
    ------------


    Anyone who gets 1 definitely loses since not exist a x in range of (0, 1)

    1. Anyone who gets 2 definitely wins since he always/or only can make 2
       become 1 because x can only be 1, 2 % 1 == 0 and 2 - 1 = 1

    2. For any N >= 2, N will definitely be reduced to 2

    3. Just illustrate some N below. Based on the "chain", you can see, no
       matter what N starts, all leads to 2 in the end:


    //  2 -> 1
        3 -> 2
    //  4 -> 2, 3
        5 -> 4
    //  6 -> 3, 4, 5
        7 -> 6
    //  8 -> 4, 6, 7
        9 -> 6, 8
    //  10 -> 5, 8, 9
        11 -> 10
    //  12 -> 8, 9, 10, 11
        13 -> 12
    //  14 -> 7, 12, 13
        15 -> 10, 12
    //  16 -> 8, 12, 14
        17 -> 16
    //  18 -> 9, 12, 15, 16
        19 -> 18
    //  20 -> 10, 15, 16, 18
    ...

*/

/* Time  Beats: 100.00% */
/* Space Beats:  61.19% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool divisorGame(int n)
    {
        return n % 2 == 0;
    }
};
