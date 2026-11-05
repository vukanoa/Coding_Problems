/*
    ==============
    === MEDIUM ===
    ==============

    ==================================================
    3365) Rearrange K Substrings to Form Target String
    ==================================================

    ============
    Description:
    ============

    You are given two strings s and t, both of which are anagrams of each
    other, and an integer k.

    Your task is to determine whether it is possible to split the string s into
    k equal-sized substrings, rearrange the substrings, and concatenate them in
    any order to create a new string that matches the given string t.

    Return true if this is possible, otherwise, return false.

    An anagram is a word or phrase formed by rearranging the letters of a
    different word or phrase, using all the original letters exactly once.

    A substring is a contiguous non-empty sequence of characters within a
    string.

    ================================================================
    FUNCTION: bool isPossibleToRearrange(string s, string t, int k);
    ================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "abcd", t = "cdab", k = 2
    Output: true
    Explanation:
        Split s into 2 substrings of length 2: ["ab", "cd"].
        Rearranging these substrings as ["cd", "ab"], and then concatenating
        them results in "cdab", which matches t.


    --- Example 2 ---
    Input: s = "aabbcc", t = "bbaacc", k = 3
    Output: true
    Explanation:
        Split s into 3 substrings of length 2: ["aa", "bb", "cc"].
        Rearranging these substrings as ["bb", "aa", "cc"], and then
        concatenating them results in "bbaacc", which matches t.


    --- Example 3 ---
    Input: s = "aabbcc", t = "bbaacc", k = 2
    Output: false
    Explanation:
        Split s into 2 substrings of length 3: ["aab", "bcc"].
        These substrings cannot be rearranged to form t = "bbaacc", so the
        output is false.



    *** Constraints ***
    1 <= s.length == t.length <= 2 * 10^5
    1 <= k <= s.length
    s.length is divisible by k.
    s and t consist only of lowercase English letters.
    The input is generated such that s and t are anagrams of each other.

*/

#include <string>
#include <unordered_map>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 31.67% */
/* Space Beats: 28.33% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    bool isPossibleToRearrange(string s, string t, int k)
    {
        const int N = s.size();
        const int sub_size = N / k;
        
        unordered_map<string, int> t_umap;
        unordered_map<string, int> s_umap;
        
        for (int start = 0; start < N; start += sub_size)
        {
            string str_t;
            string str_s;
            
            str_t.reserve(sub_size); // To prevent repeated reallocations
            str_s.reserve(sub_size); // To prevent repeated reallocations
            for (int j = start; j < start + sub_size; j++)
            {
                str_t += t[j];
                str_s += s[j];
            }

            ++t_umap[str_t];
            ++s_umap[str_s];
        }

        // In C++17 I could simply do:
        // return s_umap == t_umap;


        // C++14:
        if (s_umap.size() != t_umap.size())
            return false;

        for (const auto& [s_str, s_freq] : s_umap)
        {
            auto it = t_umap.find(s_str);

            if (it == t_umap.end() || it->second != s_freq)
                return false;
        }

        return true;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 47.50% */
/* Space Beats: 40.00% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_2 {
public:
    bool isPossibleToRearrange(string s, string t, int k)
    {
        const int N = s.size();
        const int sub_size = N / k;

        unordered_map<string, int> s_umap;
        unordered_map<string, int> t_umap;

        for (int start = 0; start < N; start += sub_size)
        {
            ++s_umap[s.substr(start, sub_size)];
            ++t_umap[t.substr(start, sub_size)];
        }

        return s_umap == t_umap;
    }
};
