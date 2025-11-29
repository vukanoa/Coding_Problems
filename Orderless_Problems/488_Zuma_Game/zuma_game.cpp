/*
    ============
    === HARD ===
    ============

    ===========================
    488) Zuma Game
    ===========================

    ============
    Description:
    ============

    You are playing a variation of the game Zuma.

    In this variation of Zuma, there is a single row of colored balls on a
    board, where each ball can be colored red 'R', yellow 'Y', blue 'B', green
    'G', or white 'W'. You also have several colored balls in your hand.

    Your goal is to clear all of the balls from the board. On each turn:

        + Pick any ball from your hand and insert it in between two balls in
          the row or on either end of the row.

        + If there is a group of three or more consecutive balls of the same
          color, remove the group of balls from the board.

            + If this removal causes more groups of three or more of the same
              color to form, then continue removing each group until there are
              none left.

        + If there are no more balls on the board, then you win the game.

        + Repeat this process until you either win or do not have any more
          balls in your hand.

    Given a string board, representing the row of balls on the board, and a
    string hand, representing the balls in your hand, return the minimum number
    of balls you have to insert to clear all the balls from the board. If you
    cannot clear all the balls from the board using the balls in your hand,
    return -1.

    =====================================================
    FUNCTION: int findMinStep(string board, string hand);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: board = "WRRBBW", hand = "RB"
    Output: -1
    Explanation: It is impossible to clear all the balls. The best you can do is:
    - Insert 'R' so the board becomes WRRRBBW. WRRRBBW -> WBBW.
    - Insert 'B' so the board becomes WBBBW. WBBBW -> WW.
    There are still balls remaining on the board, and you are out of balls to insert.

    --- Example 2 ---
    Input: board = "WWRRBBWW", hand = "WRBRW"
    Output: 2
    Explanation: To make the board empty:
    - Insert 'R' so the board becomes WWRRRBBWW. WWRRRBBWW -> WWBBWW.
    - Insert 'B' so the board becomes WWBBBWW. WWBBBWW -> WWWW -> empty.
    2 balls from your hand were needed to clear the board.

    --- Example 3 ---
    Input: board = "G", hand = "GGGGG"
    Output: 2
    Explanation: To make the board empty:
    - Insert 'G' so the board becomes GG.
    - Insert 'G' so the board becomes GGG. GGG -> empty.
    2 balls from your hand were needed to clear the board.


    *** Constraints ***
    1 <= board.length <= 16
    1 <= hand.length <= 5
    board and hand consist of the characters 'R', 'Y', 'B', 'G', and 'W'.
    The initial row of balls on the board will not have any groups of three or
    more consecutive balls of the same color.

*/

#include <climits>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 65.71% */
/* Space Beats: 76.67% */
class Solution {
public:
    int findMinStep( string board, string hand )
    {
        vector<int> freq(26, 0);

        for (const char& chr : hand )
            freq[chr - 'A']++;

        unordered_map<string, int> memo;

        return dfs(board, freq, memo);
    }

private:
    int dfs(string board, vector<int>& freq, unordered_map<string, int>& memo)
    {
        const int N = board.size();
        const int M = freq.size();

        string key = board + "#" + serialize_freq( freq );

        if (memo.count(key))
            return memo[key];

        int result = INT_MAX;
        if (N == 0)
        {
            result = 0; // Base case: all balls removed
        }
        else
        {
            for (int i = 0; i < N; i++ )
            {
                for (int color = 0; color < M; color++)
                {
                    bool worth_trying = false;

                    // Worth trying if same color as current spot
                    if (board[i] - 'A' == color)
                    {
                        worth_trying = true;
                    }
                    // Or if previous ball same color, avoid duplicate work
                    else if (0 < i && board[i] == board[i - 1] && board[i] - 'A' != color)
                    {
                        worth_trying = true;
                    }

                    if (freq[color] > 0 && worth_trying)
                    {
                        board.insert( board.begin() + i, char( color + 'A' ));
                        freq[color]--;

                        string new_board = update_board(board);

                        int steps = dfs(new_board, freq, memo);

                        if (steps != -1)
                            result = min(result, steps + 1);

                        // Restore state
                        freq[color]++;
                        board.erase(board.begin() + i);
                    }
                }
            }
        }

        if (result == INT_MAX)
            result = -1;

        memo[key] = result;
        return result;
    }

    string update_board(const string& board)
    {
        const int N = board.length();

        int start = 0;
        int end   = 0;
        while (start < N)
        {
            while (end < N && board[start] == board[end])
                end++;

            // If 3 or more consecutive balls, remove them
            if (end - start >= 3)
            {
                string new_board = board.substr( 0, start ) + board.substr( end );

                // Recursively remove any new groups formed
                return update_board( new_board );
            }
            else
            {
                start = end;
            }
        }

        return board;
    }

    string serialize_freq( const vector<int> &freq )
    {
        const int M = freq.size();
        string key = "";

        for (int i = 0; i < M; i++)
        {
            if (freq[i] > 0)
            {
                // Convert color index to letter, then append count
                key += string(1, char(i + 'A')) + to_string(freq[i]);
            }
        }

        return key;
    }
};
