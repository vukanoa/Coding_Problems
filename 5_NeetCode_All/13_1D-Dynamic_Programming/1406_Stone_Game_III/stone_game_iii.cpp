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
            int take_one   = stoneValue[i];
            int take_two   = stoneValue[i] + stoneValue[i + 1];
            int take_three = stoneValue[i] + stoneValue[i + 1] + stoneValue[i + 2];

            dp[i & 3] = max( {take_one   - dp[(i + 1) & 3],
                              take_two   - dp[(i + 2) & 3],
                              take_three - dp[(i + 3) & 3]
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




/*
    ------------
    --- IDEA ---
    ------------

    Standard way of turning a O(N) Space 1D-DP to O(1) Space.

*/

/* Time  Beats: 61.47% */
/* Space Beats: 94.80% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Bottom_Up__Tabulation__Space_Optimized {
public:
    string stoneGameIII(vector<int>& stoneValue)
    {
        const int N = stoneValue.size();

        /* PUSH, to prevent special cases */
        stoneValue.push_back(0);
        stoneValue.push_back(0);

        int next_next_next = 0;
        int next_next      = 0;
        int next           = stoneValue[N-1];

        for (int i = N-2; i >= 0; i--)
        {
            int take_one   = stoneValue[i + 0]                                         - next;
            int take_two   = stoneValue[i + 0] + stoneValue[i + 1]                     - next_next;
            int take_three = stoneValue[i + 0] + stoneValue[i + 1] + stoneValue[i + 2] - next_next_next;

            int curr = max(take_one, max(take_two, take_three));

            next_next_next = next_next;
            next_next      = next;
            next           = curr;
        }

        /* POP, to restore original Input state */
        stoneValue.pop_back();
        stoneValue.pop_back();

        if (next == 0)
            return "Tie";

        return next > 0 ? "Alice" : "Bob";
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 53.41% */
/* Space Beats: 60.61% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Top_Down__Memoization_1 {
private:
    static constexpr int MAX_SIZE = 5 * 1e4;
    int memo[MAX_SIZE + 4];

public:
    string stoneGameIII(vector<int>& stoneValue)
    {
        const int N = stoneValue.size();

        /* Initialize */
        fill(begin(memo), end(memo), INT_MIN);

        /* PUSH, to prevent special cases */
        stoneValue.push_back(0);
        stoneValue.push_back(0);

        /* Solve */
        int alice_points = solve(0, stoneValue, N);

        /* POP, to restore original Input state */
        stoneValue.pop_back();
        stoneValue.pop_back();

        if (alice_points == 0)
            return "Tie";

        return alice_points > 0 ? "Alice" : "Bob";
    }

private:
    int solve(int idx, vector<int>& stoneValue, const int& N)
    {
        if (idx >= N)
            return 0;

        if (memo[idx] != INT_MIN)
            return memo[idx];

        int take_one   = stoneValue[idx]                                             - solve(idx + 1, stoneValue, N);
        int take_two   = stoneValue[idx] + stoneValue[idx + 1]                       - solve(idx + 2, stoneValue, N);
        int take_three = stoneValue[idx] + stoneValue[idx + 1] + stoneValue[idx + 2] - solve(idx + 3, stoneValue, N);


        // If you use this version with an INITIALIZER LIST--You'll get a TLE!!
        //
        // The line BELOW gives a TLE!!!
        // return memo[idx] = max( {take_one, take_two, take_three} );
        //
        // The reason is quite simple: 
        // Initializer_list constructs a temporary std::initializer_list object
        // on every DP state. Since there are about 50,000 states, this adds
        // noticeable overhead.

        return memo[idx] = max(take_one, max(take_two, take_three));
    }
};





/* Time  Beats: 64.47% */
/* Space Beats: 89.99% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Top_Down__Memoization_2 {
private:
    static constexpr int MAX_SIZE = 5 * 1e4;
    int memo[MAX_SIZE + 4];

public:
    string stoneGameIII(vector<int>& stoneValue)
    {
        const int N = stoneValue.size();

        /* Initialize */
        fill(begin(memo), end(memo), INT_MIN);

        /* Solve */
        int alice_points = solve(0, stoneValue, N);

        if (alice_points == 0)
            return "Tie";

        return alice_points > 0 ? "Alice" : "Bob";
    }

private:
    int solve(int idx, vector<int>& stoneValue, const int& N)
    {
        if (idx >= N)
            return 0;

        if (memo[idx] != INT_MIN)
            return memo[idx];

        int first_one   = stoneValue[idx];
        int first_two   = first_one + ((idx + 1 < N) ? stoneValue[idx + 1] : 0);
        int first_three = first_two + ((idx + 2 < N) ? stoneValue[idx + 2] : 0);

        int take_one   = first_one   - solve(idx + 1, stoneValue, N);
        int take_two   = first_two   - solve(idx + 2, stoneValue, N);
        int take_three = first_three - solve(idx + 3, stoneValue, N);

        // If you use this version with an INITIALIZER LIST--You'll get a TLE!!
        //
        // The line BELOW gives a TLE!!!
        // return memo[idx] = max( {take_one, take_two, take_three} );
        //
        // The reason is quite simple: 
        // Initializer_list constructs a temporary std::initializer_list object
        // on every DP state. Since there are about 50,000 states, this adds
        // noticeable overhead.

        return memo[idx] = max(take_one, max(take_two, take_three));
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 74.18% */
/* Space Beats: 88.20% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Top_Down__Memoization_3 {
private:
    static constexpr int MAX_SIZE = 5 * 1e4;
    int memo[MAX_SIZE + 4];

public:
    string stoneGameIII(vector<int>& stoneValue)
    {
        const int N = stoneValue.size();

        /* Initialize */
        fill(begin(memo), end(memo), INT_MIN);

        /* Solve */
        int result = solve(0, stoneValue, N);

        if (result == 0)
            return "Tie";

        return result > 0 ? "Alice" : "Bob";
    }

private:
    int solve(int idx, vector<int>& stoneValue, const int& N)
    {
        if (idx >= N)
            return 0;

        if (memo[idx] != INT_MIN)
            return memo[idx];

        int result = INT_MIN;

        int curr_sum = 0;
        curr_sum += (idx + 0 < N) ? stoneValue[idx + 0] : 0;
        result = max(result, curr_sum - solve(idx + 1, stoneValue, N));

        curr_sum += (idx + 1 < N) ? stoneValue[idx + 1] : 0;
        result = max(result, curr_sum - solve(idx + 2, stoneValue, N));

        curr_sum += (idx + 2 < N) ? stoneValue[idx + 2] : 0;
        result = max(result, curr_sum - solve(idx + 3, stoneValue, N));

        return memo[idx] = result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Top_Down__Memoization_4 {
private:
    static constexpr int MAX = 5 * 1e4;
    int memo[MAX + 4];

public:
    string stoneGameIII(vector<int>& stoneValue)
    {
        const int N = stoneValue.size();

        /* Initialize */
        fill(begin(memo), end(memo), INT_MIN);

        /* Solve */
        int alice_points = solve(0, stoneValue);

        if (alice_points == 0)
            return "Tie";

        return alice_points > 0 ? "Alice" : "Bob";
    }

private:
    int solve(int idx, vector<int>& stoneValue)
    {
        const int N = stoneValue.size();

        if (idx >= N)
            return 0;

        if (memo[idx] != INT_MIN)
            return memo[idx];

        int result = INT_MIN;
        int curr_sum = 0;

        // j = 0   (Take first                      stone starting at index i)
        // j = 1   (Take first and second           stone starting at index i)
        // j = 2   (Take first and second and third stone starting at index i)
        for (int j = 0; j < 3; j++)
        {
            curr_sum += (idx + j >= N) ? 0 : stoneValue[idx + j];

            result = max(result, curr_sum - solve(idx + j + 1, stoneValue));
        }

        return memo[idx] = result;
    }
};
