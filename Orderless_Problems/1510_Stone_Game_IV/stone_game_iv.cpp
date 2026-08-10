/*
    ============
    === HARD ===
    ============

    ===========================
    1510) Stone Game IV
    ===========================

    ============
    Description:
    ============

    Alice and Bob take turns playing a game, with Alice starting first.

    Initially, there are n stones in a pile. On each player's turn, that player
    makes a move consisting of removing any non-zero square number of stones in
    the pile.

    Also, if a player cannot make a move, he/she loses the game.

    Given a positive integer n, return true if and only if Alice wins the game
    otherwise return false, assuming both players play optimally.

    =======================================
    FUNCTION: bool winnerSquareGame(int n);
    =======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 1
    Output: true
    Explanation: Alice can remove 1 stone winning the game because Bob doesn't
                 have any moves.

    --- Example 2 ---
    Input: n = 2
    Output: false
    Explanation: Alice can only remove 1 stone, after that Bob removes the last
                 one winning the game (2 -> 1 -> 0).

    --- Example 3 ---
    Input: n = 4
    Output: true
    Explanation: n is already a perfect square, Alice can win with one move,
                 removing 4 stones (4 -> 0).


    *** Constraints ***
    1 <= n <= 10^5

*/

#include <vector>
using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    
    Since both players play optimally, Zermelo’s theorem guarantees that every
    state is either winning or losing for the current player.

    The current player wins if at least a SINGLE move leaves the opponent in a
    losing position.


    Alice is the starting player, beginning the game with n stones.

    She can remove any square number of stones:
        1, 4, 9, 16, ...




    After Alice removes either 1, or 4, or 9… stones, the game moves to a
    smaller number of remaining stones:

        Case 1: If any of the Alice's choices leaves Bob in a LOSING position,
                then Alice can select this move and win.


        Case 2: Otherwise, if every possible Alice's choice leaves Bob in a
                WINNING position, then Alice is guaranteed to lose.



    Picture for Case 1:

                                   Alice WINS
                             __________n=9__________
                            /           |           \
                           /            |            \
                          /             |             \
                         / -1           |-4            \ -9
                        /               |               \
                       /                |                \
                   Bob WINS         Bob LOSES        Bob LOSES
                     n=8                n=5               0
                   /  |  \            /  |  \           /  |  \
                  /   |   \          /   |   \         /   |   \
                 /    |    \        /    |    \       /    |    \
                     ...                ...              ...





    Picture for Case 2:

                                Alice LOSES
                                   n=5
                                  /   \
                                 /     \
                                /       \
                               /         \
                              /           \
                          Bob WINS       Bob WINS
                            n=4           n=1
                            / \           / \
                           /   \         /   \
                          /     \       /     \
                            ...           ...    



    Here we're doing a Bottom-Up Tabulation Solution.
    We're trying to remove any of the possible squares from i=1 to i*i <= n.

    If at ANY point we can remove a square that leaves the 'new_nn' such that
    the dp[new_n] == false, that means if we take this square number, the
    opponents is guaranteed to lose.

    Therefore, we know that WHOEVER starts with this value of n WINS!

    Since we're doing a Bottom-Up approach, we're computing values for n from a
    number 1, up until the Input n.

    At the end dp[n] holds whether Alice can WIN or NOT.

*/

/* Time  Beats: 18.48% */
/* Space Beats: 73.64% */

/* Time  Complexity: O(n * sqrt(n)) */
/* Space Complexity: O(n)           */
class Solution_Bottom_up__Tabulation {
public:
    bool winnerSquareGame(int n)
    {
        vector<bool> dp(n+1, false);

        // O(n * sqrt(n)) for entire block
        for (int num = 1; num <= n; num++) // O(n)
        {
            for (int i = 1; i*i <= n; i++) // O(sqrt(n))
            {
                if (num - i*i < 0)
                    break;

                dp[num] = dp[num] | !(dp[num - i*i]);
            }
        }

        return dp[n];
    }
};
