/*
    ============
    === HARD ===
    ============

    ===========================
    1406) Stone Game III
    ===========================

    ============
    Description:
    ============

    Alice and Bob continue their games with piles of stones. There are several
    stones arranged in a row, and each stone has an associated value which is
    an integer given in the array stoneValue.

    Alice and Bob take turns, with Alice starting first. On each player's turn,
    that player can take 1, 2, or 3 stones from the first remaining stones in
    the row.

    The score of each player is the sum of the values of the stones taken. The
    score of each player is 0 initially.

    The objective of the game is to end with the highest score, and the winner
    is the player with the highest score and there could be a tie. The game
    continues until all the stones have been taken.

    Assume Alice and Bob play optimally.

    Return "Alice" if Alice will win, "Bob" if Bob will win, or "Tie" if they
    will end the game with the same score.

    =======================================================
    FUNCTION: string stoneGameIII(vector<int>& stoneValue);
    =======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: stoneValue = [1,2,3,7]
    Output: "Bob"
    Explanation: Alice will always lose. Her best move will be to take three
                 piles and the score become 6. Now the score of Bob is 7 and
                 Bob wins.

    --- Example 2 ---
    Input: stoneValue = [1,2,3,-9]
    Output: "Alice"
    Explanation: Alice must choose all the three piles at the first move to win
                 and leave Bob with negative score.
    If Alice chooses one pile her score will be 1 and the next move Bob's score
    becomes 5. In the next move, Alice will take the pile with value = -9 and
    lose.
    If Alice chooses two piles her score will be 3 and the next move Bob's
    score becomes 3. In the next move, Alice will take the pile with value = -9
    and also lose.
    Remember that both play optimally so here Alice will choose the scenario
    that makes her win.


    --- Example 3 ---
    Input: stoneValue = [1,2,3,6]
    Output: "Tie"
    Explanation: Alice cannot win this game. She can end the game in a draw if
                 she decided to choose all the first three piles, otherwise she
                 will lose.


    *** Constraints ***
    1 <= stoneValue.length <= 5 * 10^4
    -1000 <= stoneValue[i] <= 1000

*/

#include <climits>
#include <string>
#include <vector>
#include <algorithm> // To prevent my LSP complaining about initializer_list
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Classic "Bottom-Up Tabulation" Dynamic Programming technique.

*/

/* Time  Beats: 66.21% */
/* Space Beats: 80.45% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Bottom_Up__Tabulation {
public:
    string stoneGameIII(vector<int>& stoneValue)
    {
        const int N = stoneValue.size();

        vector<int> dp(N+2, INT_MIN);
        dp[N+1] = 0;
        dp[N  ] = 0;
        dp[N-1] = stoneValue[N-1];

        for (int i = N-2; i >= 0; i--)
        {
            int curr_sum = 0;

            // j = 0   (Take first                      stone starting at index i)
            // j = 1   (Take first and second           stone starting at index i)
            // j = 2   (Take first and second and third stone starting at index i)
            for (int j = 0; j < 3; j++)
            {
                curr_sum += (i + j >= N) ? 0 : stoneValue[i + j];

                dp[i] = max(dp[i], curr_sum - dp[i + j + 1]);
            }
        }

        if (dp[0] == 0)
            return "Tie";

        return dp[0] > 0 ? "Alice" : "Bob";
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 98.18% */
/* Space Beats: 97.23% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Bottom_Up__Tabulation__Fancy_Space_Optimized {
public:
    string stoneGameIII(vector<int>& stoneValue)
    {
        vector<int> dp(4);
        const int N = stoneValue.size();

        // Apend two zeros at the end to avoid boundary check on every loop.
        stoneValue.push_back(0);
        stoneValue.push_back(0);

        for (int i = N-1; i >= 0; i--)
        {
            int one   = stoneValue[i];
            int two   = stoneValue[i] + stoneValue[i + 1];
            int three = stoneValue[i] + stoneValue[i + 1] + stoneValue[i + 2];

            dp[i & 3] = max( {one   - dp[(i + 1) & 3],
                              two   - dp[(i + 2) & 3],
                              three - dp[(i + 3) & 3]
                             });
        }

        // Restore original Input
        stoneValue.pop_back();
        stoneValue.pop_back();

        if (dp[0] == 0)
            return "Tie";

        return dp[0] > 0 ? "Alice" : "Bob";
    }
};
