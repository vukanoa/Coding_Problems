/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    97) Interleaving String
    ===========================

    ============
    Description:
    ============

    Given strings s1, s2, and s3, find whether s3 is formed by an interleaving
    of s1 and s2.

    An interleaving of two strings s and t is a configuration where s and t are
    divided into n and m substrings respectively, such that:

        s = s1 + s2 + ... + sn

        t = t1 + t2 + ... + tm

        |n - m| <= 1


        The interleaving is:
        s1 + t1 + s2 + t2 + s3 + t3 + ... or t1 + s1 + t2 + s2 + t3 + s3 + ...

    =====
    Node: a + b is the concatenation of strings a and b.
    =====

    Follow up: Could you solve it using only O(s2.length) additional memory
           space?

    =============================================================
    FUNCTION: bool isInterleave(string s1, string s2, string s3);
    =============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
    Output: true

    Explanation: One way to obtain s3 is:
    Split s1 into s1 = "aa" + "bc" + "c", and s2 into s2 = "dbbc" + "a".
    Interleaving the two splits, we get "aa" + "dbbc" + "bc" + "a" + "c" =
    "aadbbcbcac".  Since s3 can be obtained by interleaving s1 and s2, we
    return true.




    --- Example 2 ---
    Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
    Output: false
    Explanation: Notice how it is impossible to interleave s2 with any other
    string to obtain s3.



    --- Example 3 ---
    Input: s1 = "", s2 = "", s3 = ""
    Output: true



    *** Constraints ***
    0 <= s1.length, s2.length <= 100
    0 <= s3.length <= 200
    s1, s2, and s3 consist of lowercase English letters.

*/

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

/* Time  Beats: 100.00% */
/* Space Beats:  61.60% */

/* Time  Complexity: O(M * N) */
/* Space Complexity: O(M * N) */
class Solution_Top_Down__Memoization {
private:
    int memo[101][101];

public:
    bool isInterleave(string s1, string s2, string s3)
    {
        const int N = s1.size();
        const int M = s2.size();
        const int K = s3.size();

        if (N + M != K)
            return false;

        /* Memset */
        memset(memo, -1, sizeof(memo));

        return solve(0, 0, 0, s1, s2, s3);
    }

private:
    bool solve(int idx_1, int idx_2, int idx_3, string& s1, string& s2, string& s3)
    {
        const int N = s1.size();
        const int M = s2.size();
        const int K = s3.size();

        if (idx_3 == K)
            return true;

        if (memo[idx_1][idx_2] != -1)
            return memo[idx_1][idx_2];

        int take_s1 = 0;
        int take_s2 = 0;

        if (idx_1 < N && s1[idx_1] == s3[idx_3])
            take_s1 = solve(idx_1 + 1, idx_2    , idx_3 + 1, s1, s2, s3);

        if (idx_2 < M && s2[idx_2] == s3[idx_3])
            take_s2 = solve(idx_1    , idx_2 + 1, idx_3 + 1, s1, s2, s3);

        return memo[idx_1][idx_2] = take_s1 | take_s2;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    It is very similar to problems such as:

        1. Longest Common Subsequence.
        2. Distinct Subsequences
        3. Edit Distance

    Here is how the matrix "dp" looks like:

             0     1     2     3     4      5
            'd'   'b'   'b'   'c'   'a'    ''
          +-----+-----+-----+-----+-----++-----+
    0 'a' |  1  |  0  |  0  |  0  |  0  ||  0  |
          +-----+-----+-----+-----+-----++-----+
    1 'a' |  1  |  0  |  0  |  0  |  0  ||  0  |
          +-----+-----+-----+-----+-----++-----+
    2 'b' |  1  |  1  |  1  |  1  |  1  ||  0  |
          +-----+-----+-----+-----+-----++-----+
    3 'c' |  0  |  1  |  1  |  0  |  1  ||  0  |
          +-----+-----+-----+-----+-----++-----+
    4 'c' |  0  |  0  |  1  |  1  |  1  ||  1  |
          +=====+=====+=====+=====+=====++=====+
    6  '' |  0  |  0  |  0  |  0  |  0  ||  1  | <--------
          +-----+-----+-----+-----+-----++-----+         |
                                            ^            |
                                            |            |
                                            ---------  This ONE is ALWAYS true!


    For the ease of readiblity:

        X ==> true
        - ==> false

    so that it's easier to distinguish one from another.


             -     1     2     3     4      5
            'd'   'b'   'b'   'c'   'a'    ''
          +-----+-----+-----+-----+-----++-----+
    - 'a' |  X  |  -  |  -  |  -  |  -  ||  -  |
          +-----+-----+-----+-----+-----++-----+
    X 'a' |  X  |  -  |  -  |  -  |  -  ||  -  |
          +-----+-----+-----+-----+-----++-----+
    2 'b' |  X  |  X  |  X  |  X  |  X  ||  -  |
          +-----+-----+-----+-----+-----++-----+
    3 'c' |  -  |  X  |  X  |  -  |  X  ||  -  |
          +-----+-----+-----+-----+-----++-----+
    4 'c' |  -  |  -  |  X  |  X  |  X  ||  X  |
          +=====+=====+=====+=====+=====++=====+
    6  '' |  -  |  -  |  -  |  -  |  -  ||  X  | <--------
          +-----+-----+-----+-----+-----++-----+         |
                                            ^            |
                                            |            |
                                            ---------  This ONE is ALWAYS true!


*/

/* Time  Beats: 100.00% */
/* Space Beats:  45.35% */

/* Time  Complexity: O(M * N) */
/* Space Complexity: O(M * N) */
class Solution_Bottom_Up__Tabulation {
public:
    bool isInterleave(string s1, string s2, string s3)
    {
        const int N = s1.size();
        const int M = s2.size();
        const int K = s3.size();

        if (N + M != K)
            return false;

        vector<vector<bool>> dp(N+1, vector<bool>(M+1, false));
        dp[N][M] = true;

        /* Initialize last ROW */
        for (int col = M-1; col >= 0; col--)
        {
            int s1_characters = 0;       // Last s1_characters from s1
            int s2_characters = M - col; // Last s2_characters from s2

            int consider_amount = s1_characters + s2_characters;

            bool possible_with_s2 = s2[M - s2_characters] == s3[K - consider_amount];

            dp[N][col] = possible_with_s2 && dp[N][col+1];
        }

        /* Initialize last COL */
        for (int row = N-1; row >= 0; row--)
        {
            int s1_characters = N - row; // Last s1_characters from s1
            int s2_characters = 0;       // Last s2_characters from s2

            int consider_amount = s1_characters + s2_characters;

            bool possible_with_s1 = s1[N - s1_characters] == s3[K - consider_amount];

            dp[row][M] = possible_with_s1 && dp[row+1][M];
        }

        /* Solve */
        for (int row = N-1; row >= 0; row--)
        {
            for (int col = M-1; col >= 0; col--)
            {
                int s1_characters = N - row;
                int s2_characters = M - col;

                int consider_amount = s1_characters + s2_characters;

                bool possible_with_s1 = s1[N - s1_characters] == s3[K - consider_amount];
                bool possible_with_s2 = s2[M - s2_characters] == s3[K - consider_amount];

                dp[row][col] = false;

                if (possible_with_s1)
                    dp[row][col] = dp[row][col] | (possible_with_s1 && dp[row+1][col  ]);

                if (possible_with_s2)
                    dp[row][col] = dp[row][col] | (possible_with_s2 && dp[row  ][col+1]);
            }
        }

        return dp[0][0];
    }
};
