#include <iostream>
#include <vector>

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

/*
    ------------
    --- IDEA ---
    ------------

    It is very similar to problems such as:
        1. Longest Common Subsequence.
        2. Distinct Subsequences
        3. Edit Distance

    Here is how the matrix "dp" looks like:

             0      1     2     3     4     5
            'a'   'a'   'b'   'c'   'c'    ''
          +-----+-----+-----+-----+-----++-----+
    0 'd' |  T  |  T  |  T  |  F  |  F  ||  F  |
          +-----+-----+-----+-----+-----++-----+
    1 'b' |  F  |  F  |  T  |  T  |  F  ||  F  |
          +-----+-----+-----+-----+-----++-----+
    2 'b' |  F  |  F  |  T  |  T  |  T  ||  F  |
          +-----+-----+-----+-----+-----++-----+
    3 'c' |  F  |  F  |  T  |  F  |  T  ||  F  |
          +-----+-----+-----+-----+-----++-----+
    4 'a' |  F  |  F  |  T  |  T  |  T  ||  F  |
          +=====+=====+=====+=====+=====++=====+
    6  '' |  F  |  F  |  F  |  F  |  T  ||  T  | <--------
          +-----+-----+-----+-----+-----++-----+         |
                                            ^            |
                                            |            |
                                            ---------  This ONE is ALWAYS true!


    Or let me use these:
        O ==> true
        - ==> false

    so that it's easier to distinguish one from another.


             0      1     2     3     4     5
            'a'   'a'   'b'   'c'   'c'    ''
          +-----+-----+-----+-----+-----++-----+
    0 'd' |  O  |  O  |  O  |  -  |  -  ||  -  |
          +-----+-----+-----+-----+-----++-----+
    1 'b' |  -  |  -  |  O  |  O  |  -  ||  -  |
          +-----+-----+-----+-----+-----++-----+
    2 'b' |  -  |  -  |  O  |  O  |  O  ||  -  |
          +-----+-----+-----+-----+-----++-----+
    3 'c' |  -  |  -  |  O  |  -  |  O  ||  -  |
          +-----+-----+-----+-----+-----++-----+
    4 'a' |  -  |  -  |  O  |  O  |  O  ||  -  |
          +=====+=====+=====+=====+=====++=====+
    6  '' |  -  |  -  |  -  |  -  |  O  ||  O  | <--------
          +-----+-----+-----+-----+-----++-----+         |
                                            ^            |
                                            |            |
                                            ---------  This ONE is ALWAYS true!

*/

/* Time  Beats: 100.00% */
/* Space Beats:  45.35% */

/* Time  Complexity: O(M * N) */
/* Space Complexity: O(M * N) */
class Solution {
public:
    bool isInterleave(std::string s1, std::string s2, std::string s3)
    {
        if (s1.length() + s2.length() != s3.length())
            return false;

        int M = s2.length(); // This is easier for me for some reason
        int N = s1.length();

        int S3_LEN = s3.length();

        std::vector<std::vector<bool>> dp(M+1, std::vector<bool>(N+1, false));

        /*
            If both s1 and s2 are empty, s3 is guaranteed to be empty or else
            we would've return false just upon entering this function.

            So since s1=="" and s2=="" and s3=="", therefore dp[M][N] = true.
        */
        dp[M][N] = true;

        // Fill Last Column
        for (int i = M-1; i >= 0; i--)
        {
            int x_from_the_back_of_s3 = s2.length() - i;

            if (s2[i] == s3[S3_LEN - x_from_the_back_of_s3])
                dp[i][N] = dp[i+1][N];
            else
                dp[i][N] = false;
        }

        // Fill Last Row
        for (int j = N-1; j >= 0; j--)
        {

            int x_from_the_back_of_s3 = s1.length() - j;

            if (s1[j] == s3[S3_LEN - x_from_the_back_of_s3])
                dp[M][j] = dp[M][j+1];
            else
                dp[M][j] = false;
        }

        // Start from Bottom Right and go to the Left until >= 0, then Up.
        for (int i = M-1; i >= 0; i--)
        {
            for (int j = N-1; j >= 0; j--)
            {
                int x_from_the_back_of_s3 = s2.length()-i + s1.length()-j;

                bool can_use_s1 = s1[j] == s3[S3_LEN - x_from_the_back_of_s3];
                bool can_use_s2 = s2[i] == s3[S3_LEN - x_from_the_back_of_s3];

                bool possible_using_s1 = can_use_s1 && dp[i  ][j+1];
                bool possible_using_s2 = can_use_s2 && dp[i+1][j  ];

                dp[i][j] = possible_using_s1 | possible_using_s2;
            }
        }

        return dp[0][0];
    }
};
