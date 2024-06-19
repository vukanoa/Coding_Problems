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
