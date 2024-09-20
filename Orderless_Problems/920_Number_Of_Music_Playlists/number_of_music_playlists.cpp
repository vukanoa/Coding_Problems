#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ==============================
    920) Number of Music Playlists
    ==============================

    ============
    Description:
    ============

    Your music player contains n different songs. You want to listen to goal
    songs (not necessarily different) during your trip. To avoid boredom, you
    will create a playlist so that:

        + Every song is played at least once.
        + A song can only be played again only if k other songs have been
          played.

    Given n, goal, and k, return the number of possible playlists that you can
    create. Since the answer can be very large, return it modulo 109 + 7.

    =========================================================
    FUNCTION: int numMusicPlaylists(int n, int goal, int k);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 3, goal = 3, k = 1
    Output: 6
    Explanation: There are 6 possible playlists: [1, 2, 3], [1, 3, 2], [2, 1,
                 3], [2, 3, 1], [3, 1, 2], and [3, 2, 1].


    --- Example 2 ---
    Input: n = 2, goal = 3, k = 0
    Output: 6
    Explanation: There are 6 possible playlists: [1, 1, 2], [1, 2, 1], [2, 1,
                 1], [2, 2, 1], [2, 1, 2], and [1, 2, 2].


    --- Example 3 ---
    Input: n = 2, goal = 3, k = 1
    Output: 2
    Explanation: There are 2 possible playlists: [1, 2, 1] and [2, 1, 2].


    *** Constraints ***
    0 <= k < n <= goal <= 100

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 25.05% */
/* Space Beats: 38.25% */

/* Time  Complexity: O(n * goal) */
/* Space Complexity: O(n * goal) */
class Solution {
public:
    int numMusicPlaylists(int n, int goal, int k) {

        const int MOD = 1'000'000'007;

        vector<vector<long long>> dp(n + 1, vector<long long> (goal + 1));
        dp[0][0] = 0;
        dp[1][1] = 1;

        for (int i = 2; i <= n; i++)
            dp[i][i] = (dp[i - 1][i - 1] * i) % MOD;

        for (int i = 1; i <= n; i++)
        {
            for (int j = i + 1; j <= goal; j++)
                (dp[i][j] = dp[i][j - 1] * max(0LL, (long long)i - k) + dp[i - 1][j - 1] * i) %= MOD;
        }

        return dp[n][goal];
    }
};
