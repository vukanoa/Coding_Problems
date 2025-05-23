/*
    ==============
    === MEDIUM ===
    ==============

    =======================================
    3096) Minimum Level to Gain More Points
    =======================================

    ============
    Description:
    ============

    You are given a binary array possible of length n.

    Alice and Bob are playing a game that consists of n levels. Some of the
    levels in the game are impossible to clear while others can always be
    cleared.

    In particular, if possible[i] == 0, then the ith level is impossible to
    clear for both the players. A player gains 1 point on clearing a level and
    loses 1 point if the player fails to clear it.

    At the start of the game, Alice will play some levels in the given order
    starting from the 0th level, after which Bob will play for the rest of the
    levels.

    Alice wants to know the minimum number of levels she should play to gain
    more points than Bob, if both players play optimally to maximize their
    points.

    Return the minimum number of levels Alice should play to gain more points.
    If this is not possible, return -1.

    Note that each player must play at least 1 level.

    ===================================================
    FUNCTION: int minimumLevels(vector<int>& possible);
    ===================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: possible = [1,0,1,0]
    Output: 1
    Explanation:
    Let's look at all the levels that Alice can play up to:
        If Alice plays only level 0 and Bob plays the rest of the levels, Alice has 1 point, while Bob has -1 + 1 - 1 = -1 point.
        If Alice plays till level 1 and Bob plays the rest of the levels, Alice has 1 - 1 = 0 points, while Bob has 1 - 1 = 0 points.
        If Alice plays till level 2 and Bob plays the rest of the levels, Alice has 1 - 1 + 1 = 1 point, while Bob has -1 point.
    Alice must play a minimum of 1 level to gain more points.

    --- Example 2 ---
    Input: possible = [1,1,1,1,1]
    Output: 3
    Explanation:
    Let's look at all the levels that Alice can play up to:
        If Alice plays only level 0 and Bob plays the rest of the levels, Alice has 1 point, while Bob has 4 points.
        If Alice plays till level 1 and Bob plays the rest of the levels, Alice has 2 points, while Bob has 3 points.
        If Alice plays till level 2 and Bob plays the rest of the levels, Alice has 3 points, while Bob has 2 points.
        If Alice plays till level 3 and Bob plays the rest of the levels, Alice has 4 points, while Bob has 1 point.
    Alice must play a minimum of 3 levels to gain more points.

    --- Example 3 ---
    Input: possible = [0,0]
    Output: -1
    Explanation:
    The only possible way is for both players to play 1 level each. Alice plays
    level 0 and loses 1 point. Bob plays level 1 and loses 1 point. As both
    players have equal points, Alice can't gain more points than Bob.


    *** Constraints ***
    2 <= n == possible.length <= 10^5
    possible[i] is either 0 or 1.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory. This is almost a "Simulation" kind of problem.

*/

/* Time  Beats: 26.48% */
/* Space Beats: 33.33% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int minimumLevels(vector<int>& possible)
    {
        const int N = possible.size();
        int result = 0;

        vector<int> ones(N, 0);

        ones[N-1] = possible[N-1] ? 1 : 0;
        for (int i = N-2; i >= 0; i--)
        {
            ones[i] = ones[i+1];

            if (possible[i])
                ones[i]++;
        }

        int alice_points = possible[0] == 1 ? 1 : -1;
        for (int i = 1; i < N; i++)
        {
            int zeroes = (N - i) - ones[i];

            int bob_points = ones[i] - zeroes;

            if (alice_points > bob_points)
                return i;

            if (possible[i])
                alice_points++;
            else
                alice_points--;
        }

        return -1;
    }
};
