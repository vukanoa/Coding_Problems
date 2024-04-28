#include <iostream>

/*
    ============
    === EASY ===
    ============

    ===========================
    292) Nim game
    ===========================

    ============
    Description:
    ============

    You are playing the following Nim Game with your friend:

        + Initially, there is a heap of stones on the table.

        + You and your friend will alternate taking turns, and you go first.

        + On each turn, the person whose turn it is will remove 1 to 3 stones
          from the heap.

        + The one who removes the last stone is the winner.

    Given n, the number of stones in the heap, return true if you can win the
    game assuming both you and your friend play optimally, otherwise return
    false.

    ================================
    FUNCTION: bool canWinNim(int n);
    ================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 4
    Output: false
    Explanation: These are the possible outcomes:
    1. You remove 1 stone. Your friend removes 3 stones, including the last
       stone. Your friend wins.
    2. You remove 2 stones. Your friend removes 2 stones, including the last
        stone. Your friend wins.
    3. You remove 3 stones. Your friend removes the last stone. Your friend
       wins.

    In all outcomes, your friend wins.


    --- Example 2 ---
    Input: n = 1
    Output: true

    --- Example 3 ---
    Input: n = 2
    Output: true


    *** Constraints ***
    1 <= n <= 2^31 - 1

*/

/*
    ------------
    --- IDEA ---
    ------------

    Let's think logically.

    Let's begin with Example 1:
        Input:  n = 4
        Output: false

    That tells us that whoever's turn is once the n is 4, he is "destined" to
    lose.

    Why?
    Consider that it's your turn and n is 4.

    You have three Options:
        1) You remove one   stone
        2) You remove two   stones
        3) You remove three stones

    1)
    If you remove one stone, then it's your opponent's turn and n = 3. Since at
    any given time, you're allowed to remove up to 3 stones(minimally 1), that
    means your opponent can remove all 3 of them and win because he removed the
    very last stone.

    2)
    If you remove two stones, then it's your opponent's turn and n = 2. Since
    at any given time you're allowed to remove up to 3 stones(minimally 1),
    that means your opponent can remove 2 out of 2 stones and win because he
    removed the very last stone.

    3)
    If you remove three stones, then it's your opponent's turn and n = 1. Since
    at any given time you're allowed to remove up to 3 stones(minimally 1),
    that means your opponent can remove 1 out of 1 stones left and win because
    he removed the very last stone.


    Since that is the case, that means that if it's your turn and n = 4 you are
    DESTINED to lose. It's guaranteed. There's no way around it.

    Therefore, if you can somehow remove some number of stones and left n=4 for
    your opponent, then you're 100% a winner.


    However, let's take a look at n=5, n=6, n=7, n=8.

    If it's your turn and n=5 and you KNOW that if you get n down to 4 a it's
    his turn, then he will lose, i.e. you will win.

    Therefore, if n=5 and it's your turn, simply remove one stone and you're a
    winner.

    Similarly, if n=6 and it's your turn, simply remove two stones and you're a
    winner as well.

    And lastly, if n=7 and it's your turn, simply remove three stones and
    you're a winner as well.


    However, if n=8 and it's your turn, then let's check your options:
        1) You remove one   stone
        2) You remove two   stones
        3) You remove three stones


    1)
        If you remove one stone, then n becomes 7 and it's your opponent's
        turn. However, as we've seen up above, whoever's turn it is at n=5 or
        n=6 or n=7 he is DESTINED to win, because if he plays optimally(which
        is said that playing this game, both of us are playing optimally) he
        will win.

    2)
        If you remove two stones, then n becomes 6 and it's your opponent's
        turn. As we've seen, that also leads to you losing.

    3)
        If you remove three stones, then n becomes 5 and it's your opponent's
        turn. As we've seen, that too leads to you losing.

    Therefore, if n=8 and it's your turn, you are DESTINED to lose!
    And vice-versa, if n=8 and it's your opponent's turn, you are going to win!


    So, as we've seen:
        1) if n=4 and it's your turn then you're guaranteed to lose.
        2) if n=8 and it's your turn then you're guaranteed to lose.
        3) ...

    Can you see a pattern?

    Exactly! If a number is divisible by 4, then, since FIRST TURN IS YOURS,
    you're a loser.

    Or let's put it positively - Since you're on the move FIRST and if n is NOT
    divisible by 4, meaning (n % 4 != 0) then, you're a winner!

    Therefore, the whole solution is this:

        return n % 4 != 0;

*/

/* Time  Beats: 100.00% */
/* Space Beats:  88.20% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool canWinNim(int n)
    {
        return n % 4 != 0;
    }
};
