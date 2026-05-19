/*
    ============
    === HARD ===
    ============

    ===========================
    115) Distinct Subsequences
    ===========================

    ============
    Description:
    ============

    Given two strings s and t, return the number of distinct subsequences of s
    which equals t.

    The test cases are generated so that the answer fits on a 32-bit signed
    integer.

    ==============================================
    FUNCTION: int numDistinct(string s, string t);
    ==============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "rabbbit", t = "rabbit"
    Output: 3
    Explanation:
    As shown below, there are 3 ways you can generate "rabbit" from s.

            ----------------
            |              |
            v              |
        rabbbit            |
            #             Omit this one
                           |
                           |
           -----------------
           |               |
           v               |
        rabbbit            |
           #               |
                           |
                           |
          ------------------
          |
          v
        rabbbit
          #




    --- Example 2 ---
    Input: s = "babgbag", t = "bag"
    Output: 5
    Explanation:
    As shown below, there are 5 ways you can generate "bag" from s.

        babgbag
          # ###    <--- Omit these

        babgbag
          ####     <--- Omit these

        babgbag
         ####      <--- Omit these

        babgbag
        ## ##      <--- Omit these

        babgbag
        ####       <--- Omit these


    *** Constraints ***
    1 <= s.length, t.length <= 1000        // This is important
    s and t consist of English letters.

*/

#include <climits>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 77.72% */
/* Space Beats: 74.29% */

/* Time  Complexity: O(N * M) */
/* Space Complexity: O(N * M) */
class Solution_Top_Down__Memoization {
private:
    unsigned long long memo[1001][1001];

public:
    int numDistinct(string s, string t)
    {
        const int N = s.size();
        const int M = t.size();

        /* Memset */
        memset(memo, 0xff, sizeof(memo)); // Fills with ULLONG_MAX

        return solve(0, 0, s, t);
    }

private:
    int solve(int i, int j, string& s, string& t)
    {
        const int N = s.size();
        const int M = t.size();

        if (j == M)
            return 1;

        if (i == N)
            return 0;

        if (N-i < M-j) // substring s is SMALLER than substring t
            return 0;

        if (memo[i][j] != ULLONG_MAX)
            return memo[i][j];

        unsigned long long diagonal = 0ULL;
        unsigned long long down     = solve(i+1, j  , s, t);

        if (s[i] == t[j])
            diagonal = solve(i+1, j+1, s, t);

        return memo[i][j] = down + diagonal;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    It's pretty similar to LCS(Longest Common Subsequence), but there are
    important differences. You really have to understand why and how are you
    filling the matrix "dp".

    Here is matrix "dp" for the Example 1:

        Input: s = "rabbbit", t = "rabbit"
        Output: 3

             0     1     2     3     4     5      6
            'r'   'a'   'b'   'b'   'i'   't'    ''
          +-----+-----+-----+-----+-----+-----++-----+
    0 'r' |  3  |  3  |  3  |  3  |  1  |  1  ||  1  |
          +-----+-----+-----+-----+-----+-----++-----+
    1 'a' |  0  |  3  |  3  |  3  |  1  |  1  ||  1  |
          +-----+-----+-----+-----+-----+-----++-----+
    2 'b' |  0  |  0  |  3  |  3  |  1  |  1  ||  1  |
          +-----+-----+-----+-----+-----+-----++-----+
    3 'b' |  0  |  0  |  1  |  2  |  1  |  1  ||  1  |
          +-----+-----+-----+-----+-----+-----++-----+
    4 'b' |  0  |  0  |  0  |  1  |  1  |  1  ||  1  |
          +-----+-----+-----+-----+-----+-----++-----+
    5 'i' |  0  |  0  |  0  |  0  |  1  |  1  ||  1  |
          +-----+-----+-----+-----+-----+-----++-----+
    6 't' |  0  |  0  |  0  |  0  |  0  |  1  ||  1  |
          +=====+=====+=====+=====+=====+=====++=====+
    7 ''  |  0  |  0  |  0  |  0  |  0  |  0  ||  1  |
          +-----+-----+-----+-----+-----+-----++-----+




    And here it is for the Example 2:

        Input: s = "babgbag", t = "bag"
        Output: 5

             0     1     2      3
            'b'   'a'   'g'    ''
          +-----+-----+-----++-----+
    0 'b' |  5  |  3  |  2  ||  1  |
          +-----+-----+-----++-----+
    1 'a' |  2  |  3  |  2  ||  1  |
          +-----+-----+-----++-----+
    2 'b' |  2  |  1  |  2  ||  1  |
          +-----+-----+-----++-----+
    3 'g' |  1  |  1  |  2  ||  1  |
          +-----+-----+-----++-----+
    4 'b' |  1  |  1  |  1  ||  1  |
          +-----+-----+-----++-----+
    5 'a' |  0  |  1  |  1  ||  1  |
          +-----+-----+-----++-----+
    6 'g' |  0  |  0  |  1  ||  1  |
          +=====+=====+=====++=====+
    7 ''  |  0  |  0  |  0  ||  1  |
          +-----+-----+-----++-----+


    First we fill the very last column with 1's because if t is an empty
    string then whatever happens to be in the string s, we know that the
    maximum number of distinct subsequences is 1.
    (Omit all character in the string s).

    However, if the opposite is the case then that means that the maximum
    number of distinct subsequences is 0. Why?

    Consider this:
        s = "bc"
        t = "abc"

    There is NOTHING we can do to string s to make it be equal to t(adding is
    not allowed, this is not "Edit Distance" Problem).

    So then if:
        s = ""
        t = "rab"

    Then the answer is 0.

    Since this matrix "dp" is of size (N+1) * (M+1) we are strating from:
        row = N
        col = M

    Since we have already computed the very last row and the very last column.

    So we are starting at that position and we are going backwards(left) within
    the COLUMNS and then backwards(up) once the entire current ROW is finished.

    This is the main point:
        if (s[row] == t[col])
            dp[row][col] = Down + Diagonal
        else
            dp[row][col] = Down only

    Make sure to understand what this means.

    If we are at certain position 'row' that means that we're considering
    string s being equal to the substring from that position untli the end.

             0     1     2      3
            'b'   'a'   'g'    ''
          +-----+-----+-----++-----+
    0 'b' |  5  |  3  |  2  ||  1  |
          +-----+-----+-----++-----+
    1 'a' |  2  |  3  |  2  ||  1  |
          +-----+-----+-----++-----+
    2 'b' |  2  |  1  |  2  ||  1  |
          +-----+-----+-----++-----+
    3 'g' |  1  |  1  |  2  ||  1  |
          +-----+-----+-----++-----+
    4 'b' |  1  |  1  |  1  ||  1  |
          +-----+-----+-----++-----+
    5 'a' |  0  |  1  |  1  ||  1  |
          +-----+-----+-----++-----+
    6 'g' |  0  |  0  |  1  ||  1  |
          +=====+=====+=====++=====+
    7 ''  |  0  |  0  |  0  ||  1  |
          +-----+-----+-----++-----+

    Each cell represents one subproblem.
    row determines what substring out of string s, we are looking right now.
    col determines what substring out of string t, we are looking right now.

    Let's say that row == 3. That means subtring of s we're considering is
    "gbag"

    Let's say that col == 1. That means substring of t we're considering is
    "ag"

    So what does that mean?

    It's the same thing as if the example looks like this:
        s = "gbag"
        t = "ag"

    What is the number of distinct subsequences. It's obvious that it's 1.

    But how do we know that? Or, rather, how did we conclude that out of the
    previously done subproblems before this one?

    If the beginning characters are NOT the same, then it's the same answer as
    if the example was:
        s = "bag"
        t = "ag"

    So what's the answer of that? What is the maximum number od distinct
    subsequences there?
    We can see that's it's 1.

    But, here comes the difficult part:
        What if the beginning characters ARE THE SAME?

    Let's consider different example(Let's use the subproblem of the Example 1)

        s = "bbit"
        t = "bit"

    What is the maximum number of distinct subsequences here?
    It's 2.

        First:
            s = "bbit"
                 #   <---- Omit this one

            t = "bit"


        Second:
            s = "bbit"
                  #  <---- Omit this one

            t = "bit"



    So if you think about the first one, it's really not any different,
    actually, it's the exact same thing - We ask:"What is the maximum number of
    distinct subsequnces if we omit this current character in string s?

    However, the Second one is the "important one".
    We want to know, IF WE TAKE THIS CURRENT CHARACTER(use it because it's the
    same one as the one at the beginning of string t), then what is the maximum
    number of distinct subsequences of the REMAINING string, which in this case
    is this:
        s = "bit"  (notice how the first 'b' isn't there anymore)
        t = "it"   (notuce how the first 'b' isn't there anymore)

    And we have to add those two answers together and store it in out
    dp[row][col].


    But how do we get the answer of this subproblem:
        s = "bit"
        t = "it"

    When we have:
        s = "bbit"
        t = "bit"


    Well, you can see that the answer you're looking for is:
        Diagonally ==> (row+1, col+1)


    That's why we do:
        if (s[row] == t[col])
            dp[row][col] = dp[row+1][col] + dp[row+1][col+1];
        else
            dp[row][col] = dp[row+1][col]

*/

/* Time  Beats: 65.41% */
/* Space Beats: 28.02% */

/* Time  Complexity: O(N * M) */
/* Space Complexity: O(N * M) */
class Solution_Bottom_Up__Tabulation {
public:
    int numDistinct(string s, string t)
    {
        const int N = s.size();
        const int M = t.size();

        vector<vector<unsigned long long>> dp(N+1, vector<unsigned long long>(M+1, 0ULL));
        dp[N][M] = 1ULL;

        /* Initialize Last COL */
        for (int i = N-1; i >= 0; i--)
            dp[i][M] = 1;

        /* Solve */
        for (int i = N-1; i >= 0; i--)
        {
            for (int j = M-1; j >= 0; j--)
            {
                if (s[i] == t[j])
                    dp[i][j] = dp[i+1][j] + dp[i+1][j+1]; // Down + Diagonal
                else
                    dp[i][j] = dp[i+1][j];                // Down
            }
        }

        return dp[0][0];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same idea as above, though you can notice above that we're only ever using
    the very next row, therefore we can use only two DP arrays instead, thus
    optimizing Space Complexity from O(N * M) down to O(M).

*/

/* Time  Beats: 75.32% */
/* Space Beats: 44.79% */

/* Time  Complexity: O(N * M) */
/* Space Complexity: O(M)     */
class Solution_Bottom_Up__Tabulation_Space_Optimized {
public:
    int numDistinct(string s, string t)
    {
        const int N = s.size();
        const int M = t.size();

        vector<unsigned long long> dp_next(M+1, 0ULL);
        dp_next[M] = 1ULL;

        /* Solve */
        for (int i = N-1; i >= 0; i--)
        {
            vector<unsigned long long> dp_curr(M+1, 0ULL);
            dp_curr[M] = 1ULL;

            for (int j = M-1; j >= 0; j--)
            {
                if (s[i] == t[j])
                    dp_curr[j] = dp_next[j] + dp_next[j+1]; // Down + Diagonal
                else
                    dp_curr[j] = dp_next[j];                // Down
            }

            dp_next = std::move(dp_curr);
        }

        return dp_next[0];
    }
};
