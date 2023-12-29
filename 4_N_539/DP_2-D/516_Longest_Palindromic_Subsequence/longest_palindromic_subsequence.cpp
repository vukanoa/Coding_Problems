#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ====================================
    516) Longest Palindromic Subsequence
    ====================================

    ============
    Description:
    ============

    Given a string s, find the longest palindromic subsequence's length in s.

    A subsequence is a sequence that can be derived from another sequence by
    deleting some or no elements without changing the order of the remaining
    elements.

    ================================================
    FUNCTION: int longestPalindromeSubseq(string s);
    ================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "bbbab"
    Output: 4
    Explanation: One possible longest palindromic subsequence is "bbbb".

    --- Example 2 ---
    Input: s = "cbbd"
    Output: 2
    Explanation: One possible longest palindromic subsequence is "bb".


    *** Constraints ***
    1 <= s.length <= 1000
    s consists only of lowercase English letters.

*/

/*
    ------------
    --- IDEA ---
    ------------

    This problem can be solved by using problem LCS(Longest Common Subsequence)
    from Blind75 list.

    The only thing we have to "prepare" before calling LCS, is to make 2
    strings that we're going to pass to LCS function.

    Since we are given only a single string, what should we do?

    Maybe it's not obvious, but if we pass:
        1. Original string
        2. Reversed Original string

    we are guaranteed to get a "Longest Palindromic Subsequence", which is what
    we are looking for.

    Why are we guaranteed?

*/

/* Time  Beats:  5.03% */
/* Space Beats: 42.70% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(n^2) */
class Solution_LCS {
public:
    int longestPalindromeSubseq(std::string s)
    {
        std::string s1 = s;
        std::string s2 = s;

        std::reverse(s2.begin(), s2.end()); // Reverse 2nd string

        return longest_increasing_subsequence(s1, s2);
    }

private:
    int longest_increasing_subsequence(std::string& s1, std::string& s2)
    {
        int n = s1.length(); // s1 and s2 are of the same length

        std::vector<std::vector<int>> dp(n+1, std::vector<int>(n+1, 0));

        for (int i = n-1; i >= 0; i--)
        {
            for (int j = n-1; j >= 0; j--)
            {
                if (s1[i] == s2[j])
                    dp[i][j] = 1 + dp[i+1][j+1];
                else
                    dp[i][j] = std::max(dp[i+1][j], dp[i][j+1]);
            }
        }

        return dp[0][0];
    }
};



/*
    ------------
    --- IDEA ---
    ------------

         0     1     2     3     4     5
         a     g     c     b     c     a
      +-----+-----+-----+-----+-----+-----+
0  a  |  1  |     |     |     |     |     |
      +-----+-----+-----+-----+-----+-----+
1  g  |     |  1  |     |     |     |     |
      +-----+-----+-----+-----+-----+-----+
2  c  |     |     |  1  |     |     |     |
      +-----+-----+-----+-----+-----+-----+     len = 1
3  b  |     |     |     |  1  |     |     |
      +-----+-----+-----+-----+-----+-----+
4  c  |     |     |     |     |  1  |     |
      +-----+-----+-----+-----+-----+-----+
5  a  |     |     |     |     |     |  1  |
      +-----+-----+-----+-----+-----+-----+



         0     1     2     3     4     5
         a     g     c     b     c     a
      +-----+-----+-----+-----+-----+-----+
0  a  |  1  |  1  |     |     |     |     |
      +-----+-----+-----+-----+-----+-----+
1  g  |     |  1  |  1  |     |     |     |
      +-----+-----+-----+-----+-----+-----+
2  c  |     |     |  1  |  1  |     |     |
      +-----+-----+-----+-----+-----+-----+     len = 2
3  b  |     |     |     |  1  |  1  |     |
      +-----+-----+-----+-----+-----+-----+
4  c  |     |     |     |     |  1  |  1  |
      +-----+-----+-----+-----+-----+-----+
5  a  |     |     |     |     |     |  1  |
      +-----+-----+-----+-----+-----+-----+


         0     1     2     3     4     5
         a     g     c     b     c     a
      +-----+-----+-----+-----+-----+-----+
0  a  |  1  |  1  |  1  |     |     |     |
      +-----+-----+-----+-----+-----+-----+
1  g  |     |  1  |  1  |  1  |     |     |
      +-----+-----+-----+-----+-----+-----+
2  c  |     |     |  1  |  1  |  3  |     |
      +-----+-----+-----+-----+-----+-----+     len = 3
3  b  |     |     |     |  1  |  1  |  1  |
      +-----+-----+-----+-----+-----+-----+
4  c  |     |     |     |     |  1  |  1  |
      +-----+-----+-----+-----+-----+-----+
5  a  |     |     |     |     |     |  1  |
      +-----+-----+-----+-----+-----+-----+



         0     1     2     3     4     5
         a     g     c     b     c     a
      +-----+-----+-----+-----+-----+-----+
0  a  |  1  |  1  |  1  |  1  |     |     |
      +-----+-----+-----+-----+-----+-----+
1  g  |     |  1  |  1  |  1  |  3  |     |
      +-----+-----+-----+-----+-----+-----+
2  c  |     |     |  1  |  1  |  3  |  3  |
      +-----+-----+-----+-----+-----+-----+     len = 3
3  b  |     |     |     |  1  |  1  |  1  |
      +-----+-----+-----+-----+-----+-----+
4  c  |     |     |     |     |  1  |  1  |
      +-----+-----+-----+-----+-----+-----+
5  a  |     |     |     |     |     |  1  |
      +-----+-----+-----+-----+-----+-----+



         0     1     2     3     4     5
         a     g     c     b     c     a
      +-----+-----+-----+-----+-----+-----+
0  a  |  1  |  1  |  1  |  1  |  3  |     |
      +-----+-----+-----+-----+-----+-----+
1  g  |     |  1  |  1  |  1  |  3  |  3  |
      +-----+-----+-----+-----+-----+-----+
2  c  |     |     |  1  |  1  |  3  |  3  |
      +-----+-----+-----+-----+-----+-----+     len = 4
3  b  |     |     |     |  1  |  1  |  1  |
      +-----+-----+-----+-----+-----+-----+
4  c  |     |     |     |     |  1  |  1  |
      +-----+-----+-----+-----+-----+-----+
5  a  |     |     |     |     |     |  1  |
      +-----+-----+-----+-----+-----+-----+



         0     1     2     3     4     5
         a     g     c     b     c     a
      +-----+-----+-----+-----+-----+-----+
0  a  |  1  |  1  |  1  |  1  |  3  |  5  |
      +-----+-----+-----+-----+-----+-----+
1  g  |     |  1  |  1  |  1  |  3  |  3  |
      +-----+-----+-----+-----+-----+-----+
2  c  |     |     |  1  |  1  |  3  |  3  |
      +-----+-----+-----+-----+-----+-----+     len = 5
3  b  |     |     |     |  1  |  1  |  1  |
      +-----+-----+-----+-----+-----+-----+
4  c  |     |     |     |     |  1  |  1  |
      +-----+-----+-----+-----+-----+-----+
5  a  |     |     |     |     |     |  1  |
      +-----+-----+-----+-----+-----+-----+


*/

/*
    #################
    ### BOTTOM-UP ###
    #################
*/

/* Time  Beats: 84.72% */
/* Space Beats: 57.23% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(n^2) */
class Solution_Bottom_Up {
public:
    int longestPalindromeSubseq(std::string s)
    {
        int n = s.length();

        std::vector<std::vector<int>> dp(n, std::vector(n, 0));

        for (int i = 0; i < n; i++)
            dp[i][i] = 1;

        for (int len = 1; len < n; len++)
        {
            for (int i = 0; i + len < n; i++)
            {
                int j = i + len;

                if (s[i] == s[j])
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                else
                    dp[i][j] = std::max(dp[i + 1][j], dp[i][j - 1]);
            }
        }

        return dp[0][n - 1];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same approach, implemented recursively.

*/

/*
    ################
    ### TOP-DOWN ###
    ################
*/

/* Using Memoization */

/* Time  Beats: 95.11% */
/* Space Beats: 57.23% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(n^2) */
class Solution_Top_Down {
public:
    int longestPalindromeSubseq(std::string& s)
    {
        if(s.empty())
            return 0;

        int n = s.size();
        std::vector<std::vector<int>> dp(n, std::vector<int>(n, -1));

        return recursion(dp, s, 0, n-1);
    }

private:
    int recursion(std::vector<std::vector<int> >& dp, std::string& s, int i, int j)
    {
        if(i > j)
            return 0;

        // Single character
        if(i == j)
            return dp[i][j] = 1;

        if(dp[i][j] == -1)
        {
            if(s[i] == s[j])
                dp[i][j] = 2 + recursion(dp, s, i+1, j-1);
            else
                dp[i][j] = std::max(recursion(dp, s, i+1, j),
                recursion(dp, s, i, j-1));
        }

        return dp[i][j];
    }
};
