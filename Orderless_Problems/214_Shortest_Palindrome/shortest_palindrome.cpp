#include <iostream>
#include <vector>

/*
    ============
    === HARD ===
    ============

    ===========================
    214) Shortest Palindrome
    ===========================

    ============
    Description:
    ============

    You are given a string s. You can convert s to a
    palindrome
    by adding characters in front of it.

    Return the shortest palindrome you can find by performing this
    transformation.

    ==============================================
    FUNCTION: string shortestPalindrome(string s);
    ==============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "aacecaaa"
    Output: "aaacecaaa"

    --- Example 2 ---
    Input: s = "abcd"
    Output: "dcbabcd"


    *** Constraints ***
    0 <= s.length <= 5 * 10^4
    s consists of lowercase English letters only.

*/

/*
    ------------
    --- IDEA ---
    ------------

    This one is O(N^2), but it's much easier to come up with.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  80.97% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(n)   */
class Solution {
public:
    string shortestPalindrome(string s)
    {
        int N = s.length();
        if (N == 0)
            return s;

        int L = 0;
        for (int R = N-1; R >= 0; R--)
        {
            if (s[R] == s[L])
                L++;
        }

        if (L == N)
            return s;

        string non_palindrome_suffix = s.substr(L);
        string reverse_suffix = string(non_palindrome_suffix.rbegin(), non_palindrome_suffix.rend());

        return reverse_suffix + shortestPalindrome(s.substr(0, L)) + non_palindrome_suffix;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 45.58% */
/* Space Beats: 19.27% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    std::string shortestPalindrome(std::string s)
    {
        const int n = s.size();
        std::string result = s;
        s += '#';

        for(int i = n-1; i >= 0; i--)
            s += s[i];

        std::vector<int>lps( 2*n + 2, 0);

        compute_LPS(lps, s, n+n+1);

        string tmp="";
        for(int i = n-1; i >= lps[2*n]; i--)
            tmp += s[i];

        return tmp + result;
    }

private:
    void compute_LPS(std::vector<int>& lps, std::string s, int m)
    {
        int len = 0;
        int i = 1;

        while(i < m)
        {
            if(s[len] == s[i])
            {
                len++;
                lps[i]=len;
                i++;
            }
            else
            {
                if(len != 0)
                    len = lps[len-1];
                else
                {
                    lps[i] = 0;
                    i++;
                }
            }
        }
    }
};
