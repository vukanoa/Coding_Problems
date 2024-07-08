#include <iostream>
#include <unordered_set>

/*
    ==============
    === MEDIUM ===
    ==============

    ==========================================
    1823) Find The Winner of The Circular Game
    ==========================================

    ============
    Description:
    ============

    There are n friends that are playing a game. The friends are sitting in a
    circle and are numbered from 1 to n in clockwise order. More formally,
    moving clockwise from the ith friend brings you to the (i+1)th friend for 1
    <= i < n, and moving clockwise from the nth friend brings you to the 1st
    friend.

    The rules of the game are as follows:

        1. Start at the 1st friend.

        2. Count the next k friends in the clockwise direction including the
           friend you started at. The counting wraps around the circle and may
           count some friends more than once.

        3. The last friend you counted leaves the circle and loses the game.

        4. If there is still more than one friend in the circle, go back to
           step 2 starting from the friend immediately clockwise of the friend
           who just lost and repeat.

        5. Else, the last friend in the circle wins the game.

    Given the number of friends, n, and an integer k, return the winner of the
    game.

    ==========================================
    FUNCTION: int findTheWinner(int n, int k);
    ==========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 5, k = 2
    Output: 3
    Explanation: Here are the steps of the game:
    1) Start at friend 1.
    2) Count 2 friends clockwise, which are friends 1 and 2.
    3) Friend 2 leaves the circle. Next start is friend 3.
    4) Count 2 friends clockwise, which are friends 3 and 4.
    5) Friend 4 leaves the circle. Next start is friend 5.
    6) Count 2 friends clockwise, which are friends 5 and 1.
    7) Friend 1 leaves the circle. Next start is friend 3.
    8) Count 2 friends clockwise, which are friends 3 and 5.
    9) Friend 5 leaves the circle. Only friend 3 is left, so they are the winner.

    --- Example 2 ---
    Input: n = 6, k = 5
    Output: 1
    Explanation: The friends leave in this order: 5, 4, 6, 2, 3. The winner is
                 friend 1.

    *** Constraints ***
    1 <= k <= n <= 500

*/

/*
    ------------
    --- IDEA ---
    ------------

    Basic logic. Intuitive approach.

*/

/* Time  Beats:  5.04% */
/* Space Beats: 33.96% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int findTheWinner(int n, int k)
    {
        std::unordered_set<int> eliminated;
        int friend_idx = n;

        while (eliminated.size() < n-1)
        {
            int i = 0;
            while (i < k)
            {
                friend_idx = (friend_idx % n) + 1;

                if (eliminated.count(friend_idx) == 0)
                    i++;
            }

            eliminated.insert(friend_idx);
        }

        /* Find the one that has NOT been eliminated */
        for (int i = 1; i <= n; i++)
        {
            if (eliminated.count(i) == 0) // NOT eliminated
                return i;
        }

        return -1;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 75.45% */
/* Space Beats: 92.77% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Recursive {
public:
    int findTheWinner(int n, int k)
    {
        return recursion(n, k) + 1;
    }

private:
    int recursion(int n, int k)
    {
        if (n == 1)
            return 0;

        return (recursion(n-1, k) + k) % n;
    }
};
