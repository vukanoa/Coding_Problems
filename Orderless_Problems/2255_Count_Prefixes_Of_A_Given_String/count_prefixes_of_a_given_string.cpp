/*
    ============
    === EASY ===
    ============

    ======================================
    2255) Count Prefixes of a Given String
    ======================================

    ============
    Description:
    ============

    You are given a string array words and a string s, where words[i] and s
    comprise only of lowercase English letters.

    Return the number of strings in words that are a prefix of s.

    A prefix of a string is a substring that occurs at the beginning of the
    string. A substring is a contiguous sequence of characters within a string.

    =============================================================
    FUNCTION: int countPrefixes(vector<string>& words, string s);
    =============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: words = ["a","b","c","ab","bc","abc"], s = "abc"
    Output: 3
    Explanation:
    The strings in words which are a prefix of s = "abc" are:
    "a", "ab", and "abc".
    Thus the number of strings in words which are a prefix of s is 3.

    --- Example 2 ---
    Input: words = ["a","a"], s = "aa"
    Output: 2
    Explanation:
    Both of the strings are a prefix of s. 
    Note that the same string can occur multiple times in words, and it should
    be counted each time.


    *** Constraints ***
    1 <= words.length <= 1000
    1 <= words[i].length, s.length <= 10
    words[i] and s consist of lowercase English letters only.

*/

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
/* Space Beats:  68.24% */

/* Time  Complexity: O(N) */ // Since words[i] and s are maximally 10
/* Space Complexity: O(1) */
class Solution {
public:
    int countPrefixes(vector<string>& words, string s)
    {
        const int N = words.size();
        int result = 0;

        for (int i = 0; i < N; i++)
        {
            int size_of_substring = words[i].length();
            string substring_of_s = s.substr(0, size_of_substring);

            if (words[i] == substring_of_s)
                result++;
        }

        return result;
    }
};
