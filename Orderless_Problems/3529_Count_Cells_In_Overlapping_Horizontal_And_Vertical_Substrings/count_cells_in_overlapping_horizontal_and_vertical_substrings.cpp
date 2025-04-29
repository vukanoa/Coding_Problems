/*
    ==============
    === MEDIUM ===
    ==============

    ===================================================================
    3529) Count Cells in Overlapping Horizontal and Vertical Substrings
    ===================================================================

    ============
    Description:
    ============

    You are given an m x n matrix grid consisting of characters and a string
    pattern.

    A horizontal substring is a contiguous sequence of characters read from
    left to right. If the end of a row is reached before the substring is
    complete, it wraps to the first column of the next row and continues as
    needed. You do not wrap from the bottom row back to the top.

    A vertical substring is a contiguous sequence of characters read from top
    to bottom. If the bottom of a column is reached before the substring is
    complete, it wraps to the first row of the next column and continues as
    needed. You do not wrap from the last column back to the first.

    Count the number of cells in the matrix that satisfy the following
    condition:

        The cell must be part of at least one horizontal substring and at
        least one vertical substring, where both substrings are equal to the
        given pattern.

    Return the count of these cells.

    =====================================================================
    FUNCTION: int countCells(vector<vector<char>>& grid, string pattern);
    =====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [["a","a","c","c"],
                   ["b","b","b","c"],
                   ["a","a","b","a"],
                   ["c","a","a","c"],
                   ["a","a","b","a"]],

            pattern = "abaca"
    Output: 1
    Explanation: The pattern "abaca" appears once as a horizontal substring
                 (colored blue) and once as a vertical substring (colored red),
                 intersecting at one cell (colored purple).


    --- Example 2 ---
    Input: grid = [["c","a","a","a"],
                   ["a","a","b","a"],
                   ["b","b","a","a"],
                   ["a","a","b","a"]], pattern = "aba"
    Output: 4
    Explanation: The cells colored above are all part of at least one
                 horizontal and one vertical substring matching the pattern
                 "aba".


    *** Constraints ***
    Input: grid = [["a"]], pattern = "a"
    Output: 1

*/

#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Even though this Solution has THE SAME Time and Space Complexities, this
    one gives us a TLE.

    Why?

    Because in practice, if we have:

        grid = [["a", "a", "a", ... , "a"]
                ["a", "a", "a", ... , "a"]
                ...
                ["a", "a", "a", ... , "a"]

        pattern "aaaaaaa...aaaaa"


    It will be WAY to inefficient.

    However in terms of correctness, this one does work. It is correctly
    implemented.


    However, in order to overcome this inefficiency, we need to use on KMP
    "trick":

        (Read the "IDEA" of the 2nd Solution down below)

*/

/* Time  Complexity: O(ROWS * COLS + PATTERN_LEN) */
/* Space Complexity: O(ROWS * COLS + PATTERN_LEN) */
class Solution_Working_BUT_TLEEE {
public:
    int countCells(vector<vector<char>>& grid, string pattern)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();
        const int TOTAL = ROWS * COLS;

        const int PATTERN_LEN = pattern.length();

        string str_horizontal(TOTAL, 0);
        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                str_horizontal[row * COLS + col] = grid[row][col];
            }
        }

        string str_vertical(TOTAL, 0);
        for (int col = 0; col < COLS; col++)
        {
            for (int row = 0; row < ROWS; row++)
            {
                str_vertical[col * ROWS + row] = grid[row][col];
            }
        }

        vector<int> LPS = compute_LPS(pattern);

        vector<vector<bool>> state_hor(ROWS, vector<bool>(COLS, false));
        vector<vector<bool>> state_ver(ROWS, vector<bool>(COLS, false));

        int i = 0;
        int j = 0;
        while (i < (TOTAL))
        {
            if (str_horizontal[i] == pattern[j])
            {
                i++;
                j++;
            }
            else
            {
                if (j > 0)
                {
                    j = LPS[j - 1];
                }
                else
                {
                    i++;
                }
            }

            if (j == PATTERN_LEN)
            {
                for (int k = i - PATTERN_LEN; k < i; ++k)
                    state_hor[k / COLS][k % COLS] = true;

                j = LPS[j-1];
            }
        }


        i = 0;
        j = 0;
        while (i < (TOTAL))
        {
            if (PATTERN_LEN - j > (ROWS * COLS - i))
                break;

            if (str_vertical[i] == pattern[j])
            {
                i++;
                j++;
            }
            else
            {
                if (j > 0)
                {
                    j = LPS[j - 1];
                }
                else
                {
                    i++;
                }
            }

            if (j == PATTERN_LEN)
            {
                for (int k = i - PATTERN_LEN; k < i; ++k)
                {
                    state_ver[k % ROWS][k / ROWS] = true;
                }

                j = LPS[j-1];
            }
        }

        int result = 0;
        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                if (state_hor[row][col] && state_ver[row][col])
                    result++;
            }
        }

        return result;
    }

private:
    vector<int> compute_LPS(string pattern)
    {
        const int M = pattern.length();
        vector<int> LPS(M);

        int prefix_len = 0;
        int i = 1;
        while (i < pattern.length())
        {
            if (pattern[prefix_len] == pattern[i])
            {
                LPS[i] = prefix_len + 1;
                prefix_len++;
                i++;
            }
            else
            {
                if (prefix_len > 0)
                {
                    prefix_len = LPS[prefix_len - 1];
                }
                else
                {
                    LPS[i] = 0;
                    i++;
                }
            }
        }

        return LPS;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO
    This is the main "trick" of this problem:

        string horizontal_match_str = pattern + "#" + str_horizontal;
        string vertical_match_str   = pattern + "#" + str_vertical;

        vector<int> horizontal_LPS = compute_LPS(horizontal_match_str);
        vector<int> vertical_LPS   = compute_LPS(vertical_match_str);


    Example 2:
        Input: grid = [["c","a","a","a"],
                       ["a","a","b","a"],
                       ["b","b","a","a"],
                       ["a","a","b","a"]], pattern = "aba"
        Output: 4


    For this Input grid and pattern "aba":

        // indices               0 1 2 3 4 5 6 7 8 9 ...           ... 19
        horizontal_match_str =   a b a # c a a a a a b a b b a a a a b a
        LPS_horizontal       =  [0 0 1 0 0 1 2 3 1 1 2 3 1 2 3 2 3 1 1 1]


        // indices               0 1 2 3 4 5 6 7 8 9 ...           ... 19
        vertical_match_str   =   a b a # c a b a a a b a a b a b a a a a
        LPS_vertical         =  [0 0 1 0 0 1 2 3 1 1 2 3 1 2 3 2 3 1 1 1]


    As you can see, to determine how many matches we got in horizontal or
    vertical we can simply get the number of PATTER_LEN values in each LPS.

    However, we can't just take those values or positions. Those are the ENDS
    of successful pattern matches.

    Therefore, subtracting PATTERN_LEN and adding 1 will get us to the starting
    index of this matched substring.

    We then store those using Line_Sweep technique and then for each state that
    is greater than 0, we know it's used in horizontal.

    We calculate correct row and col and mark used[row][col] = true.


    Once we get to do the same for vertical, we don't have to mark, we can just
    check if this cell was already used. If it is, that means it's used in both
    horizontal and vertical string matching, therefore we increment result.


    It seems difficult, but it's not. There's just "a lot of things to do".

    Also, if you didn't know aobut the "trick", you'd get a TLE as we did right
    up above.

*/

/* Time  Beats: 80.99% */
/* Space Beats: 30.19% */

/* Time  Complexity: O(ROWS * COLS + PATTERN_LEN) */
/* Space Complexity: O(ROWS * COLS + PATTERN_LEN) */
class Solution_KMP_Trick {
public:
    int countCells(vector<vector<char>>& grid, string pattern)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();
        const int TOTAL = ROWS * COLS;

        const int PATTERN_LEN = pattern.length();

        string str_horizontal(TOTAL, 0);
        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                str_horizontal[row * COLS + col] = grid[row][col];
            }
        }

        string str_vertical(TOTAL, 0);
        for (int col = 0; col < COLS; col++)
        {
            for (int row = 0; row < ROWS; row++)
            {
                str_vertical[col * ROWS + row] = grid[row][col];
            }
        }

        string horizontal_match_str = pattern + "#" + str_horizontal;
        string vertical_match_str   = pattern + "#" + str_vertical;

        vector<int> horizontal_LPS = compute_LPS(horizontal_match_str);
        vector<int> vertical_LPS   = compute_LPS(vertical_match_str);



        const int LPS_SIZE = horizontal_LPS.size(); // or vertical_LPS.size()

        vector<int> line_sweep_horizontal(LPS_SIZE + 1, 0);
        vector<int> line_sweep_vertical  (LPS_SIZE + 1, 0);

        // Horizontal Line Sweep
        for (int i = 0; i < LPS_SIZE; i++)
        {
            if (horizontal_LPS[i] == PATTERN_LEN)
            {
                int substr_start = i - PATTERN_LEN + 1;
                int substr_end   = i;

                line_sweep_horizontal[substr_start]++;
                line_sweep_horizontal[substr_end + 1]--;
            }
        }

        // Vertical Line Sweep
        for (int i = 0; i < LPS_SIZE; i++)
        {
            if (vertical_LPS[i] == PATTERN_LEN)
            {
                int substr_start = i - PATTERN_LEN + 1;
                int substr_end   = i;

                line_sweep_vertical[substr_start]++;
                line_sweep_vertical[substr_end + 1]--;
            }
        }

        vector<vector<bool>> used(ROWS, vector<bool>(COLS, false));

        int state = 0;
        for (int i = 0; i < line_sweep_horizontal.size(); i++)
        {
            state += line_sweep_horizontal[i];

            if (state > 0)
            {
                int real_idx = i - PATTERN_LEN - 1;

                int row = real_idx / COLS;
                int col = real_idx % COLS;

                used[row][col] = true;
            }
        }

        int result = 0;

        state = 0;
        for (int i = 0; i < line_sweep_vertical.size(); i++)
        {
            state += line_sweep_vertical[i];

            if (state > 0)
            {
                int real_idx = i - PATTERN_LEN - 1;

                int row = real_idx % ROWS;
                int col = real_idx / ROWS;

                if (used[row][col])
                    result++;
            }
        }

        return result;
    }

private:
    vector<int> compute_LPS(string pattern)
    {
        const int M = pattern.length();
        vector<int> LPS(M);

        int prefix_len = 0;
        int i = 1;
        while (i < pattern.length())
        {
            if (pattern[prefix_len] == pattern[i])
            {
                LPS[i] = prefix_len + 1;
                prefix_len++;
                i++;
            }
            else
            {
                if (prefix_len > 0)
                {
                    prefix_len = LPS[prefix_len - 1];
                }
                else
                {
                    LPS[i] = 0;
                    i++;
                }
            }
        }

        return LPS;
    }
};
