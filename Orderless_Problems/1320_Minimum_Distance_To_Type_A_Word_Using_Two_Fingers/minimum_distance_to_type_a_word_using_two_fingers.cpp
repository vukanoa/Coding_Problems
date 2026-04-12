/*
    ============
    === HARD ===
    ============

    =======================================================
    1320) Minimum Distance to Type a Word Using Two Fingers
    =======================================================

    ============
    Description:
    ============

    You have a keyboard layout as shown above in the X-Y plane, where each
    English uppercase letter is located at some coordinate.

        + For example, the letter 'A' is located at coordinate (0, 0), the
          letter 'B' is located at coordinate (0, 1), the letter 'P' is located
          at coordinate (2, 3) and the letter 'Z' is located at coordinate (4,
          1).

    Given the string word, return the minimum total distance to type such
    string using only two fingers.

    The distance between coordinates:

        (x1, y1) and (x2, y2) is |x1 - x2| + |y1 - y2|.

    =====
    Note: that the initial positions of your two fingers are considered free so
          do not count towards your total distance, also your two fingers do
          not have to start at the first letter or the first two letters. 
    =====

    ===========================================
    FUNCTION: int minimumDistance(string word);
    ===========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: word = "CAKE"
    Output: 3
    Explanation: Using two fingers, one optimal way to type "CAKE" is: 
    Finger 1 on letter 'C' -> cost = 0 
    Finger 1 on letter 'A' -> cost = Distance from letter 'C' to letter 'A' = 2 
    Finger 2 on letter 'K' -> cost = 0 
    Finger 2 on letter 'E' -> cost = Distance from letter 'K' to letter 'E' = 1 
    Total distance = 3

    --- Example 2 ---
    Input: word = "HAPPY"
    Output: 6
    Explanation: Using two fingers, one optimal way to type "HAPPY" is:
    Finger 1 on letter 'H' -> cost = 0
    Finger 1 on letter 'A' -> cost = Distance from letter 'H' to letter 'A' = 2
    Finger 2 on letter 'P' -> cost = 0
    Finger 2 on letter 'P' -> cost = Distance from letter 'P' to letter 'P' = 0
    Finger 1 on letter 'Y' -> cost = Distance from letter 'A' to letter 'Y' = 4
    Total distance = 6


    *** Constraints ***
    2 <= word.length <= 300
    word consists of uppercase English letters.

*/

#include <climits>
#include <cstring>
#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Classic Memoization problem.

*/

/* Time  Beats: 89.56% */
/* Space Beats: 75.90% */

/* Time  Complexity: O(N * 27 * 27) */
/* Space Complexity: O(N * 27 * 27) */
class Solution {
private:
    int memo[301][27][27];

    const int UNPLACED = 26;
    const int ROWS = 5;
    const int COLS = 6;

public:
    int minimumDistance(string word)
    {
        const int N = word.size();

        /* Memset */
        memset(memo, 0xff, sizeof(memo)); // 0xff == -1 in 2's complement

        // 26 == UNPLACED
        return solve(0, 26, 26, word);
    }

private:
    int solve(int idx, int f1, int f2, string& word)
    {
        const int N = word.size();

        if (idx == N)
            return 0;


        if (memo[idx][f1][f2] != -1)
            return memo[idx][f1][f2];

        int move_f1 = INT_MAX;
        int move_f2 = INT_MAX;

        // f1
        if (f1 == UNPLACED)
        {
            int new_f1 = word[idx] - 'A';
            move_f1 = 0 + solve(idx+1, new_f1, f2, word);
        }
        else
        {
            int cur_f1_x = f1 / COLS;
            int cur_f1_y = f1 % COLS;

            int new_f1_x = (word[idx] - 'A') / COLS;
            int new_f1_y = (word[idx] - 'A') % COLS;

            int distance = abs(cur_f1_x - new_f1_x) + abs(cur_f1_y - new_f1_y);

            int new_f1 = word[idx] - 'A';
            move_f1 = distance + solve(idx+1, new_f1, f2, word);
        }

        // f2
        if (f2 == UNPLACED)
        {
            int new_f2 = word[idx] - 'A';
            move_f2 = 0 + solve(idx+1, f1, new_f2, word);
        }
        else
        {
            int cur_f2_x = f2 / COLS;
            int cur_f2_y = f2 % COLS;

            int new_f2_x = (word[idx] - 'A') / COLS;
            int new_f2_y = (word[idx] - 'A') % COLS;

            int distance = abs(cur_f2_x - new_f2_x) + abs(cur_f2_y - new_f2_y);

            int new_f2 = word[idx] - 'A';
            move_f2 = distance + solve(idx+1, f1, new_f2, word);
        }

        return memo[idx][f1][f2] = min(move_f1, move_f2);
    }
};
