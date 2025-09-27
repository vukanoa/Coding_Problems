/*
    ============
    === EASY ===
    ============

    ==================================
    3692) Majority Frequency Character
    ==================================

    ============
    Description:
    ============

    You are given a string s consisting of lowercase English letters.

    The frequency group for a value k is the set of characters that appear
    exactly k times in s.

    The majority frequency group is the frequency group that contains the
    largest number of distinct characters.

    Return a string containing all characters in the majority frequency group,
    in any order. If two or more frequency groups tie for that largest size,
    pick the group whose frequency k is larger.

    ==================================================
    FUNCTION: string majorityFrequencyGroup(string s);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "aaabbbccdddde"
    Output: "ab"

    --- Example 2 ---
    Input: s = "abcd"
    Output: "abcd"

    --- Example 3 ---
    Input: s = "pfpfgi"
    Output: "fp"


    *** Constraints ***
    1 <= s.length <= 100
    s consists only of lowercase English letters.

*/

#include <algorithm>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats:  0.00% */
/* Space Beats: 11.11% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    string majorityFrequencyGroup(string s)
    {
        const int N = s.length();
        vector<unordered_set<char>> vec(101, unordered_set<char>());

        /* Sort */
        sort(s.begin(), s.end());

        int i = 0;
        while (i < N)
        {
            char chr = s[i];
            int freq = 0;
            while (i < N && chr == s[i])
            {
                i++;
                freq++;
            }

            vec[freq].insert(chr);
        }

        int group_size = 0;
        int slot = 100;
        for (int i = 100; i >= 0; i--)
        {
            if (vec[i].size() > group_size)
            {
                group_size = vec[i].size();
                slot = i;
            }
        }


        string result = "";
        for (const auto& iter : vec[slot])
            result += iter;
        
        return result;
    }
};
