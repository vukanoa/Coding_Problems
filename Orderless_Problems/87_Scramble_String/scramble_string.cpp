#include <iostream>
#include <vector>
#include <unordered_map>

/*
    ============
    === HARD ===
    ============

    ===========================
    87) Scramble String
    ===========================

    ============
    Description:
    ============

    We can scramble a string s to get a string t using the following algorithm:

        1. If the length of the string is 1, stop.
        2. If the length of the string is > 1, do the following:

               + Split the string into two non-empty substrings at a random
                 index, i.e., if the string is s, divide it to x and y where:
                 s = x + y.

               + Randomly decide to swap the two substrings or to keep them in
                 the same order. i.e., after this step, s may become s = x + y
                 or s = y + x.

               Apply step 1 recursively on each of the two substrings x and y.

    Given two strings s1 and s2 of the same length, return true if s2 is a
    scrambled string of s1, otherwise, return false.

    ================================================
    FUNCTION: bool isScramble(string s1, string s2);
    ================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s1 = "great", s2 = "rgeat"
    Output: true
    Explanation: One possible scenario applied on s1 is:

    "great" --> "gr/eat" // divide at random index.

    "gr/eat" --> "gr/eat" // random decision is not to swap the two substrings
                 and keep them in order.

    "gr/eat" --> "g/r / e/at" // apply the same algorithm recursively on both
                 substrings. divide at random index each of them.

    "g/r / e/at" --> "r/g / e/at" // random decision was to swap the first
                     substring and to keep the second substring in the same
                     order.

    "r/g / e/at" --> "r/g / e/ a/t" // again apply the algorithm recursively,
                     divide "at" to "a/t".

    "r/g / e/ a/t" --> "r/g / e/ a/t" // random decision is to keep both
                       substrings in the same order.

    The algorithm stops now, and the result string is "rgeat" which is s2.
    As one possible scenario led s1 to be scrambled to s2, we return true.



    --- Example 2 ---
    Input: s1 = "abcde", s2 = "caebd"
    Output: false


    --- Example 3 ---
    Input: s1 = "a", s2 = "a"
    Output: true


    *** Constraints ***
    s1.length == s2.length
    1 <= s1.length <= 30
    s1 and s2 consist of lowercase English letters.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats:  7.76% */
/* Space Beats:  5.09% */

/* Time  Complexity: O(n^4) */
/* Space Complexity: O(n^3) */
class Solution {
public:
    std::unordered_map<std::string, bool> umap;
    bool isScramble(std::string s1, std::string s2)
    {
        const int n = s1.size();

        if (n != s2.size())
            return false;

        if (s1.compare(s2) == 0)
            return true;

        if (umap.find(s1 + " " + s2) != umap.end())
            return umap[s1 + " " + s2];

        for (int i = 1; i < n; i++)
        {
            if (isScramble(s1.substr(0, i), s2.substr(0, i)) &&
                isScramble(s1.substr(i), s2.substr(i)))
            {
                return umap[s1 + " " + s2] = true;
            }

            if (isScramble(s1.substr(0, i), s2.substr(n - i)) &&
                isScramble(s1.substr(i), s2.substr(0, n - i)))
            {
                return umap[s1 + " " + s2] = true;
            }
        }

        return umap[s1 + " " + s2] = false;
    }
};




// Recursive approach - gives TLE
class Solution_TLE {
public:
    bool scramble(string s, string t)
    {
        const int n = s.size();

        if(s == t)
            return true;

        std::vector<int> letters_freq(26, 0);
        for(int i = 0; i < n; i++)
        {
            letters_freq[s[i] - 'a']++;
            letters_freq[t[i] - 'a']--;
        }

        for(int i = 0; i < 26; i++)
        {
            if (letters_freq[i])
                return false;
        }

        // s=gr|eat  t=gr|eat   (not scrambled)
        // s=gr|eat  t=ate|gr   (scrambled)
        for (int len = 1; len < n; len++)
        {
            if (scramble(s.substr(0,len), t.substr(0,len)) &&
                scramble(s.substr(len), t.substr(len)))
            {
                return true;
            }

            if (scramble(s.substr(0,len), t.substr(n-len)) &&
                scramble(s.substr(len), t.substr(0,n-len)))
            {
                return true;
            }
        }

        return false;
    }

    bool isScramble(std::string s, std::string t)
    {
        return scramble(s, t);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 70.77% */
/* Space Beats: 56.09% */

/* Time  Complexity: O(n^4) */
/* Space Complexity: O(n^3) */
class Solution_DP_plus_Top_Down {
private:
   std::map<std::pair<std::string, std::string>, bool> dp;

public:
    bool isScramble(std::string s, std::string t)
    {
        return scramble(s, t);
    }

private:
    bool scramble(std::string s, std::string t)
    {
        const int n = s.size();
        std::pair<std::string, std::string> combo = std::make_pair(s,t);

        if (dp.count(combo) != 0)
            return dp[combo];

        if (s == t)
            return true;

        std::vector<int> letters_freq(26, 0);

        for(int i = 0; i < n; i++)
            letters_freq[s[i] - 'a']++, letters_freq[t[i]-'a']--;

        for (int i = 0; i < 26; i++)
        {
            if (letters_freq[i])
                return false;
        }

        // s=gr|eat  t=gr|eat   (not scrambled)
        // s=gr|eat  t=ate|gr   (scrambled)

        for(int len = 1; len < n; len++)
        {
            if (scramble(s.substr(0,len), t.substr(0,len))     &&
                scramble(s.substr(len)  , t.substr(len))       ||
                scramble(s.substr(0,len), t.substr(n-len))     &&
                scramble(s.substr(len)  , t.substr(0, n-len)))
            {
                return dp[combo] = true;
            }

        }

        return dp[combo] = false;
    }
};
